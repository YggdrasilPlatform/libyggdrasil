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
  *  @file cpp/asgard_coproc/driver/gpio.hpp
  *  @ingroup asgard_coproc
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief GPIO Pin abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/gpio.hpp>

namespace bsp::asg_coproc::drv {

	namespace {

		/**
		 * @brief Register map for used registers
		 */
		enum class RegisterMap {
			MODER 	= 0x00,		///< Mode register
			OTYPER	= 0x04,		///< Output type register
			IDR 	= 0x10,		///< Input data register
			ODR 	= 0x14,		///< Output data register
		};

	}


	// Forward declaring
	template<addr_t BaseAddress>
	struct GPIOPort;

	/**
	 * @brief GPIOPin implementation for Asgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam BaseAddress GPIO Block base address
	 * @tparam Pin Pin number
	 */
	template<addr_t BaseAddress, u8 Pin, bsp::drv::Active LogicActive>
	struct GPIOPin {
		GPIOPin(const GPIOPin&) = delete;
		GPIOPin(GPIOPin&&) = delete;

	    static_assert(Pin <= 15, "Pin out of range");

	    GPIOPin& operator=(const GPIOPin&) = delete;

	    /**
	     * @brief Assignment operator overload
	     *
	     * @param state Pin state
	     * @return Pin
	     */
	    ALWAYS_INLINE constexpr auto& operator=(bool state) const noexcept {
	        ODRx = LogicActive == bsp::drv::Active::High ? state : !state;

	        return *this;
	    }

	    /**
	     * @brief u8 conversion operator overload
	     *
	     * @return Pin value
	     */
	    [[nodiscard]] ALWAYS_INLINE constexpr operator u8() const noexcept {
	        return LogicActive == bsp::drv::Active::High ? IDRx : !IDRx;
	    }

		/**
		 * @brief Init function
		 *
		 * @return Success
		 */
		bool init() const noexcept {
			return true;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return Success
		 */
		bool deinit() const noexcept {
			return true;
		}

		/**
		 * @brief Turn pin into an output
		 */
		void makeOutput() const noexcept {
			MODERx = 0b01;
			OTYPERx = 0b0;
		}

		/**
		 * @brief Turn pin into an input
		 */
		void makeInput() const noexcept {
			MODERx = 0b00;
		}	

	private:
	    GPIOPin() = default;

		/**
		 * @brief MODER register
		 */
	    using MODER = Register<BaseAddress, RegisterMap::MODER, u32>;
	    static inline auto MODERx = typename MODER::template Field<Pin * 2, Pin * 2 + 1>();

	    /**
	     * @brief OTYPER register
	     */
	    using OTYPER = Register<BaseAddress, RegisterMap::OTYPER, u32>;
	    static inline auto OTYPERx = typename OTYPER::template Field<Pin, Pin>();

		/**
		 * @brief IDR register
		 */
	    using IDR = Register<BaseAddress, RegisterMap::IDR, u32>;
	    static inline auto IDRx = typename IDR::template Field<Pin, Pin>();

	    /**
	     * @brief ODR register
	     */
	    using ODR = Register<BaseAddress, RegisterMap::ODR, u32>;
	    static inline auto ODRx = typename ODR::template Field<Pin, Pin>();

		/**
		 * @brief Declare GPIOPort as friend
		 */
	    template<addr_t, template<addr_t,u8> typename>
		friend struct bsp::asg_coproc::drv::GPIOPort;
	};

	/**
	 * @brief GPIOPort implementation for Asgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam BaseAddress GPIO Block base address
	 */
	template<addr_t BaseAddress>
	struct GPIOPort {
	private:
		GPIOPort() = default;

	    using IDR 	= Register<BaseAddress, RegisterMap::IDR, u32>;
	    using ODR 	= Register<BaseAddress, RegisterMap::ODR, u32>;

    public:
		GPIOPort(const GPIOPort&) = delete;
		GPIOPort(GPIOPort&&) = delete;

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
	     * @brief GPIO Pin
	     *
	     * @tparam Pin Pin number
	     * @tparam LogicActive Logic active state
	     */
		template<u8 Pin, bsp::drv::Active LogicActive>
		static constexpr auto Pin = GPIOPin<BaseAddress, Pin, LogicActive>();

	    /**
	     * @brief Read multiple GPIO Pins
	     * @note These pins must be in a row
	     *
	     * @tparam From Start pin number
	     * @tparam To Stop pin
	     */
		template<u8 From, u8 To>
		static constexpr auto In = typename IDR::template Field<From, To>();

	    /**
	     * @brief Write multiple GPIO Pins
	     * @note These pins must be in a row
	     *
	     * @tparam From Start pin number
	     * @tparam To Stop pin
	     */
		template<u8 From, u8 To>
		static constexpr auto Out = typename ODR::template Field<From, To>();

	};

}
