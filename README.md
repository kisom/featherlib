featherlib
==========

This is a set of building blocks for Adafruit's Feather ecosystem. The
goal is to make it easier to deploy and write decent modularised code, and
this library does this by building on top of a number of other libraries.
It isn't intended for firmware that needs to be highly compact or with
strict requirements on memory. This library also doesn't fear using the
STL where it makes sense.


Currently supported Feathers:

+ The Feather M4 express
+ The Feather M0 (the basic and the RFM95 versions have been checked)

Currently supported Featherwings:

+ The Adalogger SD + RTC
+ The Ultimate GPS
+ The OLED display wing
+ RFM95 support (both the Feather M0 with RFM95 and RFM95 Radiowing);
  currently, this is LoRa-only with support for LoRaWAN to come in
  the future.

Next on the TODO list:

+ LoRaWAN support for the RFM95.
