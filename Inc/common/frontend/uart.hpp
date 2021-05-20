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
  *  @file common/frontend/uart.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the UART abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>
#include <common/utils.hpp>

#include <array>

namespace bsp::drv {

	/**
	 * @brief Base class for UART abstraction
	 *
	 * @tparam Context UART context
	 * @tparam UARTImpl UART implementation
	 */
	template<auto Context, template<auto> typename UARTImpl>
	struct UART {
		UART() = delete;

		using Impl = UARTImpl<Context>;

	    /**
	     * @brief UART read string function
	     *
	     * @return Read string
	     */
		static std::string readString() {
			std::string data;
			Impl::receive(data);

			return data;
		}

	    /**
	     * @brief UART read function
	     *
	     * @tparam N Size to read
	     * @return Read data
	     */
		template<size_t N>
		static std::array<u8, N> read() {
			std::array<u8, N> data;
			Impl::receive(data);

			return data;
		}

	    /**
	     * @brief UART write string function
	     *
	     * @param data String to write
	     */
		static void write(std::string_view data) {
			Impl::transmit(data);
		}

	    /**
	     * @brief UART write string function
	     *
	     * @tparam N Size to write
	     * @param data Data to write
	     */
		template<size_t N>
		static void write(const std::array<u8, N> &data) {
			Impl::transmit(data);
		}
	};
}
