#include <Arduino.h>

#include <feather/trigger.h>


Trigger::Trigger(unsigned long delta, bool skipFirst)
{
	this->next = 0;
	this->delta = delta;
	if (skipFirst) {
		this->next = millis() + delta;
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
	if (this->next < now) {
		this->next = now + this->delta;
		return true;
	}

	return false;
}
