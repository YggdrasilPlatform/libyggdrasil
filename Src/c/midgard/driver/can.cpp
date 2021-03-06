 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Midgard -                             *
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
  *  @file c/midgard/driver/can.cpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief CAN abstraction implementation for Midgard
  */

#include <yggdrasil.h>

#if BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/can.h>

	#include <math.h>

	C_LINKAGE bool yggdrasil_CAN_Init(can_t can) {
		yggdrasil_CAN_SetStdFilter(can, 0, 0, 0);	// bank 0 will accept all IDs
		return HAL_CAN_Start(can.interface) == HAL_OK;
	}

	bool yggdrasil_CAN_Deinit(can_t can) {
		return true;
	}

	C_LINKAGE bool yggdrasil_CAN_Enable(can_t can) {
		return HAL_CAN_Start(can.interface) == HAL_OK;
	}

	C_LINKAGE bool yggdrasil_CAN_Disable(can_t can) {
		return HAL_CAN_Stop(can.interface) == HAL_OK;
	}

	C_LINKAGE void yggdrasil_CAN_Read(can_t can, u32 *id, void *data, size_t size) {
		CAN_RxHeaderTypeDef rxHeader = {0};
		while (HAL_CAN_GetRxFifoFillLevel(can.interface, CAN_RX_FIFO0) == 0);
		HAL_CAN_GetRxMessage(can.interface, CAN_RX_FIFO0, &rxHeader, (u8 *)data);
		if (rxHeader.ExtId > 0) {
			*id = rxHeader.ExtId;
		}
		else {
			*id = rxHeader.StdId;
		}
	}

	C_LINKAGE u32 yggdrasil_CAN_Write(can_t can, u32 id, void *data, size_t size) {
		u32 pTxMailbox;
		CAN_TxHeaderTypeDef txHeader = {0};

		txHeader.DLC = size;

		if(id > 0x7FF){
			txHeader.IDE = CAN_ID_EXT;
			txHeader.StdId = 0;
			txHeader.ExtId = id;
		}
		else {
			txHeader.IDE = CAN_ID_STD;
			txHeader.StdId = id;
			txHeader.ExtId = 0;
		}

		HAL_CAN_AddTxMessage(can.interface, &txHeader, (u8 *)data, &pTxMailbox);
		while (HAL_CAN_GetTxMailboxesFreeLevel(can.interface) != 3);
		return pTxMailbox;
	}

	C_LINKAGE bool yggdrasil_CAN_SetStdFilter(can_t can, u8 bank, u16 id, u16 mask) {
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

		if (HAL_CAN_ConfigFilter(can.interface, &sFilterConfig) != HAL_OK) return false;
		return true;
	}

	C_LINKAGE bool yggdrasil_CAN_DisableFilter(can_t can, u8 bank) {
		if (bank > 28) return false;

		CAN_FilterTypeDef sFilterConfig;
		sFilterConfig.FilterBank = bank;
		sFilterConfig.FilterActivation = DISABLE;

		if (HAL_CAN_ConfigFilter(can.interface, &sFilterConfig) != HAL_OK) return false;
		return true;
	}

#endif
