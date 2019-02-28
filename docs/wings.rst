Featherwings and Peripherals
============================

Support for peripherals (e.g. Featherwings or the RFM95 radio on the
radio-enabled Feathers) is done using the appropriate header under
``feather/wing``. Generally, there are four steps to setting up wings:

* Define all the wings as global variables to make them available
  throughout the code.
* Register the wings using ``registerWing``.
* Call ``initialiseWings`` to run the wings' setup functions. If any
  of these fails, they will print a message about the fault to the
  serial console and booting will halt.
* Regularly run ``runWings``; support for the Arduino SAMD scheduler
  is provided using ``scheduleWingTasks``.


The ``FeatherWing`` base class
------------------------------

Every supported peripheral is an instance of the ``FeatherWing`` class. They
provide three functions:

* ``bool setup()`` runs any setup tasks; if setup fails, this will return
  false and a message about the fault is printed to the serial console.
* ``void task()`` runs regular update tasks. For example, a GPS needs to
  regularly update itself to check for new data. These are written with
  the intent that they can be used in a cooperative scheduler; they won't
  take over and block execution.
* ``const char *name()`` returns the name of the FeatherWing.

The ``void registerWing(FeatherWing &)`` function, included in ``feather/wing/wing.h``,
will add the FeatherWing to the global registry. This registry is used for
setting up the wings later on and for running update tasks.

Once the wings are all registered, ``bool initialiseWings()`` should be
called to run the setup function on all the wings, called in the order
they are registered. If any of the setup tasks fails, this will return
false. The intent is to call something like the following in the ``setup``
function::

  if (!initialiseWings()) {
          Serial.println("BOOT FAILED");
          while (true) ;
  }



Finally, near the end of the ``setup`` function, ``void scheduleWingTasks()``
should be called - this will use the Arduino scheduler to run the wing
update tasks in the background. Alternately, the function ``runWings()`` can
be called regularly, e.g. in the main loop so long as there aren't long
delays. It may also be used with another scheduler or task management system;
wing tasks are designed to be cooperative and each run of the function will
run through the update tasks once. For schedulers that don't treat tasks as
``loop`` equivalents, a wrapper function should be used, such as::

  void
  wingThread()
  {
          while (true) {
                  runWings();
                  yield();
          }
  }

The ``Clock`` abstract base class
---------------------------------

Another base class is implemented in ``feather/wing/wing.h`` is ``Clock``,
which is meant to be used in defining realtime clocks (RTCs). A ``Clock``
provides two functions:

* ``bool isClockReady()`` should return true if the clock has a valid time.
* ``bool getDateTime(DateTime &dateTime)`` will return false if the clock
  isn't ready or if an error getting the time occurs. Otherwise, the
  ``DateTime`` instance (this type is defined in `RTClib <https://platformio.org/lib/show/83/RTClib>`__)
  will be filled in with the current time from the ``Clock``.

A helper function is also provided in ``feather/wing/wing.h`` for use with
a ``Clock``: ``bool clockFormatTime(Clock &clock, char *buf)`` wraps
``getDateTime``, and if successful, fills ``buf`` with the time formatted
as YYYY-MM-DD hh:mm:ss. The buffer must be large enough to support this,
which is a minimum of 19 bytes.

