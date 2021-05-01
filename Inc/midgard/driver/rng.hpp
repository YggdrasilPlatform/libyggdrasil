/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file midgard/driver/rng.hpp                                   *
  *  @ingroup midgard                                               *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief RNG abstraction implementation for Midgard 				*
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

#include <common/driver/rng.hpp>

#include <common/registers.hpp>
#include <common/attributes.hpp>

#include <array>
#include <cmath>

namespace bsp::mid::drv {

	/**
	 * @brief RNG abstraction
	 * @tparam BaseAddress RNG Peripheral base address
	 */
	template<addr_t BaseAddress>
	struct Random {
		Random() = delete;
		Random(const Random&) = delete;
		auto operator=(const Random&) = delete;

		/**
		 * @brief Get random values seeded by true entropy
		 * @tparam T Type of data to get. Must be default and trivially constructible
		 */
		template<typename T>
		[[nodiscard]] static T get() noexcept {
			T data;

			RNGEN = true;
			for (u32 offset = 0; offset < sizeof(T); offset += sizeof(u32)) {
				while (!DRDY);

				u32 rng = RNGDATA;
				std::memcpy(&data, &rng, std::min(u32(sizeof(u32)), sizeof(T) - offset));
			}
			RNGEN = false;

			return data;
		}

	private:
		enum class RegisterMap : u8 {
			CR = 0x00,
			SR = 0x04,
			DR = 0x08,

		};

	    using CR = Register<BaseAddress, RegisterMap::CR, u32>;
	    using SR = Register<BaseAddress, RegisterMap::SR, u32>;
	    using DR = Register<BaseAddress, RegisterMap::DR, u32>;

	    static inline auto RNGEN 	= typename CR::template Field<2, 2>();
	    static inline auto DRDY 	= typename SR::template Field<0, 0>();
	    static inline auto RNGDATA 	= typename DR::template Field<0, 31>();
	};

}
