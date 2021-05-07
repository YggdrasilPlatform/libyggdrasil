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
  *  @file common/driver/dac.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the DAC abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>

namespace bsp::drv {

	/**
	 * @brief Base class for DAC abstraction
	 *
	 * @tparam Context DAC context
	 * @tparam DACChannelImpl DACChannel implementation
	 */
	template<auto Context, template<auto, u8, u32, u32> typename DACChannelImpl>
	struct DAConverter {
		DAConverter() = delete;
		DAConverter(const DAConverter&) = delete;
		DAConverter(DAConverter &&) = delete;

		/**
		 * @brief Channel implementation
		 *
		 * @tparam Index ChannelID
		 * @tparam Offset Calibration offset
		 * @tparam MaxValue Maximum value used
		 */
		template<u8 Index, u32 Offset = 0, u32 MaxValue = (1 << 12) - 1>
		static inline auto Channel = DACChannelImpl<Context, Index, Offset, MaxValue>();
	};

}
