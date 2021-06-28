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
  *  @file c/yggdrasil/peripherals/rtc.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the RV-3028-C7 RTC
  */

#pragma once

#include <c/yggdrasil/types.h>

#include <time.h>

/**
 * @brief Initialization function
 *
 * @return Success
 */
C_LINKAGE bool yggdrasil_RealTimeClock_Init(void);

/**
 * @brief Get the time saved in the RTC
 *
 * @return Time saved in the RTC
 */
C_LINKAGE time_t yggdrasil_RealTimeClock_GetTime(void);

/**
 * @brief Set the time in the RTC
 *
 * @param time Time to save in the RTC
 */
C_LINKAGE void yggdrasil_RealTimeClock_SetTime(time_t time);
