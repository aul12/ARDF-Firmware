/**
 * @file io.c
 * @author paul
 * @date 24.02.19
 * @brief io @TODO
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

    if (high_count < thresh) {
        return (last_val = false);
    } else if (high_count > (num_of_samples - thresh)){
        return (last_val = true);
    } else {
        return last_val;
    }
}
