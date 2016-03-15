
#include "nrf5xhal/gpio.h"

int digitalRead(PinName pin){
    MBED_ASSERT(pin != (PinName)NC);
    return ((NRF_GPIO->IN & (1ul << pin)) ? 1 : 0);
}

void digitalWrite(PinName pin, int value){
    MBED_ASSERT(pin != (PinName)NC);
    if (value)
        NRF_GPIO->OUTSET = (1ul << pin);
    else
        NRF_GPIO->OUTCLR = (1ul << pin);
}

void pinDirection(PinName pin, PinDirection direction)
{
    MBED_ASSERT(pin != (PinName)NC);
    switch (direction) {
        case PIN_INPUT:
            NRF_GPIO->PIN_CNF[pin] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                        | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                        | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                        | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
            break;
        case PIN_OUTPUT:
            NRF_GPIO->PIN_CNF[pin] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                        | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                        | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                        | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                        | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
            break;
    }
}

void pinMode(PinName pin, PinMode mode)
{
    MBED_ASSERT(pin != (PinName)NC);

    uint32_t pin_number = (uint32_t)pin;

    NRF_GPIO->PIN_CNF[pin_number] &= ~GPIO_PIN_CNF_PULL_Msk;
    NRF_GPIO->PIN_CNF[pin_number] |= (mode << GPIO_PIN_CNF_PULL_Pos);
}
