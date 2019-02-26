#include <Arduino.h>
#include <Scheduler.h>

#include <feather/feather.h>
#include <feather/scheduling.h>
#include <feather/wing/wing.h>
#include <feather/wing/adalogger.h>
#include <feather/wing/gps.h>
#include <feather/wing/oled.h>

#include <string.h>

#if defined(FEATHER_M0)
FeatherM0	board(INPUT, A1);
#elif defined(FEATHER_M4)
FeatherM4	board;
#else
#error Unknown board.
#endif

static OLED	display;
static GPS	gps;


void
setup()
{
	board.setup(9600, true);

	registerWing(&display);
	registerWing(&gps);
	if (!initialiseWings()) {
		while (1) ;
	}

	display.print(0, "BOOT OK");

	Scheduler.startLoop(runWings);
}


void
loop()
{
	char		buf[20];
	DateTime	dto;

	if (gps.haveFix()) {
		display.iprint(0, "GPS FIX");
	}
	else {
		display.iprint(0, "NO GPS FIX");
	}

	if (clockFormatTime(gps, buf)) {
		display.print(1, buf);
	}

	yieldFor(100);
}
