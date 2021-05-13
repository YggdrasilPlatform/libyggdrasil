 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
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
  *  @file midgard/driver/can.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief CAN abstraction implementation for Midgard
  */

#pragma once

#include <common/driver/can.hpp>

#include <string>
#include <string_view>
#include <array>

namespace bsp::mid::drv {

	/**
	 * @brief CAN implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context CAN context
	 */
	template<auto Context>
	struct CAN {
		/**
		 * @brief CAN receive
		 *
		 * @tparam N Data size
		 * @param address Device address
	     * @param data Array for the read data
		 */

		static void read(u32 &id, u32 &extendedId, u32 &timestamp, std::array<u8, 8> &data) {
			CAN_RxHeaderTypeDef rxHeader;
			while (HAL_CAN_GetRxFifoFillLevel(Context, CAN_RX_FIFO0) == 0);
			HAL_CAN_GetRxMessage(Context, CAN_RX_FIFO0, &rxHeader, data.data());
			id = rxHeader.StdId;
			extendedId = rxHeader.ExtId;
			timestamp = rxHeader.Timestamp;
		}

		/**
		 * @brief CAN write
		 *
		 * @tparam N Data size
		 * @param address Device address
	     * @param data Array to send
		 */
		template<typename T>
		static u32 write(bsp::drv::CANPacket<T> packet) {
			u32 pTxMailbox;
			CAN_TxHeaderTypeDef txHeader = {0};
			constexpr size_t Size = sizeof(T);

			std::array<u8, Size> data;
			std::memcpy(data.data(), &packet.data, Size);
			txHeader.StdId = packet.id;
			txHeader.ExtId = packet.extendedId;
			txHeader.TransmitGlobalTime = static_cast<FunctionalState>(packet.transmitGlobalTime);
			txHeader.DLC = Size;

			if(packet.extendedId > 0) txHeader.IDE = CAN_ID_EXT;
			else txHeader.IDE = CAN_ID_STD;


			HAL_CAN_AddTxMessage(Context, &txHeader, const_cast<u8*>(data.data()), &pTxMailbox);
			while (HAL_CAN_GetTxMailboxesFreeLevel(Context) != 3);
			return pTxMailbox;
		}
	};

}
