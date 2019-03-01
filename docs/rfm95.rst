RFM95 support
-------------

* Header: ``feather/wing/rfm95.h``
* Link (Featherwing): `RFM95W 900 MHz Radiofruit <https://www.adafruit.com/product/3231>`__
* Link (Feather M0 with RFM95): `Adafruit Feather M0 with RFM95 LoRa Radio - 900MHz <https://www.adafruit.com/product/3178>`__
* Update task: nothing is done

The ``RFM95`` class is used both for the Featherwing and the onboard
radio. There are a few defines that can be overridden, which should
be done in the ``platformio.ini`` config. These default to valid values
for the Feather M0 with RFM95 for use in the US.

* ``LORA_FREQ`` defaults to ``915.0``, which is valid in the US.
* ``RFM95_CS`` defaults to ``8``.
* ``RFM95_RST`` defaults to ``4``.
* ``RFM95_INT`` (which is the radio interrupt or IRQ pin) defaults to ``3``.

The wiring instructions for the Featherwing are on 
`Adafruit's site <https://learn.adafruit.com/radio-featherwing/wiring>`__.

There are two constructors:

* ``RFM95()`` uses the values from the three ``RFM95_`` defines above.
* ``RFM95(uint8_t cs, uint8_t irq, uint8_t rst)`` allows setting the
  pins explicitly.

The ``setup`` method will initialise the radio, set it to the appropriate
frequency, and set it to maximum transmit power. The transmit power can be
set using the ``setPower`` method, described below.

The class provides the following methods:

* ``bool available()`` returns true if the radio has received data.
* ``void setPower(uint8_t)`` changes the transmit power. Valid values
  are in the range 5 to 23, inclusive, with higher values providing
  more transmit power. As per the docs, this uses the ``PA_BOOST`` pin
  to provide higher transmit power.
* ``void transmit(uint8_t *buf, uint8_t len, bool blocking)`` sends
  the message contained in ``buf``; if ``blocking`` is true, the method
  will block until transmission is complete.
* ``bool receive(uint8_t *buf, uint8_t *len, int16_t *rssi)`` returns true
  if a message is available. ``buf`` should have at least 251 bytes available,
  which is the maximum message length for an RFM95 message. If ``rssi`` is
  not NULL, it will be set to the received signal strength. The message length
  will be returned via ``len``, which must be set to the size of ``buf`` before
  being passed to this method.

