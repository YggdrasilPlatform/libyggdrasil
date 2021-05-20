 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
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
  *  @file common/driver/spi.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the SPI abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>
#include <common/utils.hpp>

#include <array>
#include <type_traits>

namespace bsp::drv {

	enum class SPIMode:u8 {
		_0 = 0b00,  	///< CPOL = 0  |  CPHA = 0
		_1 = 0b01,		///< CPOL = 0  |  CPHA = 1
		_2 = 0b10,		///< CPOL = 1  |  CPHA = 0
		_3 = 0b11,		///< CPOL = 1  |  CPHA = 1
	};

	/**
	 * @brief Base class for SPI abstraction
	 *
	 * @tparam Context SPI context
	 * @tparam SPIImpl SPI implementation
	 */
	template<addr_t BaseAddress, template<auto> typename SPIImpl>
	struct SPI {
		SPI() = delete;

		using Impl = SPIImpl<BaseAddress>;

	    /**
	     * @brief SPI read function
	     *
	     * @tparam T type to read
	     * @return Read data
	     */
		template<typename T>
		static T read() {
			std::array<u8, sizeof(T)> data;
			Impl::read(data);

			return bit_cast<T>(data);
		}

	    /**
	     * @brief SPI write function
	     *
	     * @tparam T type to write
	     * @param value Data to write
	     */
		template<typename T>
		static void write(const T &value) {
			if constexpr (std::is_pointer<T>::value) {
				constexpr size_t Size = sizeof(std::remove_pointer<T>);

				std::array<u8, Size> data;
				std::memcpy(data.data(), value, Size);
				Impl::write(data);
			} else {
				constexpr size_t Size = sizeof(T);

				std::array<u8, Size> data;
				std::memcpy(data.data(), &value, Size);
				Impl::write(data);
			}

		}

		/**
		 * @brief Set the spi mode (CPOL and CPHA)
		 *
		 * @param mode SPI mode
		 * @note This function wait until the SPI is not busy anymore and then the mode change will take place
		 */
		static void setMode(SPIMode mode) {
			Impl::setMode(mode);
		}
	};
}
