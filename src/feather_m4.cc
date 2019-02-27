#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
#include <feather/feather_m4.h>
#include <Arduino.h>
#include <stdint.h>


const uint8_t	batteryPin = A6;


double
FeatherM4::voltage()
{
	// The battery pin is often used for other things,
	// as well.
	double v;

	pinMode(batteryPin, INPUT);
	delay(5); // Give time for the pin to settle.
	v = analogRead(batteryPin);

	// First, multiply by 2, then multiply by the reference voltage
	// of 3.3V, then divide by 1024.
	return v / 155.15;
}


void
FeatherM4::setup(int baudrate, bool wait)
{
	asm(".global _printf_float");
	this->seed();
	Serial.begin(baudrate);
	if (wait) {
		while (!Serial) yield();
	}
}


uint32_t
FeatherM4::random()
{
	if (!this->trngReady) {
		MCLK->APBCMASK.reg |= MCLK_APBCMASK_TRNG;
		TRNG->CTRLA.reg = TRNG_CTRLA_ENABLE;
		this->trngReady = true;
	}

	// Wait the 84 ABP clock cycles.
	while ((TRNG->INTFLAG.reg & TRNG_INTFLAG_DATARDY) == 0) yield();

	return TRNG->DATA.reg;
}


void
FeatherM4::seed()
{
	uint32_t	r = this->random();

	randomSeed(r);
}


#endif // defined(ADAFRUIT_FEATHER_M4_EXPRESS)
