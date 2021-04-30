/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file common/driver/i2c.hpp                                    *
  *  @ingroup common                                                *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Base class for the I2C abstraction				 		*
  *  									                       		*
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

#include <common/registers.hpp>
#include <common/attributes.hpp>
#include <common/utils.hpp>

#include <array>

namespace bsp::drv {

	template<auto Context, template<auto> typename I2CImpl>
	struct I2C {
		I2C() = delete;


		using Impl = I2CImpl<Context>;

		template<typename T>
		static T read(u8 address) {
			std::array<u8, sizeof(T)> data;
			Impl::read(address, data);

			return bit_cast<T>(data);
		}

		template<typename T>
		static T read(u8 address, u8 reg) {
			std::array<u8, sizeof(T)> data;
			Impl::write(address, std::array<u8, 1>{ reg });
			Impl::read(address, data);

			return bit_cast<T>(data);
		}

		static void write(u8 address, auto value) {
			std::array<u8, sizeof(value)> data;
			std::memcpy(data.data(), &value, sizeof(value));

			Impl::write(address, data);
		}

		static void write(u8 address, u8 reg, auto value) {
			std::array<u8, sizeof(value) + 1> data;
			data[0] = reg;
			std::memcpy(data.data() + 1, &value, sizeof(value));

			Impl::write(address, data);
		}
	};
}
