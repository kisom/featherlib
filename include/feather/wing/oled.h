#ifndef __FEATHERLIB_WING_OLED_H
#define __FEATHERLIB_WING_OLED_H


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <stdint.h>
#include <feather/button.h>
#include <feather/wing/wing.h>


typedef struct {
	char	text[21];	// tested manually
	bool	inverse;
} screenLine;


class OLED : public FeatherWing {
public:
	static const int	HEIGHT = 32;
	static const int	WIDTH  = 128;
	static const int	MAX_TEXT = 20;
	static const int	MAX_LINES = 3;

	// The default constructor uses the standard buttons, but
	// if the buttons have been redirected elsewhere, there is
	// a constructor for that.
	OLED() 
	: buttonA(9), buttonB(6), buttonC(5), oled(Adafruit_SSD1306(128, 32, &Wire)) 
	{
		registerWing(this);
	};
	OLED(uint8_t a, uint8_t b, uint8_t c)
	    : buttonA(a), buttonB(b), buttonC(c)
	{
		registerWing(this);
	} 


	bool		 setup();
	const char	*name();

	// Graphics routines.
	void	clear();
	void	pixel(uint16_t x, uint16_t y);
	void	clearPixel(uint16_t x, uint16_t y);
	void	circle(uint16_t x, uint16_t y, uint16_t r, bool fill);
	void	line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	void	show();

	// Text display routines.
	void	clearText();
	void	print(uint8_t line, const char *text);
	void	iprint(uint8_t line, const char *text);
	void	clearLine(uint8_t line);

	// Button handling.
	void	sample();
	void	registerCallback(uint8_t button, void (*callback)());
	void	unregisterCallback(uint8_t button);
	void	unregisterAllCallbacks();

	// Task checks the buttons for updates.
	void	task();

private:
	featherlib::Button	buttonA;
	featherlib::Button	buttonB;
	featherlib::Button	buttonC;
	Adafruit_SSD1306	oled;
	screenLine		lines[3];

	void			showLines();
};


#endif // __FEATHERLIB_WING_OLED_H
