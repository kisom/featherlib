#include <Arduino.h>
#include <feather/wing/wing.h>
#include <feather/wing/rfm95.h>


bool		 
RFM95::setup()
{
	pinMode(this->rst, OUTPUT);
	this->enable();

	if (!this->radio.init()) {
		Serial.println("failed to start radio");
		Serial.print("CS: ");
		Serial.print(this->cs);
		Serial.print(", IRQ: ");
		Serial.print(this->irq);
		Serial.print(", RST: ");
		Serial.println(this->rst);
		return false;
	}

	if (!this->radio.setFrequency(LORA_FREQ)) {
		Serial.print("failed to set frequency to ");
		Serial.println(LORA_FREQ, 1);
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


void		 
RFM95::disable()
{
	digitalWrite(this->rst, LOW);
}


void
RFM95::enable()
{
	digitalWrite(this->rst, HIGH);
}


void
RFM95::reset()
{
	this->disable();
	delay(10);
	this->enable();
}
