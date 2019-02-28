OLED Featherwing
----------------

* Header: ``feather/wing/oled.h``
* Link: `FeatherWing OLED <https://www.adafruit.com/product/2900>`__
* Update task: sample the buttons

The ``OLED`` class is instantiated with one of two constructors:

* The default constructor ``OLED()`` is a wrapper around
  ``OLED(9, 6, 5)``, and sets up the Featherwing with the default
  pin mappings.
* The ``OLED(uint8_t a, uint8_t b, uint8_t c)`` allows overriding
  the button pin assignments. If a button's pin is set to 0, that
  button will be disabled.

The ``setup`` method will do the necessary work to set up the OLED
and clear the display; the update ``task`` will regularly check and
update the buttons.

Graphics being a complex thing, this class has a lot of methods that
broadly fall into three categories: graphics primitives, text display,
and button handling.

Graphics primitives
^^^^^^^^^^^^^^^^^^^

Note: ``clear`` and ``show`` are the only functions in this group that
immediately affect the display. For the sake of efficiency, the other
functions write to a backing buffer that is sent to the display when
``show`` is called. The *x* values must be less than the constant 
``OLED::WIDTH`` and the *y* values must be less than the constant
``OLED::HEIGHT`` - these are currently 128 and 32, respectively.

* ``void clear()`` will clear both the display and the backing buffer.
* ``void pixel(uint16_t x, uint16_t y)`` draws a pixel at the x,
  y coordinates.
* ``void clearPixel(uint16_t x, uint16_t y)`` unsets the pixel at the
  x, y coordinates.
* ``void circle(uint16_t x, uint16_t y, uint16_t r, bool fill)`` draws
  a circle whose origin is at (*x*, *y*) and whose radius is *r*. If
  ``fill`` is true, the circle will be filled in, otherwise it will be
  just the outline.
* `void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)`` draws
  a line from (*x0*, *y0*) to (*x1*, *y1*).
* ``void show()`` sends the graphics buffer to the display.


Text display
^^^^^^^^^^^^

For printing text, this display supports three lines of 20 characters. The
line is indexed starting from 0. The text display functions take effect
immediately; there is no need to call ``show`` after calling these. Note
that using these functions will clear any drawing that has been done. Calling
``clear`` will also erase the text from the display, but will preserve the
text buffers so that the next call to one of these methods will restore any
previously printed text.

* ``void clearText()`` will clear all the text from the display and reset
  the text buffers.
* ``void print(uint8_t line, const char *text)`` prints normal text on
  the normal line.
* ``void iprint(uint8_t line, const char *text)`` prints inverse text
  on the line.
* ``void clearLine(uint8_t line)`` clears the text for the given line.


Button handling
^^^^^^^^^^^^^^^^

The OLED Featherwing has three buttons that are, by default, on pins
9, 6, and 5. The three buttons are called A, B, and C in the Adafruit
docs, and are indexed starting from 0: button A, the topmost button,
is at index 0 and button C, the bottom button, is at index 2. The buttons
will be setup in the ``INPUT_PULLUP`` mode during setup. Note that pin 9
conflicts with the voltage divider on the Feather M0; this is handled
by this library so that both can coexist. Buttons can be disabled by
explicitly passing a 0 pin value to the full constructor, in which case
they won't be setup in the ``INPUT_PULLUP`` mode.

* ``void sample()`` will check the buttons for updates. This is called
  in the display's update ``task``.
* ``void registerCallback(uint8_t button, void (*callback)())`` registers
  a function to be called when a button is pressed.
* ``void unregisterCallback(uint8_t button)`` clears the callback for the
  given button.
* ``void unregisterAllCallbacks()`` clears the callbacks for all buttons.

There is an example of using buttons in ``examples/calamity``.
