#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma ide diagnostic ignored "bugprone-incorrect-roundings"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>

#include "timer1.h"
#include "io.h"

uint8_t sendRequired;

void timer1_handler() {
    static uint16_t count = 0; //@TODO if the prescaler is 1 we have an oveflow here
    if(++count > (uint16_t)(60/TIMER1_GET_FREQ(1024)+0.5f)) {
        sendRequired++;
        count = 0;
    }
}

int main(void) {
    timer1_init(PRESCALER_1024, &timer1_handler);

    while (true) {

    }
}

#pragma clang diagnostic pop