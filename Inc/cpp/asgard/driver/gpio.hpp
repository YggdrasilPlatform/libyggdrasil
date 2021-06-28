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
  *  @file cpp/asgard/driver/gpio.hpp
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
#include <string>

namespace bsp::asg::drv {

	// Forward declaring
	template<u8 GPIOBaseNumber>
	struct GPIOPort;

	/**
	 * @brief GPIOPin implementation for Asgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam BaseAddress GPIO Block base address
	 * @tparam Pin Pin number
	 */
	template<u8 GPIOBaseNumber, u8 Pin, bsp::drv::Active LogicActive>
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
	    auto& operator=(bool state) const noexcept {
			state = LogicActive == bsp::drv::Active::High ? state : !state;

			int fd = open(("/sys/class/gpio/gpio" + std::to_string(GPIOBaseNumber + Pin) + "/value").c_str(), O_WRONLY);
			if (fd == -1) return *this;

			write(fd, state ? "1" : "0", 1);
			close(fd);

	        return *this;
	    }

	    /**
	     * @brief u8 conversion operator overload
	     *
	     * @return Pin value
	     */
	    [[nodiscard]] operator u8() const noexcept {
			int fd = open(("/sys/class/gpio/gpio" + std::to_string(GPIOBaseNumber + Pin) + "/value").c_str(), O_RDONLY);
			if (fd == -1) return 0;

			char buffer[2] = { 0 };
			read(fd, buffer, sizeof(buffer));
			close(fd);

			bool result = buffer[0] == '1';

	        return LogicActive == bsp::drv::Active::High ? result : !result;
	    }

		/**
		 * @brief Init function
		 *
		 * @return Success
		 */
		bool init() const noexcept {
			int fd = open("/sys/class/gpio/export", O_WRONLY);
			if (fd == -1) return false;

			auto value = std::to_string(GPIOBaseNumber + Pin);
			write(fd, value.c_str(), value.length());
			close(fd);

			return true;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return Success
		 */
		bool deinit() const noexcept {
			int fd = open("/sys/class/gpio/unexport", O_WRONLY);
			if (fd == -1) return false;

			auto value = std::to_string(GPIOBaseNumber + Pin);
			write(fd, value.c_str(), value.length());
			close(fd);

			return true;
		}

		/**
		 * @brief Turn pin into an output
		 */
		void makeOutput() const noexcept {			
			int fd = open(("/sys/class/gpio/gpio" + std::to_string(GPIOBaseNumber + Pin) + "/direction").c_str(), O_WRONLY);
			if (fd == -1) return;

			write(fd, "out", 3);
			close(fd);
		}

		/**
		 * @brief Turn pin into an input
		 */
		void makeInput() const noexcept {			
			int fd = open(("/sys/class/gpio/gpio" + std::to_string(GPIOBaseNumber + Pin) + "/direction").c_str(), O_WRONLY);
			if (fd == -1) return;

			write(fd, "in", 2);
			close(fd);
		}

	private:
	    GPIOPin() = default;
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
	template<u8 GPIOBaseNumber>
	struct GPIOPort {
	private:
		GPIOPort() = default;

    public:
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

		GPIOPort(const GPIOPort&) = delete;
		GPIOPort(GPIOPort&&) = delete;

		/**
		 * @brief GPIO Pin definition
		 * 
		 * @tparam Pin Pin number
		 * @tparam LogicActive Active logic level
		 */
		template<u8 Pin, bsp::drv::Active LogicActive>
		static constexpr auto Pin = GPIOPin<GPIOBaseNumber, Pin, LogicActive>();
	};

}
