 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file cpp/asgard_coproc/driver/rng.hpp
  *  @ingroup asgard_coproc
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief RNG abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/rng.hpp>

#include <cpp/common/registers.hpp>
#include <cpp/common/attributes.hpp>

#include <array>
#include <cmath>

namespace bsp::asg_coproc::drv {

	/**
	 * @brief RNG abstraction for Asgard
	 *
	 * @warning Do not use this on its own!
	 *
	 * @tparam BaseAddress RNG Peripheral base address
	 */
	template<addr_t BaseAddress>
	struct Random {
		Random() = delete;
		Random(const Random&) = delete;
		auto operator=(const Random&) = delete;

		/**
		 * @brief Init function
		 *
		 * @return Success
		 */
		static bool init() {
			return true;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return Success
		 */
		static bool deinit() {
			return true;
		}

		/**
		 * @brief Get random values seeded by true entropy
		 *
		 * @tparam T Type of data to get. Must be default and trivially constructible
		 */
		template<typename T>
		[[nodiscard]] static T get() noexcept {
			T data;

			RNGEN = true;																	// Enable rng
			for (u32 offset = 0; offset < sizeof(T); offset += sizeof(u32)) {				// Always get 4 baytes of random data
				while (!DRDY);																// Wait for the rng to finish

				u32 rng = RNGDATA;															// Get random data (4 bytes)
				std::memcpy(&data, &rng, std::min(u32(sizeof(u32)), sizeof(T) - offset));	// Fill up 4 bytes to the Type T
			}
			RNGEN = false;																	// Disable rng

			return data;																	// Return random data
		}

	private:
		enum class RegisterMap : u8 {
			CR = 0x00,		///< Control register
			SR = 0x04,		///< Status register
			DR = 0x08,		///< Data register

		};

	    using CR = Register<BaseAddress, RegisterMap::CR, u32>;
	    using SR = Register<BaseAddress, RegisterMap::SR, u32>;
	    using DR = Register<BaseAddress, RegisterMap::DR, u32>;

	    static inline auto RNGEN 	= typename CR::template Field<2, 2>();		///< True random number generator enable
	    static inline auto DRDY 	= typename SR::template Field<0, 0>();		///< Data Ready
	    static inline auto RNGDATA 	= typename DR::template Field<0, 31>();		///< Random data
	};

}
