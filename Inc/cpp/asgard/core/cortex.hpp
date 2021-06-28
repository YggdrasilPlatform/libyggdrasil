 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file cpp/asgard/core/cortex.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Core control functions for Asgard
  */

#pragma once

#include <cpp/common/types.hpp>
#include <cpp/common/attributes.hpp>

#include <time.h>

namespace bsp::core {

	/**
	 * @brief Delays execution by a certain number of milliseconds
	 * @param ms Number of milliseconds to wait
	 */
	ALWAYS_INLINE void delay(u32 ms) {
        struct timespec ts;
        ts.tv_sec = ms / 1'000;
        ts.tv_nsec = (ms % 1'000) * 1'000'000;

        int res;
        do {
            res = nanosleep(&ts, &ts);
        } while (res);
	}

}
