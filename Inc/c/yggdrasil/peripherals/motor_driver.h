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
  *  @file c/yggdrasil/peripherals/motor_driver.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the TC78H660FTG DC motor driver
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Motor driver Channels
 */
enum MotorDriverChannel {
	MotorDriverChannel_A = 0,		///< Channel A
	MotorDriverChannel_B = 1,		///< Channel B
};
/**
 * @brief init function for the motor as a dual channel dc driver
 * @note this function does start the needed pwm generators
 *
 * @return Success
 */
C_LINKAGE void yggdrasil_MotorDriver_Init(void);

/**
 * @brief set the motor driver to standby
 *
 * @param stby True for standby, false for active
 */
C_LINKAGE void yggdrasil_MotorDriver_Standby(bool stby);

/**
 * @brief Controls the speed and rotation of each channel
 *
 * @param ch Channel to set speed
 * @param speed Speed from -100% o 100% where - does change the rotation direction
 */
C_LINKAGE void yggdrasil_MotorDriver_SetSpeed(enum MotorDriverChannel channel, float speed);

/**
 * @brief get the Status from the motor driver
 *
 * @return false when no error occurring, true when in thermal shutdown (TSD) or over current (ISD)
 */
C_LINKAGE bool yggdrasil_MotorDriver_GetError(void);


