#include <Arduino.h>

#include <feather/trigger.h>


Trigger::Trigger(unsigned long delta, bool skipFirst)
{
	this->start = 0;
	this->delta = delta;
	if (skipFirst) {
		this->start = millis() + delta;
	}
}


bool
Trigger::ready()
{
	return this->ready(millis());
}


bool
Trigger::ready(unsigned long now)
{
	if (now - this->start > this->delta) {
		this->start = now;
		return true;
	}

	return false;
}


void
Trigger::reset()
{
	this->reset(millis());
}


void
Trigger::reset(unsigned long now)
{
	this->start = now;
}
