/**
 * @file Timer16Bit.h
 * @author paul
 * @date 23.02.19
 * @brief Timer16Bit @TODO
 */

#ifndef ARDF_FIRMWARE_TIMER16BIT_H
#define ARDF_FIRMWARE_TIMER16BIT_H

#include <stdint.h>

#define TIMER1_GET_FREQ(prescaler) ((float)F_CPU/((prescaler)*65536))

/**
 * Possible values for the prescaler for the 16-bit timer, these values correspond to the table
 * on page 109.
 */
typedef enum {
    PRESCALER_1 = 0x01,
    PRESCALER_8 = 0x02,
    PRESCALER_64 = 0x03,
    PRESCALER_256 = 0x04,
    PRESCALER_1024 = 0x05,
    PRESCALER_INF = 0x00
} prescaler_t;

void timer1_init(prescaler_t prescaler, void (*callback)(void));

#endif //ARDF_FIRMWARE_TIMER16BIT_H
