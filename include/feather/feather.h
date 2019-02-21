#ifndef __FEATHERLIB_FEATHER_H
#define __FEATHERLIB_FEATHER_H


#if defined(ARDUINO_SAMD_FEATHER_M0)
#define FEATHER_M0
#include <feather/feather_m0.h>
#elif defined(ADAFRUIT_FEATHER_M0)
#define FEATHER_M0
#include <feather/feather_m0.h>
#elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
#define FEATHER_M4
#include <feather/feather_m4.h>
#else
#error "Board not supported."
#endif

#endif // __FEATHERLIB_FEATHER_H
