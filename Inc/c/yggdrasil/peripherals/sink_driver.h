 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Yggdrasil -                           *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
  *  @file c/yggdrasil/peripherals/sink_driver.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the sink drivers
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Sink Driver Timer Channels
 */
enum SinkDriverChannel {
	SinkDriverChannel_A = 0,		///< Timer channel A
	SinkDriverChannel_B = 1,		///< Timer channel B
	SinkDriverChannel_C = 2,		///< Timer channel C
	SinkDriverChannel_D = 3,		///< Timer channel D
};

/**
 * @brief Initialization function
 *
 * @return Success
 */
C_LINKAGE void yggdrasil_SinkDriver_Init(void);

/**
 * @brief Set the servo arm rotation in percent relative to its maximal value
 * @note The needed high period of pwm signal to reach maximal magnitude can
 * be configured with the setDeltaHighTime() function (This is servo specific)
 * @warning If the system clock is not above 200MHz the function might not be able to set the pwm frequency to 50Hz
 *
 * @param channel Channel which should be changed
 * @param percent Servo arm rotation in percent from -100% to 100%
 */
C_LINKAGE void yggdrasil_SinkDriver_Servo_Set(enum SinkDriverChannel channel, float percent);

/**
 * @brief FUnction to set the high time of the pwm pulse
 *
 * @param channel Channel which should be changed
 * @param delta High time of the pwm pulse in ms
 */
C_LINKAGE void yggdrasil_SinkDriver_Servo_SetDeltaHighTime(enum SinkDriverChannel channel, u16 delta);


/*
 * @brief Set the duty cycle
 *
 * @param channel Channel which should be changed
 * @param dutyCycle Duty cycle
 */
C_LINKAGE void yggdrasil_SinkDriver_PWM_SetDuty(enum SinkDriverChannel channel, float dutyCycle);

/**
 * @brief Set the pwm frequency and (optional) the maximal ticks within on cycle for all channels
 * @note The actual duty cycle for all channels will be restored after the changes
 * @note Implement a proper error handling, the function does not guarantee to be successful
 * @warning When one channel is used as servo port, the frequency can not be changed
 *
 * @param f_hz new frequency in hz
 * @param resolution of the pwm, for 0 the actual value will be used
 *
 * @return True when the adjustment was possible, false when the parameter did not match
 */
C_LINKAGE bool yggdrasil_SinkDriver_PWM_SetFrequency(u32 frequency, u16 resolution);

/**
 * @brief Get the pwm frequency
 * @note The frequency is for all channels the same
 *
 * @param channel Channel, this is used when not all channels are from the same timer
 * @return Frequency in Hz
 */
C_LINKAGE u32  yggdrasil_SinkDriver_PWM_GetFrequency(enum SinkDriverChannel channel);


/**
 * @brief set the sink driver pin state
 *
 * @param channel Channel to set
 * @param state Pin state
 */
C_LINKAGE void yggdrasil_SinkDriver_Out_Set(enum SinkDriverChannel channel, bool state);

