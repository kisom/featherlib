#if defined(ARDUINO_SAMD_FEATHER_M0) || defined(ADAFRUIT_FEATHER_M0)
#include <feather/feather_m0.h>
#include <Arduino.h>
#include <stdint.h>


const uint8_t	batteryPin = 9;


double
FeatherM0::voltage()
{
	// The battery pin is often used for other things,
	// as well.
	double v;

	pinMode(batteryPin, INPUT);
	delay(5); // Give time for the pin to settle.
	v = analogRead(batteryPin);
	pinMode(9, this->pin9Mode);

	// First, multiply by 2, then multiply by the reference voltage
	// of 3.3V, then divide by 1024.
	return v / 155.15;
}


void
FeatherM0::setup(int baudrate, bool wait)
{
	asm(".global _printf_float");
	this->seed();
	Serial.begin(baudrate);
	if (wait) {
		while (!Serial) yield();
	}
}


uint32_t
FeatherM0::random()
{
	uint32_t	r = 0;

	pinMode(this->unusedAnalog, INPUT);

	for (int i = 0; i < 16; i++) {
		r += (analogRead(this->unusedAnalog) & 0xF);
		r <<= 4;
		delay(11);
	}

	return r;	
}


void
FeatherM0::seed()
{
	uint32_t	r = this->random();

	randomSeed(r);
}


#endif // defined(ARDUINO_SAMD_FEATHER_M0) || defined(ADAFRUIT_FEATHER_M0)