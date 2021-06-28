 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file cpp/asgard_coproc/driver/can.hpp
  *  @ingroup asgard_coproc
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief CAN abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/can.hpp>

#include <string>
#include <string_view>
#include <array>

namespace bsp::asg_coproc::drv {

	/**
	 * @brief CAN implementation for Asgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context CAN context
	 */
	template<auto Context>
	struct CAN {

		/**
		 * @brief Init function
		 *
		 * @return Success
		 */
		static bool init() {
			return HAL_FDCAN_Start(Context) == HAL_OK;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return Success
		 */
		static bool deinit() {
			return true;
		}

		/**
		 * @brief Can enable
		 */
		static bool enable() {
			return HAL_CAN_Start(Context) == HAL_OK;
		}

		/**
		 * @brief Can disable
		 */
		static bool disable() {
			return HAL_CAN_Stop(Context) == HAL_OK;
		}


		/**
		 * @brief CAN receive
		 *
		 * @param[out] id CAN ID
		 * @param[out] extendedId CAN extended ID
	     * @param[out] timestamp Timestamp
	     * @param[out] data Received data
		 */
		static void read(u32 &id, u32 &extendedId, u32 &timestamp, std::array<u8, 8> &data) {
			FDCAN_RxHeaderTypeDef rxHeader = {0};
			while (HAL_CAN_GetRxFifoFillLevel(Context, FDCAN_RX_FIFO0) == 0);
			HAL_CAN_GetRxMessage(Context, FDCAN_RX_FIFO0, &rxHeader, data.data());
			if (rxHeader.IdType == FDCAN_STANDARD_ID) {
				id = rxHeader.Identifier;
			}
			else {
				extendedId = rxHeader.Identifier;
			}
			timestamp = rxHeader.RxTimestamp;
		}

		/**
		 * @brief CAN write
		 *
		 * @tparam T type to write
		 * @param packet CAN packet to write
		 */
		template<typename T>
		static u32 write(bsp::drv::CANPacket<T> packet) {
			u32 pTxMailbox;
			FDCAN_TxHeaderTypeDef txHeader = {0};
			constexpr size_t Size = sizeof(T);

			std::array<u8, Size> data;
			std::memcpy(data.data(), &packet.data, Size);
			if (packet.extendedId > 0) {
				txHeader.Identifier = packet.extendedId;
				txHeader.IdType = FDCAN_EXTENDED_ID;
			}
			else {
				txHeader.Identifier = packet.id;
				txHeader.IdType = FDCAN_STANDARD_ID;
			}

			txHeader.DataLength = Size;

			HAL_CAN_AddTxMessage(Context, &txHeader, const_cast<u8*>(data.data()), &pTxMailbox);
			while (HAL_CAN_GetTxMailboxesFreeLevel(Context) != 3);
			return pTxMailbox;
		}

	};

}
