/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file asgard/driver/gpio.hpp                                   *
  *  @ingroup asgard                                                *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief GPIO Pin abstraction implementation for Asgard   		*
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

#include <common/driver/gpio.hpp>

namespace bsp::asg::drv {

	namespace {

		/**
		 * @brief Register map for used registers
		 */
		enum class RegisterMap {
			IDR = 0x10,
			ODR = 0x14,
		};

	}


	template<addr_t BaseAddress>
	struct GPIOPort;

	/**
	 * @brief GPIOPin implementation for Asgard
	 * @warning Do not use this on its own!
	 * @tparam BaseAddress GPIO Block base address
	 * @tparam Pin Pin number
	 */
	template<addr_t BaseAddress, u8 Pin, bsp::drv::Active LogicActive>
	struct GPIOPin {
	private:
		GPIOPin() = default;
	public:
		GPIOPin(const GPIOPin&) = delete;
		GPIOPin(GPIOPin&&) = delete;

	    static_assert(Pin <= 15, "Pin out of range");

	    GPIOPin& operator=(const GPIOPin&) = delete;

	    /**
	     * @brief Assignment operator overload
	     * @param state Pin state
	     * @return Pin
	     */
	    ALWAYS_INLINE constexpr auto& operator=(bool state) const noexcept {
	        ODRx = LogicActive == bsp::drv::Active::High ? state : !state;

	        return *this;
	    }

	    /**
	     * @brief u8 conversion operator overload
	     * @return Pin value
	     */
	    [[nodiscard]] ALWAYS_INLINE constexpr operator u8() const noexcept {
	        return LogicActive == bsp::drv::Active::High ? IDRx : !IDRx;
	    }

	private:

		/**
		 * @brief IDR register
		 */
	    using IDR 	= Register<BaseAddress, RegisterMap::IDR, u32>;
	    static inline auto IDRx = typename IDR::template Field<Pin, Pin>();

	    /**
	     * @brief ODR register
	     */
	    using ODR 	= Register<BaseAddress, RegisterMap::ODR, u32>;
	    static inline auto ODRx = typename ODR::template Field<Pin, Pin>();

	    template<addr_t, template<addr_t,u8> typename>
		friend struct bsp::asg::drv::GPIOPort;
	};

	template<addr_t BaseAddress>
	struct GPIOPort {
	private:
		GPIOPort() = default;
	public:
		GPIOPort(const GPIOPort&) = delete;
		GPIOPort(GPIOPort&&) = delete;

	private:
	    using IDR 	= Register<BaseAddress, RegisterMap::IDR, u32>;
	    using ODR 	= Register<BaseAddress, RegisterMap::ODR, u32>;

	public:
		template<u8 Pin, bsp::drv::Active LogicActive>
		static constexpr auto Pin = GPIOPin<BaseAddress, Pin, LogicActive>();

		template<u8 From, u8 To>
		static constexpr auto In = typename IDR::template Field<From, To>();

		template<u8 From, u8 To>
		static constexpr auto Out = typename ODR::template Field<From, To>();
	};

}
