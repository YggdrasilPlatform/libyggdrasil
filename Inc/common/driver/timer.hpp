/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file common/driver/timer.hpp                                  *
  *  @ingroup common                                                *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Base class for the Timer abstraction 					*
  *  									                       		*
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

#include <common/registers.hpp>
#include <common/attributes.hpp>

namespace bsp::drv {

	/**
	 * @brief Base class for GPIO port abstraction
	 * @tparam BaseAddress GPIO port bank base address
	 * @tparam GPIOPin GPIOPin implementation
	 */
	// TODO comments
	template<auto Context, template<auto, typename> typename TimerImpl, typename Size>
	struct Timer {
		Timer() = delete;
		Timer(const Timer&) = delete;
		Timer(Timer &&) = delete;

	    /**
	     * @brief GPIO Pin
	     * @tparam Number Pin number
	     */
	    template<u8 Number>
	    static inline auto& Channel = TimerImpl<Context, Size>::template Channel<Number>;
	    template<u8 Number>
	    static inline auto& Encoder = TimerImpl<Context, Size>::template Encoder<Number>;


	    using Impl = TimerImpl<Context, Size>;

	    static inline Size getCount() {
	    	return Impl::getCount();
	    }

	    static inline void setCount(Size cnt) {
	    	Impl::setCount(cnt);
	    }

	    static inline void resetCount() {
	    	Impl::setCount(0);
	    }

	    static inline u32 getPwmFrequency() {
	    	return Impl::getPwmFrequency();
	    }

	    static inline bool setPwmFrequency(u32 f_hz, Size resolution = 0) {
	    	return Impl::setPwmFrequency(f_hz, resolution);
	    }



	};

}
