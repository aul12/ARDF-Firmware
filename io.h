/**
 * @file io.h
 * @author paul
 * @date 23.02.19
 * @brief implementation of the io library
 */

#ifndef ARDF_FIRMWARE_IO_H
#define ARDF_FIRMWARE_IO_H

#include <avr/io.h>
#include <stdbool.h>

// Enabled / Disable the Send-Enable Pin
#define SET_SEND_EN (PORTA |= 0x01)
#define CLEAR_SEND_EN (PORTA &= ~0x01)

// Set the LED, the first LED is number 1
#define SET_LED(num) (PORTA |= (0x01 << ((num)+ 2)))
#define CLEAR_LED(num) (PORTA &= ~(0x01 << ((num) + 2)))

/**
 * Initialize the gpio-pins as input/output and enable the required pull up
 */
void io_init(void);

/**
 * Estimates an analogue value by calculating an moving average.
 * Then filters the value by using a schmitt-trigger
 * @param num_of_samples the number of samples to take (a sample is taken every 2ms)
 * @return a bool representing the state of the switch
 */
bool io_get_filtered_dip(uint8_t num_of_samples);

/**
 * Shows a binary number on the leds
 * @param led_start the first led to use, this is the LSB
 * @param num_of_leds the number of leds to use
 * @param val the value to show, if this value can't be displayed only the lower bits are used.
 */
void io_led_show_binary(uint8_t led_start, uint8_t num_of_leds, uint8_t val);

#endif //ARDF_FIRMWARE_IO_H
