#ifndef __FEATHERLIB_WING_GPS_H
#define __FEATHERLIB_WING_GPS_H


#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <RTClib.h>
#include <feather/wing/wing.h>


// Time is a basic timestamp to simplify serialisation.
typedef struct {
	uint16_t	year;
	uint8_t		month;
	uint8_t 	day;
	uint8_t		hour;
	uint8_t		minute;
	uint8_t		second;
} Time;

typedef struct {
	uint8_t	quality;
	uint8_t	satellites;
} Fix;

typedef struct {
	float	latitude;
	float	longitude;
	Time	timestamp;
	Fix	fix;
} Position;


class GPS : public FeatherWing, public Clock {
public:
	GPS() : gps(&Serial1), fix(false) {};
	GPS(HardwareSerial *ser) : gps(ser), fix(false) {};

	bool	setup();
	void	task();

	bool	haveFix();
	bool	position(Position &pos);
	void	dump();

	bool	isClockReady();
	bool	getDateTime(DateTime &dto);


	const char	*name() { return "GPS"; }
private:
	Adafruit_GPS	gps;
	bool		fix;
};


#endif // __FEATHERLIB_WING_GPS_H
