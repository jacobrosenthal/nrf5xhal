//DFUService.h takes ~216 bytes, grabbing underlying files instead

#include "nrf5xhal/irq.h"
#include "nrf5xhal/gpio.h"

#include <stddef.h>
#include "cmsis.h"

#include <mbed_error.h>

#ifndef YOTTA_CFG_MBED_MAX_INTERRUPTS
#   define YOTTA_CFG_MBED_MAX_INTERRUPTS 31
#endif

static uint32_t portRISE = 0;
static uint32_t portFALL = 0;
static uint8_t map[YOTTA_CFG_MBED_MAX_INTERRUPTS] = {0};

void _gpio_irq_set(PinName pin, gpio_irq_event event, uint32_t enable)
{
    NRF_GPIO->PIN_CNF[pin] &= ~(GPIO_PIN_CNF_SENSE_Msk);
    if (enable) {
        if (event == IRQ_RISE) {
            portRISE |= (1 << pin);
        } else if (event == IRQ_FALL) {
            portFALL |= (1 << pin);
        }
    } else {
        if (event == IRQ_RISE) {
            portRISE &= ~(1 << pin);
        } else if (event == IRQ_FALL) {
            portFALL &= ~(1 << pin);
        }
    }

    if (((portRISE >> pin) & 1) || ((portFALL >> pin) & 1)) {
        if ((NRF_GPIO->IN >> pin) & 1) {
            NRF_GPIO->PIN_CNF[pin] |= (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);    // | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos);
        } else {
            NRF_GPIO->PIN_CNF[pin] |= (GPIO_PIN_CNF_SENSE_High << GPIO_PIN_CNF_SENSE_Pos);     //| (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos);
        }
    }
}

void attachInterrupt(PinName pin, void (*fptr)(void), gpio_irq_event event)
{
    switch (event) {
        case IRQ_RISE:
            _gpio_irq_set(pin, IRQ_RISE, 1);
            break;
        case IRQ_FALL: 
            _gpio_irq_set(pin, IRQ_FALL, 1);
            break;
        case IRQ_NONE:
            break;
    }

    pinDirection(pin, PIN_INPUT);
    pinMode(pin, PullDefault);

    NRF_GPIOTE->EVENTS_PORT = 0;
    NRF_GPIOTE->INTENSET    = GPIOTE_INTENSET_PORT_Set << GPIOTE_INTENSET_PORT_Pos;

    NVIC_SetPriority(GPIOTE_IRQn, 3);
    NVIC_EnableIRQ  (GPIOTE_IRQn);
}

void detachInterrupt(PinName pin, gpio_irq_event event)
{
    switch (event) {
        case IRQ_RISE:
            _gpio_irq_set(pin, IRQ_RISE, 0);
            break;
        case IRQ_FALL: 
            _gpio_irq_set(pin, IRQ_FALL, 0);
            break;
        case IRQ_NONE:
            break;
    }
}
