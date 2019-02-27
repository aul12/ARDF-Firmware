/**
 * @file util.c
 * @author paul
 * @date 24.02.19
 * @brief implementation of the utility functions
 */

#include "util.h"
#include "adc.h"
#include "io.h"

#include <stdlib.h>
#include <util/delay.h>

/*
 * For further information on the length of a DIT and what a DIT is refer to:
 * https://en.wikipedia.org/wiki/Morse_code
 */
#define DIT 240

#define PULSE(len_on, len_off) (*output_func)(true);\
    _delay_ms(len_on); \
    (*output_func)(false); \
    _delay_ms(len_off);

#define LONG PULSE(3*DIT, DIT)
#define SHORT PULSE(DIT, 2*DIT)

#define R_TOP 82
#define R_BOTTOM 47
#define VCC 5

util_quantized_low_pass_t util_init_quantizized_low_pass(uint8_t steps,
        uint8_t low_pass_weight, uint16_t max_val) {
    util_quantized_low_pass_t result;
    result.low_pass_weight = low_pass_weight;
    result.steps = steps;
    result._mem = 0;
    result.val = 0;
    result.max_val = max_val;
    return result;
}

uint8_t util_add_new_measurent(util_quantized_low_pass_t *quantizized_low_pass, uint16_t measurement) {
    uint16_t val =
            (uint16_t)((uint32_t)quantizized_low_pass->_mem * quantizized_low_pass->low_pass_weight + measurement)/
                    (quantizized_low_pass->low_pass_weight + 1);
    uint16_t step_size = quantizized_low_pass->max_val / quantizized_low_pass->steps;
    uint8_t raw_step = (uint8_t) (val / step_size);
    uint16_t delta_to_middle = abs(raw_step * step_size + step_size/2 - val);
    if (delta_to_middle < step_size / 4) {
        quantizized_low_pass->val = raw_step;
    }

    return quantizized_low_pass->val;
}

void util_send_char(char c, void (*output_func)(bool)) {
    if (c >= 'A' && c <= 'Z') {
        c = (char) (c - 'A' + 'a'); // Convert to lower case
    }

    if (c < 'a' || c > 'z') {
        return;
    }

    switch (c) {
        case 'a': SHORT LONG break;
        case 'b': LONG SHORT SHORT SHORT break;
        case 'c': LONG SHORT LONG SHORT break;
        case 'd': LONG SHORT SHORT break;
        case 'e': SHORT break;
        case 'f': SHORT SHORT LONG SHORT break;
        case 'g': LONG LONG SHORT break;
        case 'h': SHORT SHORT SHORT SHORT break;
        case 'i': SHORT SHORT break;
        case 'j': SHORT LONG LONG LONG break;
        case 'k': LONG SHORT LONG break;
        case 'l': SHORT LONG SHORT SHORT break;
        case 'm': LONG LONG break;
        case 'n': LONG SHORT break;
        case 'o': LONG LONG LONG break;
        case 'p': SHORT LONG LONG SHORT break;
        case 'q': LONG LONG SHORT LONG break;
        case 'r': SHORT LONG SHORT break;
        case 's': SHORT SHORT SHORT break;
        case 't': LONG break;
        case 'u': SHORT SHORT LONG break;
        case 'v': SHORT SHORT SHORT LONG break;
        case 'w': SHORT LONG LONG break;
        case 'x': LONG SHORT SHORT LONG break;
        case 'y': LONG SHORT LONG LONG break;
        case 'z': LONG LONG SHORT SHORT break;
        default:  SET_LED(5); break; // We really shouldn't be here!
    }
}

uint16_t util_battery_voltage_milli_volt(void) {
    static uint16_t last_voltage = 12600;
    uint16_t voltage = adc_read_synchr(1) * VCC / R_BOTTOM * (R_TOP + R_BOTTOM);
    last_voltage = (voltage + last_voltage * 9) / 10;
    return last_voltage;
}
