#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma ide diagnostic ignored "bugprone-incorrect-roundings"

#include <stdbool.h>
#include <avr/eeprom.h>

#include "timer1.h"
#include "io.h"
#include "adc.h"
#include "util.h"
#include "pwm0.h"

#define CHAR_ADDRESS ((uint8_t*)0)
#define INTERVAL_ADDRESS ((uint8_t*)1)

volatile uint8_t sendRequired = 0;
volatile uint16_t interval_time; // in seconds

void timer1_handler(void) {
    static uint16_t count = 0; //@WARN if the prescaler is 1 we have an oveflow here
    if(++count / TIMER1_GET_FREQ(1024) > interval_time) {
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

    if (MCUSR & 0x0C) { // Watchdog or Brownout
        SET_LED(5);
    } else {
        CLEAR_LED(5);
    }

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

    char send_char = send_chars[eeprom_read_byte(CHAR_ADDRESS)];
    interval_time = interval_times[eeprom_read_byte(INTERVAL_ADDRESS)];

    while (true) {
        if (sendRequired > 0) {
            util_send_char(send_char, &set_send_out);
            sendRequired--;
        }

        bool dip_position = io_get_filtered_dip(50);

        if (dip_position) { // Interval
            uint8_t interval_step = util_add_new_measurent(&interval_filter, adc_read_synchr(2));
            interval_time = interval_times[interval_step];
            eeprom_update_byte(INTERVAL_ADDRESS, interval_step);
            io_led_show_binary(2, 3, interval_step);
        } else { // Character
            uint8_t char_step = util_add_new_measurent(&char_filter, adc_read_synchr(2));
            send_char = send_chars[char_step];
            eeprom_update_byte(CHAR_ADDRESS, char_step);
            io_led_show_binary(2, 3, char_step);
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