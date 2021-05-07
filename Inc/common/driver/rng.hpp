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
  *  @file common/driver/rng.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the RNG abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>

#include <array>

namespace bsp::drv {

	/**
	 * @brief Base class for the RNG abstraction
	 *
	 * @tparam BaseAddress RNG Peripheral Base address
	 * @tparam RandomImpl Random Implementation
	 */
	template<addr_t BaseAddress, template<addr_t> typename RandomImpl>
	struct Random {
		Random() = delete;
		Random(const Random&) = delete;
		auto operator=(const Random&) = delete;

		using Impl = RandomImpl<BaseAddress>;

		/**
		 * @brief Get random values seeded by true entropy
		 *
		 * @tparam T Type of data to get. Must be default and trivially constructible
		 */
		template<typename T>
		static T get() {
			return Impl::template get<T>();
		}

	};

}
