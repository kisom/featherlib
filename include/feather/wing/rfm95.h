#ifndef __FEATHERLIB_RFM95_H
#define __FEATHERLIB_RFM95_H


#include <stdint.h>
#include <feather/wing/wing.h>
#include <RH_RF95.h>


// Inclusion of these defaults was a matter of some debate, but I decided to
// default to the Feather M0 with RFM95 in the US region.
//
#ifndef LORA_FREQ
#define LORA_FREQ	915.0
#endif // LORA_FREQ

#ifndef RFM95_CS
#define RFM95_CS	8
#endif

#ifndef RFM95_RST
#define RFM95_RST	4
#endif

#ifndef	RFM95_INT
#define RFM95_INT	3
#endif


class RFM95 : public FeatherWing {
public:
	RFM95() : cs(RFM95_CS), irq(RFM95_INT), rst(RFM95_RST), radio(RFM95_CS, RFM95_INT) {}
	RFM95(uint8_t cs, uint8_t irq, uint8_t rst) :
		cs(cs), irq(irq), rst(rst), radio(cs, irq) { }

	bool		 setup();
	void		 task();
	const char	*name() { return "RFM95"; }

	bool		 available();
	void		 setPower(uint8_t);
	void		 transmit(uint8_t *buf, uint8_t len, bool blocking);
	bool		 receive(uint8_t *buf, uint8_t *len, int16_t *rssi);


private:
	uint8_t	cs, irq, rst;
	RH_RF95	radio;
};


#endif // __FEATHERLIB_RFM95_H
