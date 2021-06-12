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

C_LINKAGE void yggdrasil_SinkDriver_Servo_Set(enum SinkDriverChannel channel, float percent);
C_LINKAGE void yggdrasil_SinkDriver_Servo_SetDeltaHighTime(enum SinkDriverChannel channel, u16 delta);

C_LINKAGE void yggdrasil_SinkDriver_PWM_SetDuty(enum SinkDriverChannel channel, float dutyCycle);
C_LINKAGE bool yggdrasil_SinkDriver_PWM_SetFrequency(u32 frequency, u16 resolution);
C_LINKAGE u32  yggdrasil_SinkDriver_PWM_GetFrequency();

C_LINKAGE void yggdrasil_SinkDriver_Out_Set(enum SinkDriverChannel channel, bool state);

