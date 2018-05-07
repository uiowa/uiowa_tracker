<?php

namespace Drupal\uiowa_tracker\Form;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Database\Connection;
use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Implements the admin form for the University of Iowa Tracker.
 */
class UIowaTrackerConfigForm extends ConfigFormBase {

  protected $connection;

  /**
   * {@inheritdoc}
   */
  public function __construct(ConfigFactoryInterface $config_factory, Connection $connection) {
    parent::__construct($config_factory);
    $this->connection = $connection;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('config.factory'),
      $container->get('database')
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return [
      'uiowa_tracker.settings',
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'uiowa_tracker_config_form';
  }

  /**
   * Build the simple form.
   *
   * A build form method constructs an array that defines how markup and
   * other form elements are included in an HTML form.
   *
   * @param array $form
   *   Default form array structure.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   Object containing current form state.
   *
   * @return array
   *   The render array defining the elements of the form.
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $query = $this->connection->select('uiowa_tracker_paths', 'p')
      ->fields('p', array('path'))
      ->execute();
    while($result = $query->fetchAssoc()) {
      $pathlist[] = $result[path];
    }
    $uiowa_tracker_pathlist = implode("\r\n", $pathlist);

    $form['uiowa_tracker_pathlist'] = [
      '#type' => 'textarea',
      '#title' => $this->t('Enter paths of all nodes to track authenticated user views (one per line)'),
      '#description' => $this->t('The paths (e.g. /about/contact) of all nodes that require tracking of authenticated user views, one path per line. ADD leading or trailing slashes.'),
      '#required' => TRUE,
      '#rows' => 15,
      '#default_value' => $uiowa_tracker_pathlist,
    ];

    $form['uiowa_tracker_clearlog_fieldset'] = [
      '#type' => 'fieldset',
      '#title' => $this->t('Operations'),
      '#description' => $this->t('In order to clear all entries in the tracking log table, click the \'Clear tracking log\' button. This will remove ALL entries in the table, so use with caution.'),
      '#open' => FALSE,
    ];

    $form['uiowa_tracker_clearlog_fieldset']['uiowa_tracker_clearlog'] = [
      '#type' => 'submit',
      '#value' => $this->t('Clear tracking log'),
      '#attributes' => ['onclick' => 'if(!confirm("Are you sure you want to delete all entries in the tracking log?")){return false;}'],
      '#submit' => ['::uiowaTrackerClearlogFormSubmit'],
    ];

    // Add a submit button that handles the submission of the form.
    $form['actions']['#type'] = 'actions';
    $form['actions']['submit'] = [
      '#type' => 'submit',
      '#value' => $this->t('Save configuration'),
      '#button_type' => 'primary',
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    // Clear existing entries from the uiowa_tracker_paths table.
    $this->connection->delete('uiowa_tracker_paths')->execute();
    drupal_set_message($this->t('The paths table has been cleared.'));
  }

  /**
   * Implements a form submit handler.
   *
   * The submitForm method is the default method called for any submit elements.
   *
   * @param array $form
   *   The render array of the currently built form.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   Object describing the current state of the form.
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {

    $values = array(
      'uiowa_tracker_pathlist' => $form_state->getValue('uiowa_tracker_pathlist'),
    );

    $pathlist = preg_split("/\r\n|\n|\r/", $values['uiowa_tracker_pathlist']);

    // Enter the node id and alias of each path in the pathlist into the uiowa_tracker_paths table.
    $query = $this->connection->insert('uiowa_tracker_paths')->fields(array('nid','path'));
    foreach ($pathlist as $path) {
      $normal_path = \Drupal::service('path.alias_manager')->getPathByAlias($path);
      $nid = str_ireplace("/node/",'',$normal_path);

      if (empty($path)) {
        continue;
      }
      elseif ($normal_path == $path) {
        // If the node does not exist, the normal_path and path will be the same value.
        drupal_set_message($this->t('The path \'' . $path . '\' has been ignored and removed because it does not exist.'), 'warning');
        continue;
      }

      $query->values(array(
        'nid' => $nid,
        'path' => $path,
      ));
    }
    $query->execute();

    drupal_set_message($this->t('The path list of tracked nodes has been saved.'));

    return parent::submitForm($form, $form_state);
  }

  /**
   * Clear log submit event.
   *
   * @param array $form
   *   The render array of the currently built form.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   Object describing the current state of the form.
   */
  public function uiowaTrackerClearlogFormSubmit(array &$form, FormStateInterface $form_state) {
    $this->connection->delete('uiowa_tracker_log')->execute();
    drupal_set_message($this->t('All entries in the University of Iowa tracker log have been cleared.'));
  }

}
