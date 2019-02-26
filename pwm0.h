/**
 * @file pwm0.h
 * @author paul
 * @date 26.02.19
 * @brief pwm0 @TODO
 */

#ifndef ARDF_FIRMWARE_PWM0_H
#define ARDF_FIRMWARE_PWM0_H

#include <stdint.h>

/**
 * Initialize timer0 to use the OC0A (PB2) as a pwm output.
 */
void pwm0_init(void);

/**
 * Set the duty cycle of the pwm
 */
void pwm0_set(uint8_t duty_cycle);

#endif //ARDF_FIRMWARE_PWM0_H
