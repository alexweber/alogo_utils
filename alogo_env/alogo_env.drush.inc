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
      return 'Switches website environment between development, staging and production mode.';
  }
}

/**
 * Implements hook_drush_command().
 */
function alogo_env_drush_command() {
  return array(
    'env' => array(
      'callback' => '_alogo_env_drush_env',
      'description' => "Switches website environment between development, staging and production mode. Specify the environment as an argument: press 'd' for development, 's' for staging or 'p' for production. If you type '?' or leave out the argument the function will inform what is the current environment.",
      'arguments' => array(
        'env' => "Optional. Specify the environment: press 'd' for development, 's' for staging or 'p' for production. If you type '?' or leave out the argument the function will inform what is the current environment.",
      ),
      'examples' => array(
        'drush env d' => 'Put the site in development mode',
        'drush env s' => 'Put the site in staging mode',
        'drush env t' => 'Put the site in production mode',
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
function _alogo_env_drush_env($env = NULL) {
  $modules = array(
    'dev' => array(
//      'bulk_export',
      'devel',
      'devel_generate',
//      'devel_node_access',
      'context_ui',
      'imagecache_ui',
      'filter_perms',
      'module_filter',
//      'panels_ipe',
//      'spaces_ui',
      'views_ui',
    ),
    'prod' => array(
      'advagg_bundler',
      'advagg_js_cdn',
      'advagg_js_compress',
      'advagg_css_compress',
      'advagg',
      'boost',
//      'headjs',
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
      // AdvAgg settings
      'advagg_aggregate_mode' => 2,
      'advagg_async_generation' => 1,
      'advagg_async_socket_connect' => 1,
      'advagg_bundler_active' => 1,
      'advagg_bundler_max_css' => 4,
      'advagg_bundler_max_js' => 4,
      'advagg_closure' => 1,
      'advagg_css_compressor' => 1,
      'advagg_css_compress_agg_files' => 1,
      'advagg_css_compress_compressor_level' => 'safe',
      'advagg_css_compress_inline' => 1,
      'advagg_dir_htaccess' => 0,
      'advagg_enabled' => 1,
      'advagg_gzip_compression' => 1,
//      'advagg_js_compressor' => 0,
      'advagg_js_compress_agg_files' => 1,
      'advagg_js_compress_inline' => 1,
      'advagg_js_compress_packer_enable' => 0,
      'advagg_page_cache_mode' => 1,
      'advagg_rebuild_on_flush' => 0,
      'block_cache' => 1,
      // Boost settings
      'boost_aggressive_cookie' => 1,
      'boost_aggressive_gzip' => 1,
      'boost_apache_etag' => 2,
      'boost_apache_rfc2616' => 1,
      'boost_apache_xheader' => 0,
      'boost_asynchronous_output' => 1,
      'boost_cacheability_option' => 0,
      'boost_cacheability_pages' => 0,
      'boost_cache_css' => 1,
      'boost_cache_html' => 1,
      'boost_cache_js' => 1,
      'boost_cache_json' => 1,
      'boost_cache_json_lifetime' => 1800,
      'boost_cache_lifetime' => 1800,
      'boost_cache_query' => 1,
      'boost_cache_url_alais_src' => 1,
      'boost_cache_xml' => 1,
      'boost_cache_xml_lifetime' => 1800,
      'boost_check_before_cron_expire' => 0,
      'boost_clear_cache_offline' => 1,
      'boost_crawl_on_cron' => 1,
      'boost_crawl_url_alias' => 0,
      'boost_disable_clean_url' => 0,
      'boost_document_root' => "%{DOCUMENT_ROOT}",
      'boost_enabled' => 1,
      'boost_expire_cron' => 1,
      'boost_expire_no_flush' => 0,
      'boost_flush_all_multisite' => 0,
      'boost_flush_cck_references' => 1,
      'boost_flush_dir' => 0,
      'boost_flush_front' => 1,
      'boost_flush_menu_items' => 1,
      'boost_flush_node_terms' => 1,
      'boost_flush_views' => 1,
      'boost_flush_views_insert' => 1,
      'boost_halt_on_errors' => 1,
      'boost_halt_on_messages' => 1,
      'boost_ignore_flush' => 1,
      'boost_ignore_htaccess_warning' => 0,
      'boost_ignore_subdir_limit' => 1,
      'boost_loopback_bypass' => 1,
      'boost_multisite_single_db' => 0,
      'boost_no_database' => 0,
      'boost_only_ascii_path' => 1,
      'boost_overwrite_file' => 0,
      'boost_permissions_dir' => 0,
      'boost_permissions_file' => 0,
      'boost_push_html' => 1,
      'boost_push_json' => 1,
      'boost_push_xml' => 1,
      'boost_server_name_http_host' => "%{SERVER_NAME}",
      'boost_verbose' => 1,
      // Other settings
      'block_cache' => 1,
      'devel_error_handler' => 0,
      'devel_rebuild_theme_registry' => 0,
      'error_level' => 0,
      'page_compression' => 1,
    ),
  );
  
  // if Boost is disabled, enable standard Drupal cache variables for production mode
  if (!function_exists('boost_menu')) {
    $variables['prod']['preprocess_css'] = 1;
    $variables['prod']['preprocess_js'] = 1;
    $variables['prod']['cache'] = 1;
  }

  switch ($env) {
    case 'd':
      $return = _alogo_env_development($modules, $variables);
      drush_log('Environment set to: Development', 'ok');
      $flush = TRUE;
      break;
    case 's':
      $return = _alogo_env_staging($modules, $variables);
      drush_log('Environment set to: Staging', 'ok');
      $flush = TRUE;
      break;
    case 'p':
      $return = _alogo_env_production($modules, $variables);
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
    // And again
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
 * @param array $variables
 * @return bool
 */
function _alogo_env_production($modules, $variables) {
  // enable/disable modules
  foreach ($modules as $env => $module) {
    if ($env === 'dev') {
      if (module_exists($module)) {
        module_disable($module);
      }
    }
    else {
      if (module_exists($module)) {
        module_enable($module);
      }
    }
  }

  // set variables
  foreach ($variables as $env => $var) {
    if ($env === 'prod') {
      foreach ($var as $name => $value) {
        variable_set($name, $value);
      }
    }
  }

  variable_set('alogo_env', 'production');
}

/**
 * Puts the website in staging mode
 *
 * @param array $modules
 * @param array $variables
 * @return bool
 */
function _alogo_env_staging($modules, $variables) {
  // @TODO do something unique in staging environment
  $return = _alogo_env_development($modules);
  variable_set('alogo_env', 'staging');
  return $return;
}

/**
 * Puts the website in development mode
 *
 * @param array $modules
 * @param array $variables
 * @return bool
 */
function _alogo_env_development($modules, $variables) {
  // enable/disable modules
  foreach ($modules as $env => $list) {
    if ($env === 'dev') {
      if (module_exists($module)) {
        module_enable($list);
      }
    }
    else {
      if (module_exists($module)) {
        module_disable($list);
      }
    }
  }

  // set variables
  foreach ($variables as $env => $var) {
    if ($env === 'dev') {
      foreach ($var as $name => $value) {
        variable_set($name, $value);
      }
    }
  }
  
  variable_set('alogo_env', 'development');
}