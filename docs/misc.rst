Miscellaneous functions
=======================

There are few additional utility functions provided that don't fall
under direct hardware support, but that I find myself using often.


Scheduling
----------

If ``feather/scheduling.h`` is included, the following functions are
available:

* ``void yieldFor(unsigned long ms)`` will yield for at least ``ms``
  milliseconds. It acts like a cooperative delay.
* ``void startThread(void (*thread)())`` will launch ``thread`` as
  a background task using the Arduino scheduler.


Triggers
--------

Including ``feather/trigger.h`` makes the ``Trigger`` class available. This
class is constructed with a millisecond delta, and its ``ready`` method will
return true if at least that long has passed since the last call to ``ready``.
By default, it will be ready immediately; if a second optional true argument
is passed to the constructor, it will require waiting ``delta`` milliseconds
before being ready for the first time.

The ``ready`` method has two forms:

* ``bool ready()`` calls ``ready(millis())``.
* ``bool ready(unsigned long now)`` allows the same ``millis`` value to be
  reused in multiple places to avoid calling the function multiple
  times. When the allotted time is up, the trigger will reset to the last
  update time plus the delta.

Finally, there is a ``reset`` method:

* ``void reset()``  calls ``reset(millis())``.
* ``void reset(unsigned long now)`` resets the trigger to fire next in
  ``now`` + ``delta`` milliseconds.


Util
----

The ``feather/util.h`` contains functions that don't really fit elsewhere:

* ``void swap_u8(uint8_t &a, uint8_t &b)`` will swap its arguments.
* ``void swap_ul(unsigned long &a, unsigned long &b)`` will swap its arguments.
