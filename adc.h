/**
 * @file adc.h
 * @author paul
 * @date 23.02.19
 * @brief declaration of the adc library
 */

#ifndef ARDF_FIRMWARE_ADC_H
#define ARDF_FIRMWARE_ADC_H

#include <stdint.h>

/**
 * Reads the 10 bit ADC value of the selected channel. This function is blocking / synchronous.
 * Vcc is selected as the reference voltage.
 * @param adcChannel the channel must be in between 0 and 7 (inclusive)
 * @return the value between 0 and 1023 (inclusive)
 */
uint16_t adc_read_synchr(uint8_t adcChannel);

#endif //ARDF_FIRMWARE_ADC_H
