/**
 * @file util.c
 * @author paul
 * @date 24.02.19
 * @brief util @TODO
 */

#include "util.h"

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

void util_send_char(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = (char) (c - 'A' + 'a'); // Convert to lower case
    }

    if (c < 'a' || c > 'z') {
        return;
    }

    //@TODO
}
