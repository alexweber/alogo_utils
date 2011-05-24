<?php
/**
 * @file Admin functions for Alogo PNG
 */

/**
 * Admin settings form
 */
function alogo_png_admin() {
  $form = array();
  $form['alogo_png_selectors'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS Classes/Selectors to <em>Include</em>'),
    '#default_value' => variable_get('alogo_png_selectors', "img\n.pngfix"),
    '#description' => t('CSS/jQuery selectors including tag, class, id where to apply the PNG. For example use <code>#alogo_png</code> for ID, <code>.alogo_png</code> for classes, <code>img</code> for tags, and/or <code>#belatedid, .belatedclass, img</code> for combinations. Input one selector per line without comma (try to use the plain text editor instead of the WYSIWYG when editing)')
  );
  return system_settings_form($form);
}