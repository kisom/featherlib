// loraspy listens for LoRa packets and status information to
// the OLED: the number of packets received, the total size,
// and the unix timestamp of the last message received. It uses
// an RFM95 Radiofruit, an Adalogger, and an OLED display.
#include <Arduino.h>
#include <string.h>

#include <feather/feather.h>
#include <feather/trigger.h>
#include <feather/wing/wing.h>
#include <feather/wing/adalogger.h>
#include <feather/wing/oled.h>
#include <feather/wing/rfm95.h>


// The RFM95 Radiofruit Feather is a standard Feather M0 with
// an onboard radio.
FeatherM0	feather(INPUT_PULLUP);
// The SD card isn't used, so SD support is disabled so that
// an SD card isn't required.
Adalogger	logger(0);
// The RFM95 class defaults to working with the pins on the
// Radiofruit Feather M0.
RFM95		radio;
OLED		display;
// printTime ensures that the time is only updated once every
// 250ms; since Unix time is being used for timestamps and
// it has a resolution of one second, this is sufficient.
Trigger		printTime(250);

const int	led = 13;


// distress blinks the LED rapidly to visually indicate
// a problem.
void
distress()
{
	while (true) {
		digitalWrite(led, HIGH);
		delay(100);
		digitalWrite(led, LOW);
		delay(100);
	}
}


void
setup()
{
	pinMode(led, OUTPUT);

	// Start the serial port at 9600 baud but don't wait
	// for a serial connection.
	feather.setup(9600, true);

        // Registering wings allows them to be set up in one pass and
        // allows any update tasks to be started later on.
	registerWing(&logger);
	registerWing(&radio);
	registerWing(&display);

	if (!initialiseWings()) {
		// If the Featherwings can't be setup, an error
		// is printed and the LED is flashed.
		Serial.println("BOOT FAILED");
		distress();
	}

	// If the clock isn't ready, it means the RTC needs to be
	// set; print a warning and flash the LED in that case.
	if (!logger.isClockReady()) {
		display.iprint(0, "WARNING");
		display.iprint(1, "RTC FAIL");
		distress();
	}

	// This starts a background thread that runs the update tasks
	// for the featherwings. There aren't any boards that really
	// need to be checked, but if support for buttons is added later,
	// the OLED wing will need to check the buttons. Another scheduler
	// can be used that calls `runWings`, too.
	scheduleWingTasks();	
	display.print(0, "BOOT OK");
}


void
loop()
{
	static DateTime	dateTime;
	uint8_t		buf[252];	// buf is used for the radio.
	char		text[21];	// text is used to print to the OLED.
	int16_t		rssi;
	// len needs to be set to tell the RFM95 how much buffer space is
	// available.
	uint8_t		len = 251;
	static int	nmsg = 0;
	static uint16_t	msglen = 0;

	if (printTime.ready()) {
		if (!logger.getDateTime(dateTime)) {
			return;
		}

		clockFormatTime(dateTime, text);
		display.print(2, text);
	}

	if (radio.receive(buf, &len, &rssi)) {
		msglen += len;
		nmsg++;
		sprintf(text, "N: %d L: %u", nmsg, msglen);
		display.print(0, text);
		sprintf(text, "LAST: %lu", dateTime.unixtime());
		display.print(1, text);
	}
}
