Introduction
============

featherlib is a set of tools for quickly building programs on the Adafruit
Feather ecosystem without sacrificing readability and modularity. It's the
same sort of hardware abstraction layer (or HAL) that I find myself either
copying over or reimplementing in new projects, so I decided to package it
up as a PlatformIO library.

One of the examples that I use regularly is the program for setting the RTC
in an Adalogger using the time from an Ultimate GPS wing::

  // rtcgps is a small sketch that sets an Adalogger's RTC to the 
  // current GPS time. It uses a Feather M0, the Ultimate GPS
  // Featherwing, and the Adalogger Featherwing.
  #include <Arduino.h>
  #include <RTClib.h>
  
  #include <feather/feather.h>
  #include <feather/scheduling.h>
  #include <feather/wing/adalogger.h>
  #include <feather/wing/gps.h>
  
  
  #if defined(FEATHER_M0)
  FeatherM0        board(INPUT, A1);
  #elif defined(FEATHER_M4)
  FeatherM4        board;
  #else
  #error Unknown board.
  #endif
  
  
  // The default GPS constructor uses Serial1 for the
  // connection.
  GPS              gps;
  
  // NB: setting the Adalogger's CS pin to 0 disables the SD card,
  // which isn't used in the sketch and therefore doesn't require an
  // SD card to be inserted.
  Adalogger        logger(0);
  
  
  void
  setup()
  {
          // Start the serial port at 9600 baud but don't wait for a
          // serial connection to continue booting.
          board.setup(9600, false);
  
          // Registering wings allows them to be set up in one pass and
          // allows any update tasks to be started later on.
          registerWing(&gps);
          registerWing(&logger);
  
          if (!initialiseWings()) {
                  // If a wing fails to initialise, a message will be
                  // printed to serial.
                  while (true) ;
          }
  
          // This starts a background thread that runs the update tasks
          // for the featherwings. For example, in this sketch, the GPS
          // needs to be updated in the background. Another scheduler
          // can be used that calls `runWings`, too.
          scheduleWingTasks();
  }
  
  
  void
  loop()
  {
          // rtcSet will be set to true when the GPS is used to set the
          // RTC.
          static bool        rtcSet = false;
          DateTime           dateTime;
  
          // when rtcSet is true, the program will stop.
          while (rtcSet) ; 
  
          if (!gps.getDateTime(dateTime)) {
                  return;
          }
  
          if (!logger.adjustRTC(dateTime)) {
                  Serial.println("Failed to adjust the RTC.");
                  return;
          }
  
          rtcSet = true;
          Serial.println("RTC is set; halting.");
  }

I find this is relatively easy to read; organising the functionality under
a wing is debatable (and arguably makes this not a true HAL) but it seems
to be working out well for the projects I've been using it in.


Overhead
--------

As a test, I've compiled a basic Arduino sketch for the Feather M0::

  #include <Arduino.h>
  
  
  void
  setup()
  {
          Serial.begin(9600);
          while (!Serial) ;
          Serial.println("boot OK");
  }
  
  
  void
  loop()
  {
  
  }

Building this with PlatformIO shows the following sizes::

  Building .pioenvs/adafruit_feather_m0/firmware.bin
  Memory Usage -> http://bit.ly/pio-memory-usage
  DATA:    [=         ]   8.0% (used 2620 bytes from 32768 bytes)
  PROGRAM: [          ]   4.2% (used 10992 bytes from 262144 bytes)

and the equivalent using the featherlib library::

  #include <Arduino.h>
  #include <feather/feather.h>
  
  
  FeatherM0        board;
  
  
  void
  setup()
  {
          board.setup(9600, true);
  
          Serial.println("BOOT OK");
  }
  
  
  void
  loop()
  {
  
  }

yields the following sizes::

  Building .pioenvs/adafruit_feather_m0/firmware.bin
  Memory Usage -> http://bit.ly/pio-memory-usage
  DATA:    [=         ]   8.1% (used 2648 bytes from 32768 bytes)
  PROGRAM: [=         ]   5.2% (used 13568 bytes from 262144 bytes)

The additional program space is taken up by the random number
seeding. It's worse in this case because a fair amount of additional
setup is done, but once more peripherals are added, the tradeoff is
generally useful to me.

As additional examples for the Feather M0:

+-----------+----------------+------------------+---------------------------------+
| Example   | Data (bytes)   | Program (bytes)  | Components (plus Feather)       |
+===========+================+==================+=================================+
| calamity  |  3496 (10.7%)  |  24784 (9.5%)    | OLED                            |
+-----------+----------------+------------------+---------------------------------+
| rtcgps    |  4844 (14.8%)  |  48576 (18.5%)   | Adalogger, GPS                  |
+-----------+----------------+------------------+---------------------------------+
| loraspy   |  5216 (15.9%)  |  48336 (18.4%)   | Adalogger, OLED, RFM95, Trigger |
+-----------+----------------+------------------+---------------------------------+
| lorabcn   |  3832 (11.7%)  |  35136 (13.8%)   | RFM95, Trigger                  |
+-----------+----------------+------------------+---------------------------------+

