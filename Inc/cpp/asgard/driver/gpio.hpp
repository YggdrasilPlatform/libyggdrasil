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
  *  @file asgard/driver/gpio.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief GPIO Pin abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/gpio.hpp>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

namespace bsp::asg::drv {

	namespace {

		/**
		 * @brief Register map for used registers
		 */
		enum class RegisterMap {
			IDR = 0x10,		///< Input data register
			ODR = 0x14,		///< Output data register
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

	private:
	    GPIOPin() = default;

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

		/**
		 * @brief Declare GPIOPort as friend
		 */
	    template<addr_t, template<addr_t,u8> typename>
		friend struct bsp::asg::drv::GPIOPort;
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

		bool init() {
			int fd = open("/dev/mem", O_RDWR);
			mmap(reinterpret_cast<void*>(BaseAddress), GPIOSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BaseAddress);
			close(fd);

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

		private:
			constexpr static inline auto GPIOSize = 0x0400;
	};

}
