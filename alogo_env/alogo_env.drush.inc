<?php

/**
 * @file Alogo Env Module Drush Hooks
 */

/**
 * Implements hook_drush_help().
 */
function alogo_env_drush_help($section) {
  switch ($section) {
    case 'env':
      return t('Switches website environment between development, staging and production mode.');
  }
}

/**
 * Implements hook_drush_command().
 */
function alogo_env_drush_command() {
  return array(
    'env' => array(
      'callback' => '_alogo_env_drush_env',
      'description' => t("Switches website environment between development, staging and production mode. Specify the environment as an argument: press 'd' for development, 's' for staging or 'p' for production. If you type '?' or leave out the argument the function will inform what is the current environment."),
      'aliases' => array('es'),
      'arguments' => array(
        'env' => t("Optional. Specify the environment: press 'd' for development, 's' for staging or 'p' for production. If you type '?' or leave out the argument the function will inform what is the current environment."),
      ),
      'examples' => array(
        'drush env d' => t('Put the site in development mode'),
        'drush env s' => t('Put the site in staging mode'),
        'drush env t' => t('Put the site in production mode'),
      ),
    ),
  );
}

/*
 * Callbacks used in hook_drush_command
 */

/**
 * Router for 'env' drush command
 *
 * @param string $env
 * @return bool
 */
function _alogo_env_drush_env($env) {
  $modules = array(
    'dev' => array(
      'bulk_export',
      'devel',
      'devel_generate',
      'devel_node_access',
      'context_ui',
      'imagecache_ui',
      'panels_ipe',
      'spaces_ui',
      'views_ui',
    ),
    'prod' => array(
      'advagg_bundler',
      'advagg_js_cdn',
      'advagg_js_compress',
      'advagg_css_compress',
      'advagg',
      'boost',
      'headjs',
      'path_alias_cache',
    ),
  );

  $variables = array(
    'dev' => array(
      'block_cache' => 0,
      'cache' => 0,
      'devel_error_handler' => 1,
//      'devel_rebuild_theme_registry' => 1,
      'error_level' => 1,
      'page_compression' => 0,
      'preprocess_css' => 0,
      'preprocess_js' => 0,
    ),
    'prod' => array(
      'advagg_js_compress_agg_files' => 1,
      'advagg_js_compress_inline' => 1,
      'advagg_css_compress_agg_files' => 1,
      'advagg_css_compress_inline' => 1,
      'advagg_css_compressor' => 1,
      'advagg_css_compress_compressor_level' => 'sane',
      'advagg_bundler_active' => 1,
      'advagg_gzip_compression' => 1,
      'block_cache' => 1,
//      'cache' => 1,
      'devel_error_handler' => 0,
      'devel_rebuild_theme_registry' => 0,
      'error_level' => 0,
//      'page_compression' => 1,
//      'preprocess_css' => 1,
//      'preprocess_js' => 1,
    ),
  );

  switch ($env) {
    case 'd':
      $return = _alogo_env_development($modules);
      drush_log('Environment set to: Development', 'ok');
      $flush = TRUE;
      break;
    case 's':
      $return = _alogo_env_staging($modules);
      drush_log('Environment set to: Staging', 'ok');
      $flush = TRUE;
      break;
    case 'p':
      $return = _alogo_env_production($modules);
      drush_log('Environment set to: Production', 'ok');
      $flush = TRUE;
      break;
    default:
      $env = variable_get('alogo_env', '-undefined-');
      drush_log('Current environment is: ' . $env, 'ok');
      $flush = FALSE;
      $return = TRUE;
  }

  if ($flush) {
    // Flush all caches; no need to re-implement this.
    drush_cache_clear('all');
  }

  return $return;
}

/*
 * Auxiliary functions
 */

/**
 * Puts the website in production mode
 *
 * @param array $modules
 * @return bool
 */
function _alogo_env_production($modules) {
  // enable/disable modules
  foreach ($modules as $env => $list) {
    if ($env === 'dev') {
      module_disable($list);
    }
    else {
      module_enable($list);
    }
  }

  variable_set('alogo_env', 'production');
}

/**
 * Puts the website in staging mode
 *
 * @param array $modules
 * @return bool
 */
function _alogo_env_staging($modules) {
  // @TODO do something unique in staging environment
  $return = _alogo_env_development($modules);
  variable_set('alogo_env', 'staging');
  return $return;
}

/**
 * Puts the website in development mode
 *
 * @param array $modules
 * @return bool
 */
function _alogo_env_development($modules) {
  // enable/disable modules
  foreach ($modules as $env => $list) {
    if ($env === 'dev') {
      module_enable($list);
    }
    else {
      module_disable($list);
    }
  }

  variable_set('alogo_env', 'development');
}