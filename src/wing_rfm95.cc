#include <Arduino.h>
#include <feather/wing/wing.h>
#include <feather/wing/rfm95.h>


bool		 
RFM95::setup()
{
	pinMode(this->rst, OUTPUT);
	digitalWrite(this->rst, HIGH);

	if (!this->radio.init()) {
		return false;
	}

	if (!this->radio.setFrequency(LORA_FREQ)) {
		return false;
	}

	// Initially set to maximum power, but this can
	// be adjusted using setPower later.
	this->radio.setTxPower(23, false);

	return true;
}


void
RFM95::task()
{
	// Currently, there aren't any tasks to be done. In the
	// future, there might be an RX/TX packet queue.
	return;
}


bool
RFM95::available()
{
	return this->radio.available();	
}


void		
RFM95::setPower(uint8_t power)
{
	this->radio.setTxPower(power, false);
}


void
RFM95::transmit(uint8_t *buf, uint8_t len, bool block)
{
	this->radio.send(buf, len);
	if (block) {
		this->radio.waitPacketSent();
	}
}


bool
RFM95::receive(uint8_t *buf, uint8_t *len, int16_t *rssi)
{
	if (this->radio.recv(buf, len)) {
		if (rssi) {
			*rssi = this->radio.lastRssi();	
		}
		return true;
	}
	return false;
}

