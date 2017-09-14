<?php

/**
 * Implements hook_form().
 */
function addtoany_entities_form(){

  $entities = entity_get_info();

  foreach($entities as $entity => $info) {

    $bundles = $info['bundles'];

    $form['addtoany_'.$entity] = array(
      '#type'          => 'fieldset',
      '#title'         => t('!entity',array('!entity' => ucwords($entity))),
      '#description'   => t('Display buttons for <em>!entity</em> entity type.', array('!entity' => $entity)),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['addtoany_'.$entity]['addtoany_'.$entity.'_bundles'] = array(
      '#type'          => 'checkboxes',
      '#title'         => t('<em>!entity</em> bundles',array('!entity' => ucwords($entity))),
      '#description'   => t('Select !entity bundles.', array('!entity' => $entity)),
      '#default_value' => variable_get('addtoany_'.$entity.'_bundles', array()),
      '#options'       => array_combine(array_keys($bundles), array_keys($bundles))
    );

    $form['addtoany_'.$entity]['addtoany_'.$entity.'_view_mode'] = array(
      '#type'          => 'checkboxes',
      '#title'         => t('<em>!entity</em> view modes',array('!entity' => ucwords($entity))),
      '#default_value' => variable_get('addtoany_'.$entity.'_view_mode', array()),
      '#options'       => array_combine(array_keys($info['view modes']), array_keys($info['view modes']))
    );

    $form['addtoany_'.$entity]['addtoany_'.$entity.'_section'] = array(
      '#type'          => 'radios',
      '#title'         => t('Display Section'),
      '#default_value' => variable_get('addtoany_'.$entity.'_section', 'content'),
      '#options'       => array('content','links'),
      '#description'   => t('Select the section in which display buttons.'),
    );

    $form['addtoany_'.$entity]['addtoany_'.$entity.'_section_weight'] = array(
      '#type'          => 'weight',
      '#title'         => t('Weight'),
      '#default_value' => variable_get('addtoany_'.$entity.'_section_weight', 40),
      '#delta'         => 50,
      '#description'   => t('<strong>Optional</strong>: <em>Weight</em> value for AddToAny button displayed in <em>Content</em> section'),
      '#states' => array(
        // Show the settings if 'bar' has been selected for 'foo'.
        'visible' => array(
          ':input[name="addtoany_'.$entity.'_section"]' => array('value' => 0),
        ),
      ),
    );
  }

  return $form;
}
