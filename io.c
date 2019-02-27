/**
 * @file io.c
 * @author paul
 * @date 24.02.19
 * @brief library for abstraction of all digital io
 */

#include "io.h"
#include <util/delay.h>

// Get the measured value of the DIP switch
#define GET_DIP ((PINB >> 1) & 0x01)

void io_init(void) {
    DDRA = 0xF9; // Set input / output modes for register a
    DDRB = 0x04; // Set input / output modes for register b

    PORTB |= (0x01 << 1); // Enable the Pull-Up for PB1
}

bool io_get_filtered_dip(uint8_t num_of_samples) {
    static uint8_t last_val = false;
    uint8_t high_count = 0;
    for (uint8_t c = 0; c < num_of_samples; c++) {
        if (GET_DIP) {
            high_count++;
        }
        _delay_ms(2);
    }

    uint8_t thresh = (uint8_t) (num_of_samples / 10);

    if (high_count <= thresh) {
        return (last_val = false);
    } else if (high_count >= (num_of_samples - thresh)){
        return (last_val = true);
    } else {
        return last_val;
    }
}

void io_led_show_binary(uint8_t led_start, uint8_t num_of_leds, uint8_t val) {
    for (uint8_t led = 0; led < num_of_leds; ++led) {
        uint8_t bit = (uint8_t) ((val >> led) & 0x01);
        if (bit) {
            SET_LED(led + led_start);
        } else {
            CLEAR_LED(led+led_start);
        }
    }
}
