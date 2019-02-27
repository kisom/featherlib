#include <Arduino.h>
#include <Scheduler.h>
#include <RTClib.h>
#include <SdFat.h>

#include <feather/wing/adalogger.h>


bool
Adalogger::setup()
{
	if (!this->rtc.begin()) {
		Serial.println("RTC BEGIN");
		return false;
	}

	// Setting CS to 0 should disable the SD card.
	if (this->cardSelect == 0) {
		Serial.println("adalogger: storage disabled");
		return true;
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
Adalogger::task()
{
	// The Adalogger has no ongoing tasks.
	yield();
}


// File access routines.
File
Adalogger::openFile(const char *path, bool write)
{
	if (this->storageDisabled()) {
		return File();
	}

	if (write) {
		return this->card.open(path, FILE_WRITE);
	}
	return this->card.open(path, FILE_READ);
}


bool
Adalogger::exists(const char *path)
{
	if (this->storageDisabled()) {
		return false;
	}

	return this->card.exists(path);
}


bool
Adalogger::remove(const char *path)
{
	if (this->storageDisabled()) {
		return false;
	}
	return this->card.remove(path);
}


bool
Adalogger::mkdir(const char *path)
{
	if (this->storageDisabled()) {
		return false;
	}
	return this->card.mkdir(path);
}


// RTC routines.
bool
Adalogger::isClockReady()
{
	return this->rtc.initialized();
}


bool
Adalogger::adjustRTC(DateTime &dto)
{
	this->rtc.adjust(dto);
	return true;
}


bool
Adalogger::getDateTime(DateTime &dto)
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
