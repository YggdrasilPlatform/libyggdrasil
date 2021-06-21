 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
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
  *  @file cpp/midgard/driver/dac.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief DAC Channel abstraction implementation for Midgard
  */

#pragma once

#include <cpp/common/frontend/dac.hpp>

#include <cmath>

namespace bsp::mid::drv {

	/**
	 * @brief DAC Channel implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context DAC Context
	 * @tparam Index ChannelID
	 * @tparam Offset Calibration offset
	 * @tparam MaxValue Maximum value used
	 */
	template<auto Context, u8 Index, u32 Offset, u32 MaxValue>
	struct DACChannel {
		DACChannel(const DACChannel&) = delete;
		auto operator=(const DACChannel&) = delete;

		constexpr static auto ReferenceVoltage = 3.3;

		/**
		 * @brief Init function
		 *
		 * @return True when successfully started, false when not
		 */
		static bool init() {
			DACChannel::s_device = open(("/sys/bus/iio/devices/iio:device" + std::to_string(Context) + "/out_voltage" + std::to_string(Index) + "_raw").c_str(), O_RDWR);
			return DACChannel::s_device != -1;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return True when successfully stopped, false when not
		 */
		static bool deinit() {
			close(DACChannel::s_device);
			return true;
		}

		/**
		 * @brief Set the current DAC value
		 *
		 * @param value Current value between 0.0 and 1.0
		 */
		auto operator=(float value) const noexcept {
			u32 rawValue = std::max<float>(value * MaxValue - Offset, 0.0F);

			std::string data = std::to_string(rawValue);
			lseek(DACChannel::s_device, 0, 0);
			if (write(DACChannel::s_device, data.data(), data.size()) <= 0)
				return;
			lseek(DACChannel::s_device, 0, 0);
		}

		/**
		 * @brief Get the current DAC value
		 * 
		 * @return Fraction of reference voltage between 0.0 and 1.0
		 */ 
		operator float() const noexcept {
			std::string data(0xFF, 0x00);

			if (read(DACChannel::s_device, data.data(), data.size()) < 0)
				return 0.0F;
			lseek(DACChannel::s_device, 0, 0);

			return float(std::max<float>(std::stof(data) + Offset, 0)) / MaxValue;
		}

	private:
		DACChannel() = default;

		/**
		 * @brief Declare DAConverter frontend as friend
		 */
		template<auto, template<auto, u8, u32, u32> typename>
		friend struct bsp::drv::DAConverter;

		static inline int s_device = -1;
	};

}
