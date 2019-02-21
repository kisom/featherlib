#include <Arduino.h>
#undef min
#undef max
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
		delay(100);
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
	delay(10);
}