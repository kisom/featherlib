#ifndef __FEATHERLIB_WING_WING_H
#define __FEATHERLIB_WING_WING_H


#include <Scheduler.h>
#include <RTClib.h>


// A FeatherWing is a generic interface for FeatherWings. It supports a setup
// function and a task function.
class FeatherWing {
public:
	virtual 	~FeatherWing() {};

	// setup should run any initialisation tasks.
	virtual bool		 setup() = 0;

	// task is used by runTasks to run all the background tasks required by
	// the wings. It should make liberal use of yield where possible.
	virtual void		 task() = 0;
	virtual const char	*name() = 0;
};


// A Clock represents some form of RTC.
class Clock {
public:
	virtual		~Clock() {};

	virtual bool	isClockReady() = 0;
	virtual bool	getDateTime(DateTime &dto) = 0;
};


void	registerWing(FeatherWing *wing);
bool	initialiseWings();
void	runWings();
void	scheduleWingTasks();
bool	clockFormatTime(Clock &clock, char *buf);


#endif // __FEATHERLIB_WING_WING_H
