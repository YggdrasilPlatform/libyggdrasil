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
  *  @file cpp/midgard/driver/spi.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief SPI abstraction implementation for Midgard
  */

#pragma once

#include <cpp/common/frontend/spi.hpp>

#include <string>
#include <string_view>
#include <array>
extern SPI_HandleTypeDef hspi2;
namespace bsp::mid::drv {

	/**
	 * @brief SPI implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context SPI context
	 */
	template<auto Context>
	struct SPI {

		/**
		 * @brief SPI initialization
		 */
		static bool init() {
			return true;
		}

		/**
		 * @brief SPI receive
		 *
		 * @tparam N Data size
	     * @param data Array for the read data
		 */
		template<size_t N>
		static void read(std::array<u8, N> &data) {
			HAL_SPI_Receive(Context, data.data(), data.size(), HAL_MAX_DELAY);
		}

		/**
		 * @brief SPI write
		 *
		 * @tparam N Data size
	     * @param data Array to send
		 */
		template<size_t N>
		static void write(const std::array<u8, N> &data) {
			HAL_SPI_Transmit(Context, const_cast<u8*>(data.data()), data.size(), HAL_MAX_DELAY);
		}


		/**
		 * @brief Set the spi mode (CPOL and CPHA)
		 *
		 * @param mode SPI mode
		 * @note This function wait until the SPI is not busy anymore and then the mode change will take place
		 */
		static void setMode(bsp::drv::SPIMode mode) {
			while (HAL_SPI_GetState(Context) == HAL_SPI_STATE_BUSY);
			Context->Instance->CR1 = (Context->Instance->CR1 & ~0b11) | enumValue(mode);
		}

	};

}
