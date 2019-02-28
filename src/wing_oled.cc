#include <Arduino.h>
#include <Scheduler.h>
#include <feather/wing/oled.h>
#include <feather/wing/wing.h>


bool
OLED::setup()
{
	if (!this->oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		return false;
	}
	this->oled.setTextSize(1);
	this->oled.setTextColor(WHITE);        // Draw white text
	this->oled.clearDisplay();
	return true;
}


const char *
OLED::name()
{
	return "OLED";
}


void
OLED::clear()
{
	this->oled.clearDisplay();
	this->oled.fillScreen(BLACK);
}


void
OLED::pixel(uint16_t x, uint16_t y)
{
	this->oled.drawPixel(x, y, WHITE);
}


void
OLED::clearPixel(uint16_t x, uint16_t y)
{
	this->oled.drawPixel(x, y, BLACK);
}


void
OLED::circle(uint16_t x, uint16_t y, uint16_t r, bool fill)
{
	if (fill) {
		this->oled.fillCircle(x, y, r, WHITE);
	}
	else {
		this->oled.drawCircle(x, y, r, WHITE);
	}
}


void
OLED::line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	this->oled.drawLine(x0, y0, x1, y1, WHITE);
}


void
OLED::show()
{
	this->oled.display();
}


void
OLED::clearText()
{
	for (uint8_t i = 0; i < this->MAX_LINES; i++) {
		memset(this->lines[i].text, 0, this->MAX_TEXT+1);
		this->lines[i].inverse = false;
	}
	this->oled.clearDisplay();
	this->oled.display();
}


void
OLED::showLines()
{
	this->oled.clearDisplay();
	for (uint8_t i = 0; i < this->MAX_LINES; i++) {
		this->oled.setCursor(0, i * 10);
		if (lines[i].inverse) {
			this->oled.setTextColor(BLACK, WHITE);
		}
		else {
			this->oled.setTextColor(WHITE, BLACK);
		}
		this->oled.println(lines[i].text);
	}
	this->oled.display();
}


void
OLED::print(uint8_t line, const char *text)
{
	if (line > (this->MAX_LINES - 1)) {
		return;
	}

	int	slen = strnlen(text, MAX_TEXT);

	memset(this->lines[line].text, 0, MAX_TEXT+1);
	strncpy(this->lines[line].text, text, slen);
	this->lines[line].inverse = false;
	showLines();	
}


void
OLED::iprint(uint8_t line, const char *text)
{
	if (line > (this->MAX_LINES - 1)) {
		return;
	}

	int	slen = strnlen(text, MAX_TEXT);

	memset(this->lines[line].text, 0, MAX_TEXT+1);
	strncpy(this->lines[line].text, text, slen);
	this->lines[line].inverse = true;
	showLines();	
}


void
OLED::clearLine(uint8_t line)
{
	if (line > (this->MAX_LINES - 1)) {
		return;
	}

	memset(this->lines[line].text, 0, MAX_TEXT+1);
	showLines();	
}


void
OLED::sample()
{
	this->buttonA.sample();
	this->buttonB.sample();
	this->buttonC.sample();
}


void
OLED::registerCallback(uint8_t button, void (*callback)())
{
	switch (button) {
	case 0:
		this->buttonA.registerCallback(callback);
		break;
	case 1:
		this->buttonB.registerCallback(callback);
		break;
	case 2:
		this->buttonC.registerCallback(callback);
		break;
	default:
		// Invalid button index, so do nothing.
		return;
	}
}


void
OLED::unregisterCallback(uint8_t button)
{
	this->registerCallback(button, nullptr);
}


void
OLED::unregisterAllCallbacks()
{
	for (uint8_t i = 0; i < 3; i++) {
		this->unregisterCallback(i);
	}
}


void
OLED::task()
{
	this->sample();
	yield();
}
