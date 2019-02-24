/**
 * @file Timer16Bit.c
 * @author paul
 * @date 23.02.19
 * @brief implementation of the timer1 library
 */
#include "timer1.h"

#include <avr/interrupt.h>

void (*callback_funct)(void) = 0;

ISR(TIM1_OVF_vect) {
    if (callback_funct != 0) {
        (*callback_funct)();
    }
}


void timer1_init(prescaler_t prescaler, void (*callback)(void)) {
    cli();
    TCCR1A = 0x00; // No Output compare, normal waveform (See Page 106)
    TCCR1B = 0x00; // No Input noise cancelling (we do not use the input, normal waveform
    TCCR1B |= 0x07 & prescaler; // Set the lower three bits to the prescaler values
    TCCR1C = 0x00; // Do not force the output compare

    TIMSK1 = 0x01; // No compare and no input capture interrupts but the overflow interrupt

    TCNT1 = 0; // Set the timer value to zero
    callback_funct = callback;
    sei();
}
