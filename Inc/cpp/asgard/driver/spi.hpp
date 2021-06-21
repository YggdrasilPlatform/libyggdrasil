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
  *  @file cpp/asgard/driver/spi.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief SPI abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/spi.hpp>

#include <string>
#include <string_view>
#include <array>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>

namespace bsp::asg::drv {

	/**
	 * @brief SPI implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context SPI context
	 */
	template<auto Context>
	struct SPI {

		/**
		 * @brief Init function
		 *
		 * @return True when successfully started, false when not
		 */
		static bool init() {
			SPI::s_device = open(("/dev/spidev" + std::to_string(Context[0]) + "." + std::to_string(Context[1])).c_str(), O_RDWR);
			if (SPI::s_device == -1)
				return false;

			u8 mode = 0;
			u8 bitsPerWord = 8;
			u32 speed = 1'000'000;
			

			if (ioctl(SPI::s_device, SPI_IOC_WR_MODE, &mode) < 0)
				return false;

			if (ioctl(SPI::s_device, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord) < 0)
				return false;

			if (ioctl(SPI::s_device, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
				return false;

			SPI::s_transfer.bits_per_word = bitsPerWord;
			SPI::s_transfer.cs_change = 0;
			SPI::s_transfer.delay_usecs = 0;
			SPI::s_transfer.speed_hz = speed;

			return true;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return True when successfully stopped, false when not
		 */
		static bool deinit() {
			close(SPI::s_device);
			return true;
		}

		/**
		 * @brief SPI receive
		 *
		 * @tparam N Data size
	     * @param data Array for the read data
		 */
		template<size_t N>
		static void read(std::array<u8, N> &data) {
			std::array<u8, N> dummyData;

			SPI::s_transfer.tx_buf = reinterpret_cast<u64>(dummyData.data());
			SPI::s_transfer.rx_buf = reinterpret_cast<u64>(data.data());
			SPI::s_transfer.len = data.size();

			ioctl(SPI::s_device, SPI_IOC_MESSAGE(1), &SPI::s_transfer);
		}

		/**
		 * @brief SPI write
		 *
		 * @tparam N Data size
	     * @param data Array to send
		 */
		template<size_t N>
		static void write(const std::array<u8, N> &data) {
			std::array<u8, N> dummyData;
			SPI::s_transfer.tx_buf = reinterpret_cast<u64>(data.data());
			SPI::s_transfer.tx_buf = reinterpret_cast<u64>(dummyData.data());
			SPI::s_transfer.len = data.size();

			ioctl(SPI::s_device, SPI_IOC_MESSAGE(1), &SPI::s_transfer);
		}

		/**
		 * @brief Set the spi mode (CPOL and CPHA)
		 *
		 * @param mode SPI mode
		 * @note This function wait until the SPI is not busy anymore and then the mode change will take place
		 */
		static void setMode(bsp::drv::SPIMode mode) {
			u8 value = 0;
			if (ioctl(SPI::s_device, SPI_IOC_RD_MODE, &value) < 0)
				return;

			value &= ~SPI_MODE_3;

			switch (mode) {
				case bsp::drv::SPIMode::_0: 
					value |= SPI_MODE_0;
					break;
				case bsp::drv::SPIMode::_1:
					value |= SPI_MODE_1;
					break;
				case bsp::drv::SPIMode::_2:
					value |= SPI_MODE_2;
					break;
				case bsp::drv::SPIMode::_3:
					value |= SPI_MODE_3;
					break;
			}

			ioctl(SPI::s_device, SPI_IOC_WR_MODE, &value);
		}

		private:
			static inline int s_device = -1;
			static inline spi_ioc_transfer s_transfer;
	};

}
