/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file common/driver/spi.hpp                                    *
  *  @ingroup common                                                *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Base class for the SPI abstraction				 		*
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

	template<auto Context, template<auto> typename SPIImpl>
	struct SPI {
		SPI() = delete;

		using Impl = SPIImpl<Context>;

		template<typename T>
		static T read(u8 address, u8 reg) {
			std::array<u8, sizeof(T)> data;
			Impl::write(address, std::array<u8, 1>{ reg });
			Impl::read(address, data);

			return bit_cast<T>(data);
		}

		template<typename T>
		static void write(T value) {
			std::array<u8, sizeof(T)> data;
			std::memcpy(data.data(), &value, sizeof(T));
			Impl::write(data);
		}
	};
}
