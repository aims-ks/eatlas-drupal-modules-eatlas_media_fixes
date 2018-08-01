<?php

function _eatlas_media_fixes_settings() {
	// https://api.drupal.org/api/drupal/developer%21topics%21forms_api_reference.html/7
	$form = array();

	// Get the list of all view mode (file styles) for images.
	$fake_file = new stdClass();
	$fake_file->type = 'image';
	// http://www.drupalcontrib.org/api/drupal/contributions%21media%21includes%21media.filter.inc/function/media_get_wysiwyg_allowed_view_modes/7
	$view_modes = media_get_wysiwyg_allowed_view_modes($fake_file);

	// Create options for the form dropdown.
	$image_view_modes = array();
	foreach ($view_modes as $view_mode_id => $view_mode_info) {
		$image_view_modes[$view_mode_id] = $view_mode_info['label'];
	}

	// http://www.drupalcontrib.org/api/drupal/contributions!media!includes!media.variables.inc/function/media_variable_get/7
	$form['wysiwyg_default_view_mode'] = array(
		'#type' => 'select',
		'#options' => $image_view_modes,
		'#title' => t('Default image style'),
		'#description' => t('Choose the image style used when images are added to the WYSIWYG editor. This will decide of the image <strong>physical maximum dimensions</strong>.'),
		'#default_value' => media_variable_get('wysiwyg_default_view_mode')
	);
	$form['eatlas_maximum_image_width'] = array(
		'#type' => 'textfield',
		'#title' => t('Maximum image width'),
		'#description' => t('Choose the image maximum default width. This value can be changed by the user using <strong>image properties</strong>. Set it to nothing to allow the image to use its natural width.'),
		'#default_value' => media_variable_get('eatlas_maximum_image_width')
	);
	$form['eatlas_maximum_image_height'] = array(
		'#type' => 'textfield',
		'#title' => t('Maximum image height'),
		'#description' => t('Choose the image maximum default height. This value can be changed by the user using <strong>image properties</strong>. Set it to nothing to allow the image to use its natural height.'),
		'#default_value' => media_variable_get('eatlas_maximum_image_height')
	);

	// If we were using drupal variables instead of media_variables,
	// we could use the following line instead of defining the buttons
	// and a "submit" method.
	//   return system_settings_form($form);

	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save')
	);

	return $form;
}

function _eatlas_media_fixes_settings_validate($form, &$form_state) {
	$eatlas_maximum_image_width = $form_state['values']['eatlas_maximum_image_width'];
	if ($eatlas_maximum_image_width !== '') {
		if (!is_numeric($eatlas_maximum_image_width)) {
			form_set_error('eatlas_maximum_image_width', t('You must enter an integer for the maximum image width.'));
		} elseif ($eatlas_maximum_image_width <= 0) {
			form_set_error('eatlas_maximum_image_width', t('Maximum image width must be positive.'));
		}
	}

	$eatlas_maximum_image_height = $form_state['values']['eatlas_maximum_image_height'];
	if ($eatlas_maximum_image_height !== '') {
		if (!is_numeric($eatlas_maximum_image_height)) {
			form_set_error('eatlas_maximum_image_height', t('You must enter an integer for the maximum image height.'));
		} elseif ($eatlas_maximum_image_height <= 0) {
			form_set_error('eatlas_maximum_image_height', t('Maximum image height must be positive.'));
		}
	}
}

function _eatlas_media_fixes_settings_submit($form, &$form_state) {
	// http://www.drupalcontrib.org/api/drupal/contributions!media!includes!media.variables.inc/function/media_variable_set/7
	$wysiwyg_default_view_mode = $form_state['values']['wysiwyg_default_view_mode'];
	if (empty($wysiwyg_default_view_mode)) {
		media_variable_del('wysiwyg_default_view_mode');
	} else {
		media_variable_set('wysiwyg_default_view_mode', $wysiwyg_default_view_mode);
	}

	$eatlas_maximum_image_width = $form_state['values']['eatlas_maximum_image_width'];
	if (empty($eatlas_maximum_image_width)) {
		media_variable_del('eatlas_maximum_image_width');
	} else {
		media_variable_set('eatlas_maximum_image_width', $eatlas_maximum_image_width);
	}

	$eatlas_maximum_image_height = $form_state['values']['eatlas_maximum_image_height'];
	if (empty($eatlas_maximum_image_height)) {
		media_variable_del('eatlas_maximum_image_height');
	} else {
		media_variable_set('eatlas_maximum_image_height', $eatlas_maximum_image_height);
	}
}

?>
