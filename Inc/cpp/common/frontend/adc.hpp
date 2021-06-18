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
  *  @file cpp/common/frontend/adc.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the ADC abstraction
  */

#pragma once

#include <cpp/common/registers.hpp>
#include <cpp/common/attributes.hpp>

namespace bsp::drv {

	/**
	 * @brief Base class for ADC abstraction
	 * @tparam Context ADC context
	 * @tparam ADCChannel ADCChannel implementation
	 */
	template<auto Context, template<auto, u8, u32, u32> typename ADCChannelImpl>
	struct ADConverter {
		ADConverter() = delete;
		ADConverter(const ADConverter&) = delete;
		ADConverter(ADConverter &&) = delete;

		/**
		 * @brief Init function
		 *
		 * @return True when successfully started, false when not
		 */
		static auto init(auto ... args) {
			return Impl::init(args...);
		}

		/**
		 * @brief Deinit function
		 *
		 * @return True when successfully stopped, false when not
		 */
		static auto deinit(auto ... args) {
			return Impl::deinit(args...);
		}

		/**
		 * @brief Channel implementation
		 * @tparam Index ChannelID
		 * @tparam Offset Calibration offset
		 * @tparam MaxValue Maximum value reported
		 */
		template<u8 Index, u32 Offset = 0, u32 MaxValue = (1 << 12) - 1>
		static inline auto Channel = ADCChannelImpl<Context, Index, Offset, MaxValue>();
	};

}
