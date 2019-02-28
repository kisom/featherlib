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
