#ifndef __FEATHERLIB_TRIGGER_H
#define __FEATHERLIB_TRIGGER_H


// A Trigger returns true if enough time has passed.
class Trigger {
public:
	Trigger(unsigned long delta) : next(0), delta(delta) {}
	Trigger(unsigned long delta, bool skipFirst);
	bool	ready();
	bool	ready(unsigned long now);
	void	reset();
	void	reset(unsigned long now);

private:
	unsigned long	next;
	unsigned long	delta;
};


#endif // __FEATHERLIB_TRIGGER_H
