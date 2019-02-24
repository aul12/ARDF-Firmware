#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma ide diagnostic ignored "bugprone-incorrect-roundings"

#include <stdlib.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "timer1.h"
#include "io.h"
#include "adc.h"
#include "util.h"

volatile uint8_t sendRequired;
volatile uint16_t interval_time = 60; // in seconds

void timer1_handler() {
    static uint16_t count = 0; //@TODO if the prescaler is 1 we have an oveflow here
    if(++count > (uint16_t)(interval_time / TIMER1_GET_FREQ(1024))) {
        sendRequired++;
        count = 0;
    }
}

int main(void) {
    io_init();
    timer1_init(PRESCALER_1024, &timer1_handler);
    util_quantized_low_pass_t char_filter = util_init_quantizized_low_pass(5, 10, 1023);
    util_quantized_low_pass_t interval_filter = util_init_quantizized_low_pass(5, 10, 1023);

    char send_char = 'A';

    while (true) {
        if (sendRequired) {
            util_send_char(send_char);
            sendRequired--;
        }

        bool dip_position = io_get_filtered_dip(50);

        if (dip_position) { // Interval
            uint8_t interval_step = util_add_new_measurent(&interval_filter, adc_read_synchr(2));
            switch (interval_step) {
                case 0:
                    interval_time = 10;
                    break;
                    //@TODO handle all values
                default:
                    interval_time = 60;
                    break;
            }
        } else { // Buchstaben
            uint8_t char_step = util_add_new_measurent(&char_filter, adc_read_synchr(2));
            switch (char_step) {
                case 0:
                    send_char = 'A';
                    break;
                    //@TODO handle all values
                default:
                    send_char = 'B';
                    break;
            }
        }
    }
}

#pragma clang diagnostic pop