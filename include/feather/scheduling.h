#ifndef __FEATHERLIB_SCHEDULING_H
#define  __FEATHERLIB_SCHEDULING_H


#include <Arduino.h>


static inline void
yieldFor(unsigned long ms)
{
	unsigned long	until = millis() + ms;
	while (millis() < until) yield();
}


#endif //  __FEATHERLIB_SCHEDULING_H