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
  *  @file cpp/common/frontend/can.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the CAN abstraction
  */

#pragma once

#include <cpp/common/registers.hpp>
#include <cpp/common/attributes.hpp>
#include <cpp/common/utils.hpp>

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

		/**
		 * @brief Init function
		 * @note Filter bank 0 will be set to 0 0 to accept all IDs
		 *
		 * @return Success
		 */
		static auto init(auto ... args) {
			return Impl::init(args...);
		}

		/**
		 * @brief Deinit function
		 *
		 */
		static auto deinit(auto ... args) {
			return Impl::deinit(args...);
		}

		/**
		 * @brief Can enable
		 */
		static bool enable() {
			return Impl::enable();
		}

		/**
		 * @brief Can disable
		 */
		static bool disable() {
			return Impl::disable();
		}


	    /**
	     * @brief CAN read function
	     *
	     * @tparam T type to read
	     * @return Read data in a CANpacket
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
	     * @tparam T type to write
	     * @param packet CAN packet to write
	     */
		template<typename T>
		static u32 write(CANPacket<T> packet) {
			static_assert(sizeof(T) <= 8, "CAN data can be 8 byte maximal");

			return Impl::write(packet);

		}

	    /**
	     * @brief CAN write function
	     *
	     * @tparam T type to write
	     * @param id CAN id
	     * @param data Data to write
	     */
		template<typename T>
		static u32 write(u32 id,  const T &data) {
			static_assert(sizeof(T) <= 8, "CAN data can be 8 byte maximal");
			CANPacket<T>  packet = {0};
			if(id <= 0x7FF) packet.id = id;
			else packet.extendedId = id;
			packet.data = data;
			return Impl::write(packet);

		}

		/**
		 * @brief Standard ID filter configuration function
		 *
		 * @param bank Filterbank 0 to 28
		 * @param id Standard ID 0 to 0x7FF
		 * @param mask Filtermask 0 to 0x7FF
		 * @return Success
		 */
		static bool setStdFilter(u8 bank, u16 id, u16 mask = 0x7FF) {
			return Impl::setStdFilter(bank, id, mask);
		}

		/**
		 * @brief Extended ID filter configuration function
		 *
		 * @param bank Filterbank 0 to 28
		 * @param id Standard ID 0 to 0x1FFFFFFF
		 * @param mask Filtermask 0 to 0x1FFFFFFF
		 * @return Success
		 *
		 * @warning This function might have complications with PCAN
		 */
		static bool setExtFilter(u8 bank, u32 id, u32 mask = 0x1FFF'FFFF) {
			return Impl::setExtFilter(bank, id, mask);
		}

		/**
		 * @brief Filter bank disable
		 *
		 * @param bank Filterbank number
		 * @return Success
		 */
		static bool disableFilter(u8 bank) {
			return Impl::disableFilter(bank);
		}
	};
}
