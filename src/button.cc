#include <Arduino.h>
#include <feather/button.h>
#include <feather/util.h>


namespace featherlib {


const unsigned long debounceDelay = 50;


uint8_t
Button::read()
{
	return this->value;
}


bool
Button::sample()
{
	uint8_t		reading = digitalRead(this->pin);
	unsigned long	sampledAt = millis();

	if (reading != this->value) {
		return false;
	}

	if (this->lastSample == 0) {
		this->lastSample = sampledAt;
		this->lastValue = reading;
		return false;
	}

	unsigned long lastSample = this->lastSample;
	if (sampledAt < this->lastSample) {
		swap_ul(sampledAt, lastSample);
	}

	if ((sampledAt - lastSample) > debounceDelay) {
		this->value = !this->value;
		this->lastSample = 0;
		if (this->cb && this->value) {
			this->cb();
		}
		return true;
	}

	return false;
}


void
Button::registerCallback(button_callback cb)
{
	this->cb = cb;
}


} // namespace hal