#ifndef __FEATHERLIB_FEATHER_M4_H
#define __FEATHERLIB_FEATHER_M4_H


#include <Arduino.h>
#include <stdint.h>

#include <feather/board.h>


#if !defined(ADAFRUIT_FEATHER_M4_EXPRESS)
#error Attempting to load board support for the wrong board.
#endif


// FeatherM0 supports the Feather M0 family of boards.
class FeatherM4 : Board {
public:
	FeatherM4() : trngReady(false) {};

	double		voltage();
	void		setup(int baudrate, bool wait);
	uint32_t	random();
	void		seed();
private:
	bool		trngReady;
};


#endif // __FEATHERLIB_FEATHER_M4_H