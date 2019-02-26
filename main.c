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
#include "pwm0.h"

volatile uint8_t sendRequired = 0;
volatile uint16_t interval_time; // in seconds

void timer1_handler(void) {
    static uint16_t count = 0; //@WARN if the prescaler is 1 we have an oveflow here
    if(++count > (uint16_t)(interval_time / TIMER1_GET_FREQ(1024))) {
        sendRequired++;
        count = 0;
    }
}

void set_send_out(bool state) {
    if (state) {
        SET_SEND_EN;
        SET_LED(1);
    } else {
        CLEAR_SEND_EN;
        CLEAR_LED(1);
    }
}

int main(void) {
    io_init();
    pwm0_init();
    timer1_init(PRESCALER_1024, &timer1_handler);

    // Possible intervals between sending in seconds
    uint16_t interval_times[] = {10, 20, 30, 45, 60, 120, 600};
    // Possible chars to be send
    char send_chars[] = {'A', 'E', 'I', 'O', 'U'};

    util_quantized_low_pass_t char_filter =
            util_init_quantizized_low_pass(sizeof(interval_times)/ sizeof(interval_times[0]), 10, 1024);
    util_quantized_low_pass_t interval_filter =
            util_init_quantizized_low_pass(sizeof(send_chars)/ sizeof(send_chars[0]), 10, 1024);

    //@TODO read values out of the eeprom
    char send_char = send_chars[0];
    interval_time = interval_times[0];

    while (true) {
        if (sendRequired > 0) {
            util_send_char(send_char, &set_send_out);
            sendRequired--;
        }

        bool dip_position = io_get_filtered_dip(50);

        //@TODO save the intervall time if it changed (and only if it changed)
        if (dip_position) { // Interval
            uint8_t interval_step = util_add_new_measurent(&interval_filter, adc_read_synchr(2));
            interval_time = interval_times[interval_step];
        } else { // Character
            uint8_t char_step = util_add_new_measurent(&char_filter, adc_read_synchr(2));
            send_char = send_chars[char_step];
        }

        // Buzzer for the battery (approx 1.7 kHz)
        if (util_battery_voltage_milli_volt() < 10500) {
            pwm0_set(127);
        } else {
            pwm0_set(0);
        }
    }
}

#pragma clang diagnostic pop