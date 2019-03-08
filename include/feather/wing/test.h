#ifndef __FEATHERLIB_WING_TEST_H
#define __FEATHERLIB_WING_TEST_H


#include <Arduino.h>
#include <feather/wing/wing.h>


class TestWing : public FeatherWing {
public:
	TestWing() : counter(0) {};
	bool	setup();
	void	task();

	const char	*name() { return "Test"; }
private:
	int	counter;
};


#endif // __FEATHERLIB_WING_TEST_H
