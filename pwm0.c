/**
 * @file pwm0.c
 * @author paul
 * @date 26.02.19
 * @brief pwm0 @TODO
 */

#include <avr/io.h>
#include "pwm0.h"

void pwm0_init(void) {
    TCCR0A = 0xC0; // OC0A as output, normal mode
    TCCR0B = 0x02; // No force, prescaler 8 (=> ~1.7kHz)
    TIMSK0 = 0x00; // No interrupts


    TCNT0 = 0; // Set the counter to 0
    pwm0_set(0);
}

void pwm0_set(uint8_t duty_cycle) {
    OCR0A = duty_cycle;
}