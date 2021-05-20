 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
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
  *  @file cpp/midgard/core/cache.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Cache related constants and functions
  */

#pragma once

#include <cpp/common/types.hpp>
#include <cpp/common/attributes.hpp>

#include <cpp/midgard/core/instructions.hpp>

#include <core_cm7.h>

namespace bsp::core {

	constexpr auto DCacheLineSize = 32; ///< Size of one Data Cache Line
	constexpr auto ICacheLineSize = 32; ///< Size of one Instruction Cache Line

	/**
	 * @brief Invalidates the entire ICache
	 */
	ALWAYS_INLINE void invalidateICache() {
		DSB();
		ISB();

		SCB->ICIALLU = 0UL;

		DSB();
		ISB();
	}

	/**
	 * @brief Invalidates all possibly cached instructions in a specific region of memory
	 * @param address Start address of the region
	 * @param size Size of the region
	 */
	ALWAYS_INLINE void invalidateICache(void *address, size_t size) {
		if (size > 0) {
			addr_t invalidateAddress = reinterpret_cast<addr_t>(address);
			ssize_t invalidateSize = size + (invalidateAddress & (ICacheLineSize - 1));

			DSB();

			do {
				SCB->ICIMVAU = invalidateAddress;

				invalidateAddress += ICacheLineSize;
				invalidateSize -= ICacheLineSize;
			} while (invalidateSize > 0);

			DSB();
			ISB();
		}
	}

}
