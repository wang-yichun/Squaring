### v3.3.1 [view commit logs](https://github.com/soomla/android-store/compare/v3.3.0...v3.3.1)

* New Features
  * Added the option to overwrite an object in StoreInfo and save it.

* Fixes
  * Enforce providing a SOOM_SEC in obfuscator.
  * If the purchasable item is NonConsumableItem and it already exists then we don't fire any events.

* Optimizations
  * Added build phase to create multiple platform static lib.

### v3.3.0 [view commit logs](https://github.com/soomla/android-store/compare/v3.2.2...v3.3.0)

* New Features
  * ios-store will now refresh details of market items on initialization.
  * Added the option to fetch prices from the app store.
  * Added the receipt of a successful purchase to EVENT_APPSTORE_PURCHASED's userInfo.

* Optimizations
  * Fixed Names of objects and events so they match in all SOOMLA plugins.
