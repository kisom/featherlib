#ifndef __FEATHER_BUTTONS_H
#define __FEATHER_BUTTONS_H


#include <Arduino.h>
#include <stdint.h>

namespace featherlib {


typedef void (*button_callback)();


class Button {
public:
	Button(uint8_t pin) : pin(pin),
			      lastValue(0),
			      value(0),
			      lastSample(0),
			      cb(nullptr)
	{
		pinMode(pin, INPUT_PULLUP);
	};
	uint8_t	read();			// Return the button's current value.
	bool	sample();		// Take another reading of the button.
	void	registerCallback(button_callback);
private:
	uint8_t		pin;		// Which pin is the button on?
	uint8_t		lastValue;	// What was the last sampled value?
	uint8_t		value;		// What is the last known value?
	unsigned long	lastSample;	// When was the last sample taken?
	button_callback	cb;		// What happens when the state changes?
};


} // namespace featherlib
#endif // __FEATHER_BUTTONS_H