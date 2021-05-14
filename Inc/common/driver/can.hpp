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
  *  @file common/driver/CAN.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the CAN abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>
#include <common/utils.hpp>

#include <array>
#include <tuple>

namespace bsp::drv {

	template<typename T>
		struct CANPacket {
			u32 id, extendedId;
			union {
				u32 timestamp, transmitGlobalTime;
			};
			T data;
		};

	/**
	 * @brief Base class for CAN abstraction
	 *
	 * @tparam Context CAN context
	 * @tparam CanImpl CAN implementation
	 */
	template<auto Context, template<auto> typename CanImpl>
	struct CAN {
		CAN() = delete;



		using Impl = CanImpl<Context>;

		static bool enable() {
			return Impl::enable();
		}

		static bool disable() {
			return Impl::disable();
		}


	    /**
	     * @brief CAN read function
	     *
	     * @tparam T type to read
	     * @param address Device address
	     * @return Read data
	     */
		template<typename T>
		static CANPacket<T> read() {
			static_assert(sizeof(T) <= 8, "CAN data can be 8 byte maximal");
			CANPacket<T> rxPacket;
			std::array<u8, 8> data;
			Impl::read(rxPacket.id, rxPacket.extendedId, rxPacket.timestamp, data);

			rxPacket.data = bit_cast<T>(data);

			return rxPacket;
		}

	    /**
	     * @brief CAN write function
	     *
	     * @param address Device address
	     * @param value Data to write
	     */
		template<typename T>
		static u32 write(CANPacket<T> packet) {
			static_assert(sizeof(T) <= 8, "CAN data can be 8 byte maximal");

			return Impl::write(packet);

		}

		template<typename T>
		static u32 write(u32 id,  const T &data) {
			static_assert(sizeof(T) <= 8, "CAN data can be 8 byte maximal");
			CANPacket<T>  packet = {0};
			if(id <= 0x7FF) packet.id = id;
			else packet.extendedId = id;
			packet.data = data;
			return Impl::write(packet);

		}

		static bool setStdFilter(u8 bank, u16 id, u16 mask = 0x7FF) {
			return Impl::setStdFilter(bank, id, mask);
		}

		static bool setExtFilter(u8 bank, u32 id, u32 mask = 0x1FFF'FFFF) {
			return Impl::setExtFilter(bank, id, mask);
		}

		static bool disableFilter(u8 bank) {
			return Impl::disableFilter(bank);
		}
	};
}
