#ifndef __FEATHERLIB_FEATHER_M0_H
#define __FEATHERLIB_FEATHER_M0_H


#include <Arduino.h>
#include <stdint.h>

#include <feather/board.h>


#if !defined(ARDUINO_SAMD_FEATHER_M0) && !defined(ADAFRUIT_FEATHER_M0)
#error Attempting to load board support for the wrong board.
#endif

#ifndef UNUSED_ANALOG
#define UNUSED_ANALOG	A0
#endif


// FeatherM0 supports the Feather M0 family of boards.
class FeatherM0 : Board {
public:
	FeatherM0() : pin9Mode(INPUT), unusedAnalog(UNUSED_ANALOG) {};
	FeatherM0(int pin9Mode) : pin9Mode(pin9Mode), unusedAnalog(UNUSED_ANALOG) {};
	FeatherM0(int pin9Mode, int unusedAnalog)
	    : pin9Mode(pin9Mode), unusedAnalog(unusedAnalog) {};

	double		voltage();
	void		setup(int baudrate, bool wait);
	uint32_t	random();
	void		seed();
private:
	int		pin9Mode;
	int		unusedAnalog;
};


#endif // __FEATHERLIB_FEATHER_M0_H
