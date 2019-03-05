Ultimate GPS Featherwing
------------------------

* Header: ``feather/wing/gps.h``
* Link: `Adafruit Ultimate GPS FeatherWing <https://www.adafruit.com/product/3133>`
* Update task: checking the GPS for new data and updating the fix and position data

The GPS Featherwing is a standard serial-based GPS. It is instantiated using one of
two constructors:

* ``GPS()`` will use ``Serial1`` for communicating with the GPS.
* ``GPS(HardwareSerial *)`` will use the given hardware serial port.

GPS position data is returned using the following structures::

  typedef struct {
          uint16_t        year;
          uint8_t         month;
          uint8_t         day;
          uint8_t         hour;
          uint8_t         minute;
          uint8_t         second;
  } Time;
  
  typedef struct {
          uint8_t quality;
          uint8_t satellites;
  } Fix;
  
  typedef struct {
          float   latitude;
          float   longitude;
          Time    timestamp;
          Fix     fix;
  } Position;

The ``setup`` method will set up the serial connection to the GPS and tell
it to return the standard position data (aka ``RMCGGA``) and to send updates
every second. This can be overriden using the ``GPS_MODE`` and ``GPS_UPDATE_FREQ``
defines, which should be set in ``platformio.ini``. It also expects the GPS to
be communicating at a baudrate of 9600; this can be overridden with the 
``GPS_BAUDRATE`` define.

The ``GPS`` class provides the following methods for working with
position data:

* ``bool haveFix()`` returns true if the GPS has a fix.
* ``bool position(Position &pos)`` returns true if the GPS has a valid fix and
  fills in the ``Position`` struct with the most recent fix data.
* ``void dump()`` will block and echo data from the GPS serial port to the
  serial console. This might be useful for debugging GPS issues.

The ``GPS`` class is also an instance of the ``Clock`` virtual class,
and therefore provides the relevant RTC methods.

Note that the returned GPS coordinates have a precision of six
decimal degrees at most. According to
`this <https://en.wikipedia.org/wiki/Decimal_degrees>` article,
that should be sufficient for fairly precise locations.
