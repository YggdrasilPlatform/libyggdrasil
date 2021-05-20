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
  *  @file cpp/common/frontend/i2c.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the I2C abstraction
  */

#pragma once

#include <cpp/common/registers.hpp>
#include <cpp/common/attributes.hpp>
#include <cpp/common/utils.hpp>

#include <array>

namespace bsp::drv {

	/**
	 * @brief Base class for I2C abstraction
	 *
	 * @tparam Context I2C context
	 * @tparam I2CImpl I2C implementation
	 */
	template<auto Context, template<auto> typename I2CImpl>
	struct I2C {
		I2C() = delete;

		using Impl = I2CImpl<Context>;

		static bool init(auto ... args) {
			return Impl::init(args...);
		}

	    /**
	     * @brief I2C read function
	     *
	     * @tparam T type to read
	     * @param address Device address
	     * @return Read data
	     */
		template<typename T>
		static T read(u8 address) {
			std::array<u8, sizeof(T)> data;
			Impl::read(address, data);

			return bit_cast<T>(data);
		}

	    /**
	     * @brief I2C read function
	     *
	     * @tparam T type to read
	     * @param address Device address
	     * @param reg Register address
	     * @return Read data
	     */
		template<typename T>
		static T read(u8 address, u8 reg) {
			std::array<u8, sizeof(T)> data;
			Impl::write(address, std::array<u8, 1>{ reg });
			Impl::read(address, data);

			return bit_cast<T>(data);
		}

	    /**
	     * @brief I2C write function
	     *
	     * @tparam T type to write
	     * @param address Device address
	     * @param value Data to write
	     */
		template<typename T>
		static void write(u8 address, T value) {
			std::array<u8, sizeof(T)> data;
			std::memcpy(data.data(), &value, sizeof(T));

			Impl::write(address, data);
		}

	    /**
	     * @brief I2C write function
	     *
	     * @tparam T type to write
	     * @param address Device address
	     * @param reg Register address
	     * @param value Data to write
	     */
		template<typename T>
		static void write(u8 address, u8 reg, T value) {
			std::array<u8, sizeof(T) + 1> data;
			data[0] = reg;
			std::memcpy(data.data() + 1, &value, sizeof(T));

			Impl::write(address, data);
		}
	};
}
