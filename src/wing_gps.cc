#include <Arduino.h>
#include <Adafruit_GPS.h>

#include <feather/wing/wing.h>
#include <feather/wing/gps.h>


bool	
GPS::setup()
{
	gps.begin(GPS_BAUDRATE);
	gps.sendCommand(GPS_MODE);
	gps.sendCommand(GPS_UPDATE_FREQ);
#ifndef GPS_NO_ANTENNA_UPDATES
	gps.sendCommand(PGCMD_ANTENNA);
#endif // GPS_NO_ANTENNA_UPDATES
	delay(500);
	return true;
}


void	
GPS::task()
{
	this->gps.read();
	if (this->gps.newNMEAreceived()) {
		this->gps.parse(this->gps.lastNMEA());
	}

	if (gps.fix && !this->fix) {
		Serial.println("GPS FIX ACQUIRED");
		this->fix = true;
	}
	else if (!gps.fix && this->fix) {
		Serial.println("GPS FIX LOST");
		this->fix = false;
	}
}


bool	
GPS::haveFix()
{
	return this->gps.fix;
}


float
convert_reading(float reading)
{
	float	base, converted, sec;
	int16_t deg, min;

	base = trunc(reading);
	deg = static_cast<int16_t>(base) / 100;
	min = static_cast<int16_t>(base) % 100;
	sec = static_cast<float>(reading) - trunc(reading);

	sec *= 0.027777777; // * 100 / 3600
	converted = min;
	converted /= 60;
	converted += deg;
	converted += sec;
	return converted;
}


bool	
GPS::position(Position &pos)
{
	if (!this->gps.fix) {
		return false;
	}

	pos.latitude = convert_reading(gps.latitude);
	pos.longitude = convert_reading(gps.longitude);
	pos.timestamp.year = gps.year + 2000;
	pos.timestamp.month = gps.month;
	pos.timestamp.day = gps.day;
	pos.timestamp.hour = gps.hour;
	pos.timestamp.minute = gps.minute;
	pos.timestamp.second = gps.seconds;
	pos.fix.quality = gps.fixquality;
	pos.fix.satellites = gps.satellites;

	return true;	
}


void
GPS::dump()
{
	while (true) {
		char	ch = this->gps.read();
		Serial.print(ch);
	}
}


bool	
GPS::isClockReady()
{
	return this->gps.year > 18;
}


bool	
GPS::getDateTime(DateTime &dto)
{
	Position	pos;

	if (!this->position(pos)) {
		return false;
	}

	dto = DateTime(pos.timestamp.year, pos.timestamp.month,
	               pos.timestamp.day, pos.timestamp.hour,
	               pos.timestamp.minute, pos.timestamp.second);
	return true;
}
