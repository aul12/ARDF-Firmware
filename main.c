#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-incorrect-roundings"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>

#include "timer1.h"

#define NUM_COUNTS_PER_MINUTE (60/TIMER1_GET_FREQ(1024))

uint8_t sendRequired;

void timer1_handler() {
    static uint16_t count = 0; //@TODO if the prescaler is 1 we have an oveflow here
    if(++count > (uint16_t)(NUM_COUNTS_PER_MINUTE+0.5f)) {
        sendRequired++;
        count = 0;
    }
}

int main()
{
    timer1_init(PRESCALER_1024, &timer1_handler);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
    }
#pragma clang diagnostic pop
}

#pragma clang diagnostic pop