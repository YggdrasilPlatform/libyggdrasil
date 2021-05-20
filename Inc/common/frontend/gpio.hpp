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
  *  @file common/frontend/gpio.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the GPIO abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>

namespace bsp::drv {

	enum class Active {
		Low,
		High
	};

	/**
	 * @brief Base class for GPIO port abstraction
	 *
	 * @tparam Context GPIO context
	 * @tparam GPIOPin GPIOPin implementation
	 */
	template<auto Context, template<addr_t> typename GPIOImpl>
	struct GPIOPort {
	    GPIOPort() = delete;
	    GPIOPort(const GPIOPort&) = delete;
	    GPIOPort(GPIOPort &&) = delete;

		using Impl = GPIOImpl<Context>;

		static bool init(auto ... args) {
			return Impl::init(args...);
		}

	    /**
	     * @brief GPIO Pin
	     *
	     * @tparam Number Pin number
	     */
	    template<u8 Number, Active LogicActive = Active::High>
	    static inline auto& Pin = Impl::template Pin<Number, LogicActive>;

	    /**
	     * @brief Input bitfield
	     *
	     * @tparam Number Pin number
	     */
	    template<u8 From, u8 To>
	    static inline auto& In = Impl::template In<From, To>;

	    /**
	     * @brief Output bitfield
	     *
	     * @tparam Number Pin number
	     */
	    template<u8 From, u8 To>
	    static inline auto& Out = Impl::template Out<From, To>;
	};

}
