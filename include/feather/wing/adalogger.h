#ifndef __FEATHERLIB_ADALOGGER_H
#define __FEATHERLIB_ADALOGGER_H


#include <RTClib.h>
#include <SdFat.h>
#include <feather/wing/wing.h>


class AdaLogger : public FeatherWing, public Clock {
public:
	AdaLogger() : cardSelect(10) {};
	AdaLogger(uint8_t cs) : cardSelect(cs) {};

	bool	setup();
	void	task();

	// File access routines.
	File	openFile(const char *path, bool write);
	bool	exists(const char *path);
	bool	remove(const char *path);
	bool	mkdir(const char *path);	

	// RTC routines.
	bool	isClockReady();
	bool	adjustRTC(DateTime &dto);
	bool	getDateTime(DateTime &dto);

	const char	*name() { return "AdaLogger"; }
private:
	uint8_t		cardSelect;
	RTC_PCF8523	rtc;
	SdFat		card;
};


#endif // __FEATHERLIB_ADALOGGER_H