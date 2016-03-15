
#ifndef NRF5XHAL_IRQ_H
#define NRF5XHAL_IRQ_H

#include <stdint.h>
#include "device.h"
#include "gpio_irq_api.h"

#ifdef __cplusplus
extern "C" {
#endif

void attachInterrupt(PinName pin, void (*fptr)(void), gpio_irq_event event);
void detachInterrupt(PinName pin, gpio_irq_event event);

struct _gpio_irq_s {
  uint32_t pin;
  void (*fptr)(void);
};

static uint32_t portRISE;
static uint32_t portFALL;

#ifdef __cplusplus
}
#endif

#endif
