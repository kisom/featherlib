// calamity uses an OLED display with a Feather to toggle the LED. The
// display shows the current LED state; if the middle button on the
// Featherwing is pressed, the display will flash the word "CALAMITY."
#include <Arduino.h>

// feather/feather.h pulls in support for the appropriate board.
#include <feather/feather.h>

// scheduling contains useful functions for working with the Arduino
// task scheduler; it's used here for the `kasl::yieldFor` function that
// acts like a delay that coöperates with other threads.
#include <kasl/scheduling.h>
#include <feather/wing/wing.h>
#include <feather/wing/oled.h>


#if defined(FEATHER_M0)
FeatherM0	board;
#elif defined(FEATHER_M4)
FeatherM4	board;
#else
#error Unknown board.
#endif


OLED	display;
int	ledPin = 13;
bool	ledOn = false;


// calamity is the callback function registered to button B on the
// display, which is the middle button.
void
calamity()
{
	for (uint8_t i = 0; i < 8; i++) {
		display.print(2, "CALAMITY");
		kasl::yieldFor(250);
		display.iprint(2, "CALAMITY");
		kasl::yieldFor(250);
	}
	
	display.clearLine(2);
}


void
setup()
{
	// Start the serial port at 9600 baud but don't wait for a serial
	// connection to continue booting.
	board.setup(9600, false);

	// Registering wings allows them to be set up in one pass and allows
	// any update tasks to be started later on.
	registerWing(&display);

	if (!initialiseWings()) {
		// If a wing fails to initialise, a message will be
		// printed to serial.
		while (true) ;
	}

	// When button B (the middle button, or index 1) is pressed, run
	// the calamity function.
	display.registerCallback(1, calamity);

	// This starts a background thread that runs the update tasks
	// for the featherwings. For example, in this sketch, the OLED 
	// Featherwings need to be checked regularly. Another scheduler
	// can be used that calls `runWings`, too.
	scheduleWingTasks();
}


void
loop()
{
	if (ledOn) {
		ledOn = false;
		digitalWrite(ledPin, LOW);
		display.print(0, "LED OFF");
	}
	else {
		ledOn = true;
		digitalWrite(ledPin, HIGH);
		display.iprint(0, "LED ON");
	}

	kasl::yieldFor(1000);
}
