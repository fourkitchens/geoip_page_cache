Description
-----------

Allows Drupal's page cache to work when using Acquia's GeoIP service.


Installation
------------

Configuring the module takes place entirely in your site's settings.php file.

1. Download and unpack the module to your Drupal site.

2. Open your settings.php file for editing.

3. Add GeoIP Page Cache to the list of available cache backends by adding this line:
    ```
    $conf['cache_backends'][] = 'sites/all/modules/geoip_page_cache/GeoIPPageCache.inc';
    ```
    If you placed the module in a directory other than 'sites/all/modules', adjust the line accordingly.

4. Configure the page cache to use GeoIPPageCache:
    ```
    $conf['cache_class_cache_page'] = 'GeoIPPageCache';
    ```

5. Switch on the anonymous page cache in admin/config/development/performance.

6. If you want to use Memcache for page cache bin, first ensure your Acquia environment is configured properly for Memcached: https://docs.acquia.com/acquia-cloud/performance/memcached

7. Then you should use this pair of settings instead of the ones in points 3 & 4:
    ```
    $conf['cache_backends'][] = 'sites/all/modules/geoip_page_cache/GeoIPPageMemcache.inc';
    $conf['cache_class_cache_page'] = 'GeoIPPageMemcache';
    ```
