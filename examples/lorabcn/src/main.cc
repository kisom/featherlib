// lorabcn is a program that transmits a LoRa beacon every
// second. It uses a Feather M0 with RFM95. It's useful for
// testing LoRa reception.
#include <Arduino.h>
#include <string.h>

#include <kasl/scheduling.h>
#include <feather/feather.h>
#include <feather/trigger.h>
#include <feather/wing/rfm95.h>


// The RFM95 Radiofruit Feather is a standard Feather M0 with
// an onboard radio.
FeatherM0	board;
// The RFM95 class defaults to working with the pins on the
// Radiofruit Feather M0.
RFM95		radio;

const int ledPin = 13;


// distress blinks the LED rapidly to visually indicate
// a problem.
void
distress()
{
	while (true) {
		digitalWrite(ledPin, HIGH);
		delay(100);
		digitalWrite(ledPin, LOW);
		delay(100);
	}
}


// beacon flashes the LED in a double blink pattern to
// visually indicate normal operation.
void
beacon()
{
	digitalWrite(ledPin, HIGH);
	kasl::yieldFor(100);
	digitalWrite(ledPin, LOW);
	kasl::yieldFor(100);
	digitalWrite(ledPin, HIGH);
	kasl::yieldFor(100);
	digitalWrite(ledPin, LOW);
	kasl::yieldFor(700);
}


void
setup()
{
	pinMode(ledPin, OUTPUT);

	// Start the serial port at 9600 baud but don't wait
	// for a serial connection.
	board.setup(9600, false);

	// Registering wings allows them to be set up in one pass and
	// allows any update tasks to be started later on.
	registerWing(&radio);

	if (!initialiseWings()) {
		// If the radio can't be initialised, print a message
		// and flash the LED.
		Serial.println("BOOT FAILED");
		distress();
	}
		
	Serial.println("BOOT OK");

	// Start up a background task to blink the LED.
	kasl::scheduleThread(beacon);
	kasl::startScheduler();
}


void
loop()
{
	// transmit is used to limit transmissions to once per second.
	static Trigger	transmit(1000);
	static int16_t	packetno = 0; 
	uint8_t		buf[20];

	kasl::runScheduler();
	if (transmit.ready()) {
		sprintf((char *)buf, "hello world #%0u", ++packetno);
		radio.transmit(buf, 18, true);
	}
}
