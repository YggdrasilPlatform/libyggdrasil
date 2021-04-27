/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file midgard/driver/uart.hpp                                  *
  *  @ingroup midgard                                               *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Timer abstraction implementation for Midgard  		    *
  *  			                                                    *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#pragma once

#include <common/driver/timer.hpp>

#include <string>
#include <string_view>
#include <array>

#include <cmsis_gcc.h>

namespace bsp::mid::drv {

	template<auto Context, u8 Channel, typename Size>
	struct TimerChannel {
		static_assert(Channel >= 1 && Channel <= 6, "Channel index out of range");
		ALWAYS_INLINE void startPwm() const noexcept{
			HAL_TIM_PWM_Start(Context, getHALChannel());
		}
		ALWAYS_INLINE void stopPwm() const noexcept{
			HAL_TIM_PWM_Stop(Context, getHALChannel());

		}
		ALWAYS_INLINE Size getValue() const noexcept{
			return Context.Instance->CNT;
		};

	private:
		static constexpr auto getHALChannel(){
			switch(Channel){
			case 1: return TIM_CHANNEL_1;
			case 2: return TIM_CHANNEL_2;
			case 3: return TIM_CHANNEL_3;
			case 4: return TIM_CHANNEL_4;
			case 5: return TIM_CHANNEL_5;
			case 6: return TIM_CHANNEL_6;
			default: bsp::unreachable();
			}
		}


	};

	template<auto Context, typename Size>
	struct Timer {
		template<u8 Number>
		static constexpr auto Channel = TimerChannel<Context, Number, Size>();

	private:

	};

}
