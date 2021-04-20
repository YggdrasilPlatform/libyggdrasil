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
  *  @brief UART abstraction implementation for Midgard  		    *
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

#include <common/driver/uart.hpp>

#include <string>
#include <string_view>
#include <array>

#include <cmsis_gcc.h>

namespace bsp::mid::drv {

	template<addr_t BaseAddress>
	struct UART {

		ALWAYS_INLINE static void transmit(std::string_view buffer) {
			for (char c : buffer) {
				while(!TXE);

				TRNS = c;
			}
		}

		ALWAYS_INLINE static void receive(std::string &buffer) {
			while (true) {
				while (!RXNE);

				char c = RECV;

				if (c == '\n' || c == '\r')
					break;
				else
					buffer.push_back(c);
			}
		}

		template<size_t N>
		ALWAYS_INLINE static void receive(std::array<u8, N> &buffer) {
			u32 index = 0;
			while (index < N) {
				while (!RXNE);

				u8 c = RECV;

				buffer[index] = c;

				index++;
			}
		}

	private:
		enum class RegisterMap {
			CR1	= 0x00,
			CR2 = 0x04,
			CR3 = 0x08,
			ISR = 0x1C,
			ICR = 0x20,
			RDR = 0x24,
			TDR = 0x28,
		};

		using CR1 = Register<BaseAddress, RegisterMap::CR1, u32>;
		using CR2 = Register<BaseAddress, RegisterMap::CR2, u32>;
		using CR3 = Register<BaseAddress, RegisterMap::CR3, u32>;
		using ISR = Register<BaseAddress, RegisterMap::ISR, u32>;
		using ICR = Register<BaseAddress, RegisterMap::ICR, u32>;
		using RDR = Register<BaseAddress, RegisterMap::RDR, u32>;
		using TDR = Register<BaseAddress, RegisterMap::TDR, u32>;

		static inline auto RXNE	= typename ISR::template Field<5, 5>();
		static inline auto TXE 	= typename ISR::template Field<7, 7>();

		static inline auto RECV = typename RDR::template Field<0, 8>();
		static inline auto TRNS = typename TDR::template Field<0, 8>();
	};

}
