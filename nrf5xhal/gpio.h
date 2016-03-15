// init digitalout outside mbed to save 24 bytes

#ifndef NRF5XHAL_GPIO_H
#define NRF5XHAL_GPIO_H

#include <stdint.h>
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

int digitalRead(PinName pin);
void digitalWrite(PinName pin, int value);
void pinDirection(PinName pin, PinDirection direction);
void pinMode(PinName pin, PinMode mode);

#ifdef __cplusplus
}
#endif

#endif
