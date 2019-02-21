#include <Arduino.h>
#include <Scheduler.h>

#include <feather/feather.h>
#include <feather/scheduling.h>
#include <feather/wing/wing.h>
#include <feather/wing/adalogger.h>
#include <feather/wing/gps.h>

#include <string.h>

#if defined(FEATHER_M0)
FeatherM0	board(INPUT, A1);
#elif defined(FEATHER_M4)
FeatherM4	board;
#else
#error Unknown board.
#endif

AdaLogger	adalogger;
GPS		gps;


void
setup()
{
	board.setup(9600, true);

	registerWing(&adalogger);
	registerWing(&gps);
	if (!initialiseWings()) {
		while (1) ;
	}

	Serial.println("BOOT OK");

	Scheduler.startLoop(runWings);
}


void
loop()
{
	char		buf[20];
	DateTime	dto;

	if (gps.haveFix()) {
		Serial.println("GPS FIXED");
	}
	else {
		Serial.println("GPS NO FIX");
	}

	if (!adalogger.getDateTime(dto)) {
		Serial.println("RTC not ready");
		if (gps.isClockReady()) {
			adalogger.adjustRTC(dto);
			Serial.println("RTC adjusted from GPS");
		}
	}
	else {
		sprintf(buf, "%04d-%02d-%02d %02d:%0d:%02d", dto.year(),
		        dto.month(), dto.day(), dto.hour(), dto.minute(),
		        dto.second());
		Serial.println(buf);
	}
	yieldFor(1000);
}