#include <Arduino.h>
#undef max
#undef min
#include <feather/wing/test.h>


bool
TestWing::setup()
{
	Serial.println("test wing setup");
	return true;
}


void
TestWing::task()
{
	for (int i = 0; i < 10; i++) {
		Serial.print("TestWing task running #");
		Serial.println(this->counter++);
		yield();
		delay(10);
	}
}
