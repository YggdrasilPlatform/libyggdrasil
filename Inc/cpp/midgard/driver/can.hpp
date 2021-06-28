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
  *  @file cpp/midgard/driver/can.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief CAN abstraction implementation for Midgard
  */

#pragma once

#include <cpp/common/frontend/can.hpp>

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
		 * @brief Init function
		 * @note Filter bank 0 will be set to 0 0 to accept all IDs
		 *
		 * @return Success
		 */
		static bool init() {
			setStdFilter(0, 0, 0);	// bank 0 will accept all IDs
			return HAL_CAN_Start(Context) == HAL_OK;
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
			CAN_RxHeaderTypeDef rxHeader = {0};
			while (HAL_CAN_GetRxFifoFillLevel(Context, CAN_RX_FIFO0) == 0);
			HAL_CAN_GetRxMessage(Context, CAN_RX_FIFO0, &rxHeader, data.data());
			id = rxHeader.StdId;
			extendedId = rxHeader.ExtId;
			timestamp = rxHeader.Timestamp;
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

		/**
		 * @brief Standard ID filter configuration function
		 *
		 * @param bank Filterbank 0 to 28
		 * @param id Standard ID 0 to 0x7FF
		 * @param mask Filtermask 0 to 0x7FF
		 * @return Success
		 */
		static bool setStdFilter(u8 bank, u16 id, u16 mask) {
			if (bank > 28) return false;
			if (id > 0x7FF) return false;
			if (mask > 0x7FF) return false;

			CAN_FilterTypeDef sFilterConfig;
			sFilterConfig.FilterBank = bank;
			sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
			sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
			sFilterConfig.FilterIdHigh = (id << 5);
			sFilterConfig.FilterIdLow = 0;
			sFilterConfig.FilterMaskIdHigh = (mask << 5);
			sFilterConfig.FilterMaskIdLow = 0;
			sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
			sFilterConfig.FilterActivation = ENABLE;
			sFilterConfig.SlaveStartFilterBank = 0;

			if (HAL_CAN_ConfigFilter(Context, &sFilterConfig) != HAL_OK) return false;
			return true;
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
		static bool setExtFilter(u8 bank, u32 id, u32 mask) {
			if (bank > 28) return false;
			if (id > 0x1FFFFFFF) return false;
			if (mask > 0x1FFFFFFF) return false;

			CAN_FilterTypeDef sFilterConfig;
			sFilterConfig.FilterBank = bank;
			sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
			sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
			sFilterConfig.FilterIdHigh = ((id & 0x7FF) << 5) | ((id >> 27) & 0xFFFF);
			sFilterConfig.FilterIdLow = ((id >> 11) << 3) & 0xFFFF;
			sFilterConfig.FilterMaskIdHigh = ((mask & 0x7FF) << 5) | ((mask >> 27) & 0xFFFF);
			sFilterConfig.FilterMaskIdLow = ((mask >> 11) << 3) & 0xFFFF;
			sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
			sFilterConfig.FilterActivation = ENABLE;
			sFilterConfig.SlaveStartFilterBank = 0;

			if (HAL_CAN_ConfigFilter(Context, &sFilterConfig) != HAL_OK)
				return false;

			return true;
		}

		/**
		 * @brief Filter bank disable
		 *
		 * @param bank Filterbank number
		 * @return Success
		 */
		static bool disableFilter(u8 bank) {
			if (bank > 28) return false;

			CAN_FilterTypeDef sFilterConfig;
			sFilterConfig.FilterBank = bank;
			sFilterConfig.FilterActivation = DISABLE;

			if (HAL_CAN_ConfigFilter(Context, &sFilterConfig) != HAL_OK) return false;
			return true;
		}


	};

}
