<?php

namespace Drupal\uiowa_tracker\EventSubscriber;

use Drupal\Core\Config\ConfigFactory;
use Drupal\Core\Database\Connection;
use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Entity\EntityTypeManager;
use Drupal\Core\Routing\CurrentRouteMatch;
use Drupal\Core\Session\AccountProxyInterface;
use Drupal\node\NodeInterface;
use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\HttpKernel\Event\GetResponseEvent;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;

/**
 * {@inheritdoc}
 */
class UIowaTrackerRequestSubscriber implements EventSubscriberInterface {

  protected $routeMatch;
  protected $connection;
  protected $config;
  protected $currentUser;
  protected $entityTypeManager;

  /**
   * {@inheritdoc}
   */
  public function __construct(CurrentRouteMatch $routeMatch, Connection $connection, ConfigFactory $config, AccountProxyInterface $currentUser, EntityTypeManager $entityTypeManager) {
    $this->routeMatch = $routeMatch;
    $this->connection = $connection;
    $this->config = $config;
    $this->currentUser = $currentUser;
    $this->entityTypeManager = $entityTypeManager;
  }

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    $events[KernelEvents::REQUEST][] = ['trackNodes'];
    return $events;
  }

  /**
   * Tracks the request if it belongs to a node.
   *
   * @param \Symfony\Component\HttpKernel\Event\GetResponseEvent $event
   *   The response event for this request.
   */
  public function trackNodes(GetResponseEvent $event) {

    /* @var NodeInterface $node */
    $node = $this->routeMatch->getParameter('node');
    $isNode = $node instanceof NodeInterface;
    $isNodeRoute = $this->routeMatch->getRouteName() == 'entity.node.canonical';

    if (!$isNode || !$isNodeRoute) {
      return;
    }
    // UID = 0 means anonymous.
    $uid = $this->currentUser->id();
    $nid = $node->id();

    // @TODO Is this really the name of the content type?
    $nodeIsType = TRUE || $node->bundle() == 'content-type';
    $nodeIsTracked = $this->uiowaTrackerCheckNode($node);

    if ($nodeIsType && $uid && $nodeIsTracked) {
      $this->uiowaTrackerInsertNodeView($nid, $uid);
    }
  }

  /**
   * Insert node view into uiowa_tracker_log table.
   *
   * @param int $nid
   *   The viewed node.
   * @param int $uid
   *   The user who viewed the node.
   *
   * @return bool
   *   TRUE if node was added to the uiowa_tracker_log table, otherwise FALSE.
   */
  protected function uiowaTrackerInsertNodeView($nid, $uid) {
    if (is_numeric($nid) && is_numeric($uid) && $uid) {
      $nodeStorage = $this->entityTypeManager->getStorage('node');
      $userStorage = $this->entityTypeManager->getStorage('user');

      /* @var \Drupal\node\Entity\Node $node */
      $node = $nodeStorage->load($nid);

      /* @var \Drupal\user\Entity\User $user */
      $user = $userStorage->load($uid);
    }
    else {
      return FALSE;
    }

    $path = $node->toUrl()->toString();

    $rolelist = "";
    foreach ($user->getRoles() as $role) {
      if ($role != "authenticated") {
        $rolelist .= $role . ", ";
      }
    }
    $rolelist = substr($rolelist, 0, -2);

    $this->connection->insert('uiowa_tracker_log')
      ->fields([
        'nid' => $nid,
        'path' => $path,
        'pagetitle' => $node->getTitle(),
        'uid' => $uid,
        'username' => $user->getAccountName(),
        'rolename' => $rolelist,
        'timestamp' => REQUEST_TIME,
      ])->execute();
  }

  /**
   * Check that the nid is found in the uiowa_tracker_paths table.
   *
   * @param \Drupal\Core\Entity\EntityInterface $node
   *   The viewed node.
   *
   * @return bool
   *   TRUE if the node is found in the uiowa_tracker_paths table.
   */
  public function uiowaTrackerCheckNode(EntityInterface $node) {

    $query = $this->connection->select('uiowa_tracker_paths', 'p')
      ->fields('p', ['path'])
      ->execute();
    while ($result = $query->fetchAssoc()) {
      $pathlist[] = $result[path];
    }
    $path = $node->toUrl()->toString();
    if (in_array($path, $pathlist)) {
      return TRUE;
    }
    return FALSE;
  }

}
