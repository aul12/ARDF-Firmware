/**
 * @file adc.c
 * @author paul
 * @date 23.02.19
 * @brief adc implemetation of the adc library
 */

#include <avr/io.h>
#include "adc.h"

uint16_t adc_read_synchr(uint8_t adcChannel) {
    ADMUX = 0x00; //Vcc used as Vref
    ADMUX |= adcChannel & 0x3F; // Mask the lower 6 bits
    ADCSRA = 0xC0; // Enable ADC and start the conversion, disable interrupts, sets the interrupt flag to 0
    ADCSRB = 0x00; // Right adjusted data, no auto trigger

    while (!((ADCSRA >> 4) & 0x01)); // Wait for the interrupt flag to be set
    return ADC;
}
