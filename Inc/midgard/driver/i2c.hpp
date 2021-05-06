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

namespace bsp::mid::drv {

	/**
	 * @brief I2C implementation for Midgard
	 * @warn Do not use this on its own!
	 *
	 * @tparam Context I2C context
	 */
	template<auto Context>
	struct I2C {

		/**
		 * @brief I2C receive
		 *
		 * @tparam N Data size
		 * @param address Device address
	     * @param data Array for the read data
		 */
		template<size_t N>
		ALWAYS_INLINE static void read(u8 address, std::array<u8, N> &data) {
			HAL_I2C_Master_Receive(Context, address, data.data(), data.size(), HAL_MAX_DELAY);
		}

		/**
		 * @brief I2C write
		 *
		 * @tparam N Data size
		 * @param address Device address
	     * @param data Array to send
		 */
		template<size_t N>
		ALWAYS_INLINE static void write(u8 address, const std::array<u8, N> &data) {
			HAL_I2C_Master_Transmit(Context, address, const_cast<u8*>(data.data()), data.size(), HAL_MAX_DELAY);
		}
	};

}
