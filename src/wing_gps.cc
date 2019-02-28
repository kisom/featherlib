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


bool	
GPS::position(Position &pos)
{
	if (!this->gps.fix) {
		return false;
	}

	pos.latitude = gps.latitude;
	pos.longitude = gps.longitude;
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
