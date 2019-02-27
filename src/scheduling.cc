#include <Arduino.h>
#include <Scheduler.h>
#include <feather/scheduling.h>


void
startThread(void (*thread)())
{
	Scheduler.startLoop(thread);
}
