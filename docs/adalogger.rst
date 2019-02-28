Adalogger
---------

The Adalogger is a Featherwing with a PCF8523 RTC and a microSD card slot.

* Header: ``feather/wing/adalogger.h``
* Link: `Adalogger RTC + SD <https://www.adafruit.com/product/2922>`__
* Update task: nothing is done

The ``Adalogger`` is instantiated with one of two constructors:

* ``Adalogger()`` is a wrapper for ``Adalogger(10)``, and sets up the
  Featherwing with support for the onboard RTC and SD.
* ``Adalogger(uint8_t cs)`` sets up the Featherwing with an alternate
  SD CS pin if the default has been changed. Alternatively, using a
  CS pin of 0 will disable SD card support.

The ``setup`` method doesn't check whether the RTC has a valid date and
time; this is provided by other functions.

Note: if SD support is enabled, the card must be inserted and ready by the
time ``setup()`` is called. There isn't support for hotswapping SD cards
right now.

SD support is provided by the `SdFat` external library; only FAT support is
provided at this time.

The ``Adalogger`` class provides the following methods for interacting
with the SD card:

* ``File openFile(const char *path, bool write)`` opens a file; the ``File``
  type is provided by the `SdFat <https://platformio.org/lib/show/322/SdFat>`__
  library. You don't need to include anything extra if you're not using
  the SdFat library anywhere else.
* ``bool exists(const char *path)`` returns true if the file or directory
  named by ``path`` exists on the SD card.
* ``bool remove(const char *path)`` returns true if the file named by ``path``
  was successfully removed.
* ``bool mkdir(const char *path)`` returns true if the directory named by
  ``path`` was successfully created.

This class is also an instance of the ``Clock`` class; in addition to the
standard ``Clock`` methods, it has ``void adjustRTC(DateTime &dateTime)``
to set the date and time in the RTC.
