/**
 * @file util.h
 * @author paul
 * @date 24.02.19
 * @brief several utility functions used for io
 */

#ifndef ARDF_FIRMWARE_UTIL_H
#define ARDF_FIRMWARE_UTIL_H

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"

/*
 * To decrease the write cycles on the eeprom it is of great importance to remove all noise
 * from the analogue measurements. This modules applies an low pass (using exponential smoothing)
 * and then quantizes the measured value using a fixed number of steps. This value is filtered using
 * a multivalue schmitt-trigger.
 */
typedef struct {
    uint8_t steps;
    uint8_t val;
    uint16_t _mem;
    uint8_t low_pass_weight;
    uint16_t max_val;
} util_quantized_low_pass_t;

/**
 ** Generate an quantized_low_pass_t object from a given set of parameters.
 * @param steps the number of steps to use
 * @param low_pass_weight the 1-alpha value used in exponential smoothing
 * @param max_val the maximum measured value (2^Resolution)
 * @return an quantized_low_pass_t object
 */
util_quantized_low_pass_t util_init_quantizized_low_pass(uint8_t steps, uint8_t low_pass_weight,
        uint16_t max_val);

/**
 * Add a new measurement to the filter. This calculates the filtered step ans returns it.
 * @param quantizized_low_pass the object generated by the init function
 * @param measurement the new measured value
 * @return the estimated step.
 */
uint8_t util_add_new_measurent(util_quantized_low_pass_t* quantizized_low_pass, uint16_t measurement);


/**
 * Modulates the morse code using the send_en pin, this sends the same signal to led1
 * @param c the character, if this is not an alphabetic character nothing will be send
 * @param outputFunc a functor which accepts a boolean and sets an output
 * @param delayFunc a functor which provides a delay in milliseconds
 */
void util_send_char(char c, void (*outputFunc)(bool), void (*delayFunc)(double));


#endif //ARDF_FIRMWARE_UTIL_H
