#include <Arduino.h>
#include <Scheduler.h>
#include <RTClib.h>
#include <SdFat.h>

#include <feather/wing/adalogger.h>


bool
AdaLogger::setup()
{
	if (!this->rtc.begin()) {
		Serial.println("RTC BEGIN");
		return false;
	}

	if (!this->card.begin(this->cardSelect)) {
		Serial.print("SD BEGIN ");
		Serial.println(this->cardSelect);
		this->card.errorPrint(F("SD ERR"));
		return false;
	}

	return true;
}


void
AdaLogger::task()
{
	yield();
}


// File access routines.
File
AdaLogger::openFile(const char *path, bool write)
{
	if (write) {
		return this->card.open(path, FILE_WRITE);
	}
	return this->card.open(path, FILE_READ);
}


bool
AdaLogger::exists(const char *path)
{
	return this->card.exists(path);
}


bool
AdaLogger::remove(const char *path)
{
	return this->card.remove(path);
}


bool
AdaLogger::mkdir(const char *path)
{
	return this->card.mkdir(path);
}


// RTC routines.
bool
AdaLogger::isClockReady()
{
	return this->rtc.initialized();
}


bool
AdaLogger::adjustRTC(DateTime &dto)
{
	this->rtc.adjust(dto);
	return true;
}


bool
AdaLogger::getDateTime(DateTime &dto)
{
	if (!this->isClockReady()) {
		return false;
	}

	dto = this->rtc.now();

	char		buf[20];
	sprintf(buf, "%04d-%02d-%02d %02d:%0d:%02d", dto.year(), dto.month(),
	        dto.day(), dto.hour(), dto.minute(), dto.second());
	Serial.println(buf);
	return true;	
}
