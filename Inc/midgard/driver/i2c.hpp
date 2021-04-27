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
  *  @brief I2C abstraction implementation for Midgard  		    *
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

#include <common/driver/i2c.hpp>

#include <string>
#include <string_view>
#include <array>

#include <cmsis_gcc.h>

namespace bsp::mid::drv {

	template<auto Context>
	struct I2C {

		template<size_t N>
		ALWAYS_INLINE static void read(u8 address, std::array<u8, N> &data) {
			HAL_I2C_Master_Receive(Context, address, data.data(), data.size(), HAL_MAX_DELAY);
		}

		template<size_t N>
		ALWAYS_INLINE static void write(u8 address, const std::array<u8, N> &data) {
			HAL_I2C_Master_Transmit(Context, address, const_cast<u8*>(data.data()), data.size(), HAL_MAX_DELAY);
		}
	private:

	};

}
