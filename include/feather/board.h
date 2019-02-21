#ifndef __FEATHERLIB_BOARD_H
#define __FEATHERLIB_BOARD_H


#include <stdint.h>


class Board {
public:
	virtual 		~Board() {};
	virtual double		voltage() = 0;
	virtual void		setup(int baudrate, bool wait) = 0;
	virtual uint32_t	random() = 0;
	virtual void		seed() = 0;
};


#endif // __FEATHERLIB_BOARD_H