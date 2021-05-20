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
  *  @file common/driver/timer.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the Timer abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>

namespace bsp::drv {

	/**
	 * @brief Base class for Timer abstraction
	 *
	 * @tparam Context Timer context
	 * @tparam TimerImpl Timer implementation
	 * @tparam Size	Timer counter register size (16 bit or 32 bit)
	 */
	template<auto Context, template<auto, typename> typename TimerImpl, typename Size>
	struct Timer {
		Timer() = delete;
		Timer(const Timer&) = delete;
		Timer(Timer &&) = delete;

	    /**
	     * @brief Timer channel
	     *
	     * @tparam Number Channel number
	     */
	    template<u8 Number>
	    static inline auto& Channel = TimerImpl<Context, Size>::template Channel<Number>;

	    /**
	     * @brief Timer in encoder mode
	     */
	    static inline auto& Encoder = TimerImpl<Context, Size>::Encoder;

	    /**
		 * @brief Timer used as profile counter
		 */
		static inline auto& ProfileCounter = TimerImpl<Context, Size>::ProfileCounter;


	    using Impl = TimerImpl<Context, Size>;

	    /**
	     * @brief Get the counter value
	     *
	     * @return Actual timer count
	     */
	    static inline Size getCount() {
	    	return Impl::getCount();
	    }

	    /**
	     * @brief Set the counter value
	     *
	     * @param Size new timer value
	     */
	    static inline void setCount(Size cnt) {
	    	Impl::setCount(cnt);
	    }

	    /**
	     * @brief Set the counter value to 0
	     */
	    static inline void resetCount() {
	    	Impl::setCount(0);
	    }

	    /**
	     * @brief Get the pwm frequency
	     * @note The frequency is for all channels the same
	     *
	     * @return Frequency in Hz
	     */
	    static inline u32 getPwmFrequency() {
	    	return Impl::getPwmFrequency();
	    }

		/**
		 * @brief Set the pwm frequency and (optional) the maximal ticks within on cycle for all channels
		 * @note The actual duty cycle for all channels will be restored after the changes
		 *
		 * @param f_hz new frequency in hz
		 * @param resolution of the pwm, for 0 the actual value will be used
		 * @return true when the adjustment was possible, false when the parameter did not match
		 */
	    static inline bool setPwmFrequency(u32 f_hz, Size resolution = 0) {
	    	return Impl::setPwmFrequency(f_hz, resolution);
	    }

	};

}
