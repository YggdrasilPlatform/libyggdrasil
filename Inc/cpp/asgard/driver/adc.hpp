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
  *  @file cpp/midgard/driver/adc.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief ADC Channel abstraction implementation for Midgard
  */

#pragma once

#include <cpp/common/frontend/adc.hpp>

#include <cmath>

namespace bsp::mid::drv {

	/**
	 * @brief ADC Channel implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context ADC Context
	 * @tparam Index Channel ID
	 * @tparam Offset Calibration offset
	 * @tparam MaxValue Maximum value reported
	 */
	template<auto Context, u8 Index, u32 Offset, u32 MaxValue>
	struct ADCChannel {
		ADCChannel(const ADCChannel&) = delete;
		auto operator=(const ADCChannel&) = delete;

		constexpr static auto ReferenceVoltage = 3.3;

		/**
		 * @brief Init function
		 *
		 * @return True when successfully started, false when not
		 */
		static bool init() {
			ADCChannel::s_device = open(("/sys/bus/iio/devices/iio:device" + std::to_string(Context) + "/in_voltage" + std::to_string(Index) + "_raw").c_str(), O_RDWR);
			return ADCChannel::s_device != -1;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return True when successfully stopped, false when not
		 */
		static bool deinit() {
			close(ADCChannel::s_device);
			return true;
		}

		/**
		 * @brief Get the current ADC value
		 * @note This function polls the result
		 *
		 * @return Current value between 0.0 and 1.0
		 */
		operator float() const noexcept {
			std::string data(0xFF, 0x00);

			if (read(ADCChannel::s_device, data.data(), data.size()) <= 0)
				return 0.0F;
			lseek(ADCChannel::s_device, 0, 0);

			return std::max<float>(std::stol(data) - Offset, 0.0F) / MaxValue;	// Get the value and transform it to 0.0 to 1.0
		}

	private:
		ADCChannel() = default;

		/**
		 * @brief Declare ADConverter frontend as friend
		 */
		template<auto, template<auto, u8, u32, u32> typename>
		friend struct bsp::drv::ADConverter;

		static inline int s_device = -1;
	};

}
