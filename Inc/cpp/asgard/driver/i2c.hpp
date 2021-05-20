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
  *  @file asgard/driver/i2c.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief I2C abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/i2c.hpp>

#include <string>
#include <array>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>

namespace bsp::asg::drv {

	/**
	 * @brief I2C implementation for Asgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam InterfaceNumber I2C interface number
	 */
	template<u16 InterfaceNumber>
	struct I2C {

		static void init() {
			I2C::s_fileHandle = open(("/dev/i2c-" + std::to_string(InterfaceNumber)).c_str(), O_RDWR);
		}

		/**
		 * @brief I2C receive
		 *
		 * @tparam N Data size
		 * @param address Device address
	     * @param data Array for the read data
		 */
		template<size_t N>
		static void read(u8 address, std::array<u8, N> &data) {
			::ioctl(I2C::s_fileHandle, I2C_SLAVE, address >> 1);
			::read(I2C::s_fileHandle, data.data(), N);
		}

		/**
		 * @brief I2C write
		 *
		 * @tparam N Data size
		 * @param address Device address
	     * @param data Array to send
		 */
		template<size_t N>
		static void write(u8 address, const std::array<u8, N> &data) {
			::ioctl(I2C::s_fileHandle, I2C_SLAVE, address >> 1);
			::write(I2C::s_fileHandle, data.data(), N);
		}

	private:
		static inline int s_fileHandle = -1;
	};

}
