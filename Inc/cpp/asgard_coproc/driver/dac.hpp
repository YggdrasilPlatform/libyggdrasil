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
  *  @file cpp/asgard_coproc/driver/dac.hpp
  *  @ingroup asgard_coproc
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief DAC Channel abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/dac.hpp>

#include <cmath>

namespace bsp::asg_coproc::drv {

	/**
	 * @brief DAC Channel implementation for Asgard
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
		 * @brief Set the current DAC value
		 *
		 * @param value Current value between 0.0 and 1.0
		 */
		auto operator=(float value) const noexcept {
			constexpr auto Channel = getHALChannel();
			HAL_DAC_SetValue(Context, Channel, DAC_ALIGN_12B_R, u32(std::max(value * MaxValue - Offset, 0.0F)));
			HAL_DAC_Start(Context, Channel);
		}

		/**
		 * @brief Get the current DAC value
		 * 
		 * @return Fraction of reference voltage between 0.0 and 1.0
		 */ 
		operator float() const noexcept {
			constexpr auto Channel = getHALChannel();

			return float(std::max(HAL_DAC_GetValue(Context, Channel) + Offset, 0)) / MaxValue;
		}

	private:
		DACChannel() = default;

		/**
		 * @brief get HAL channel definition depending on the set index
		 *
		 * @return HAL channel definition
		 */
		constexpr static u32 getHALChannel() {
			switch (Index) {
				case 1:  return DAC_CHANNEL_1;
				case 2:  return DAC_CHANNEL_2;
				default: bsp::unreachable();
			}
		}

		/**
		 * @brief Declare DAConverter frontend as friend
		 */
		template<auto, template<auto, u8, u32, u32> typename>
		friend struct bsp::drv::DAConverter;
	};

}
