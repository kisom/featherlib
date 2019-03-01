Changelog
=========

This is a list of the release versions of this library.

v0.3.0 - 2019-02-28
-------------------

* Fix subclassing issue with RFM95.
* Support formatting a DateTime object directly.

v0.2.5 - 2019-02-28
-------------------

* Fix Travis CI build.

v0.2.4 - 2019-02-28
-------------------

* Switch to fork of RadioHead library that supports the M4 boards.

v0.2.3 - 2019-02-28
-------------------

* The OLED now supports disabling buttons.
* The GPS supports overriding the default mode, update frequency,
  and baudrate.
* Add docs.

v0.2.2 - 2019-02-26
-------------------

* Fix RadioHead dependency name.
* Remove unused variable from the Feather M4 source.

v0.2.1 - 2019-02-26
-------------------

* Adalogger supports an RTC-only mode.
* Add startThread function so users don't have to think
  about schedulers if it's not a concern.

v0.2.0 - 2019-02-26
-------------------

* Add support for RFM95 LoRa.
* Rename AdaLogger class to Adalogger.

v0.1.0 - 2019-02-25

* Initial release.
* Supported Feathers: M0 (tested against basic and LoRa feathers), M4.
* Supported Featherwings: Adalogger, OLED, Ultimate GPS.
