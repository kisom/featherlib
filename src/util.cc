#include <feather/util.h>
#include <stdint.h>

namespace featherlib {


void
swap_u8(uint8_t &a, uint8_t &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}


void
swap_ul(unsigned long &a, unsigned long &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}


} // featherlib