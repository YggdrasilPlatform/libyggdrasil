/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file midgard/driver/uart.hpp                                  *
  *  @ingroup midgard                                               *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief UART abstraction implementation for Midgard  		    *
  *  			                                                    *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#pragma once

#include <common/driver/spi.hpp>

#include <string>
#include <string_view>
#include <array>

#include <cmsis_gcc.h>

namespace bsp::mid::drv {

	template<auto Context>
	struct SPI {

		template<size_t N>
		ALWAYS_INLINE static void read(std::array<u8, N> &data) {
			HAL_SPI_Receive(Context, const_cast<u8*>(data.data()), data.size(), HAL_MAX_DELAY);
		}

		template<size_t N>
		ALWAYS_INLINE static void write(const std::array<u8, N> &data) {
			HAL_SPI_Transmit(Context, const_cast<u8*>(data.data()), data.size(), HAL_MAX_DELAY);
		}
	private:

	};

}
