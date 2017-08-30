<?php
/**
 * @file
 * Contains a Drupal page cache backend for use with Acquia's GeoIP service.
 *
 * Extends the core DrupalDatabaseCache class.
 */

/**
 * Extends the core database cache to factor in the GeoIP country value.
 *
 * Heavily inspired by cookie_aware_page_cache.
 *
 * @link https://www.drupal.org/project/cookie_aware_page_cache
 */
class GeoIPPageCache extends DrupalDatabaseCache implements DrupalCacheInterface {

  /**
   * Returns the current GeoIP country code or FALSE.
   *
   * @return string|bool
   *   ISO code of current country or FALSE.
   */
  protected function getCountry() {
    $country = FALSE;

    if (isset($_SERVER['HTTP_X_GEO_COUNTRY']) && !empty($_SERVER['HTTP_X_GEO_COUNTRY'])) {
      $country = $_SERVER['HTTP_X_GEO_COUNTRY'];
    }

    return $country;
  }

  /**
   * Alter the CID to include the values we need.
   */
  protected function prepareCid($cid) {
    // Make sure we only alter the CID for the page cache.
    if ($this->bin === 'cache_page') {
      // Grab the country ISO code.
      $country = $this->getCountry();
      $cid = $cid . ':' . ($country ? $country : 'XX');
    }

    return $cid;
  }

  /**
   * Alter the CID on get.
   */
  public function get($cid) {
    $cid = $this->prepareCid($cid);
    return parent::get($cid);
  }

  /**
   * Alter the CID on set.
   */
  public function set($cid, $data, $expire = CACHE_PERMANENT) {
    $cid = $this->prepareCid($cid);
    parent::set($cid, $data, $expire);
  }

  /**
   * Clear correct altered CID.
   */
  public function clear($cid = NULL, $wildcard = FALSE) {
    // Make sure we clear all region hashes for this ID.
    if ($this->bin === 'cache_page') {
      $wildcard = TRUE;
    }

    parent::clear($cid, $wildcard);
  }
}
