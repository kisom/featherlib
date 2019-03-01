#include <Arduino.h>
#undef min
#undef max
#include <string>
#include <vector>
#include <feather/wing/wing.h>
#include <Scheduler.h>


static std::vector<FeatherWing *>	wingRegistry;


void
registerWing(FeatherWing *wing)
{
	wingRegistry.push_back(wing);
}


bool
initialiseWings()
{
	delay(1000); // Give wings a chance to settle.
	for (size_t i = 0; i < wingRegistry.size(); i++) {
		if (!wingRegistry[i]->setup()) {
			Serial.print(F("INIT FAIL: "));
			Serial.println(wingRegistry[i]->name());
			return false;
		}
	}

	return true;
}

void
runWings()
{
	// NB: when this is switched over to FreeRTOS or similar,
	// this should fire a separate thread / task for each
	// wing.
	for (size_t i = 0; i < wingRegistry.size(); i++) {
		wingRegistry[i]->task();
		yield();
	}
}


void
scheduleWingTasks()
{
	Scheduler.startLoop(runWings);
}


bool
clockFormatTime(DateTime &dto, char *buf)
{
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
		dto.year(), dto.month(), dto.day(),
		dto.hour(), dto.minute(), dto.second());
	return true;
}

bool
clockFormatTime(Clock &clock, char *buf)
{
	DateTime	dto;

	if (!clock.getDateTime(dto)) {
		return false;
	}

	return clockFormatTime(dto, buf);
}
