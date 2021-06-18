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
  *  @file c/midgard/driver/can.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief CAN abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

typedef struct {
	CAN_HandleTypeDef *interface;

} can_t;

/**
 * @brief CAN init function
 * @note Filter bank 0 will be set to 0 0 to accept all IDs
 *
 * @param can CAN handle
 * @return True when successfully stared, false when not
 */
C_LINKAGE bool yggdrasil_CAN_Init(can_t can);

/**
 * @brief CAN init function
 *
 * @param can CAN handle
 * @return True when successfully stopped, false when not
 */
C_LINKAGE bool yggdrasil_CAN_Deinit(can_t can);

/**
 * @brief CAN enable
 *
 * @param can CAN handle
 */
C_LINKAGE bool yggdrasil_CAN_Enable(can_t can);

/**
 * @brief CAN disable
 *
 * @param can CAN handle
 */
C_LINKAGE bool yggdrasil_CAN_Disable(can_t can);

/**
 * @brief CAN receive
 *
 * @param can CAN handle
 * @param[out] id CAN ID
 * @param[out] extendedId CAN extended ID
 * @param[out] timestamp Timestamp
 * @param[out] data Received data
 */
C_LINKAGE void yggdrasil_CAN_Read(can_t can, u32 *id, void *data, size_t size);

/**
 * @brief CAN write
 *
 * @param can CAN handle
 * @param id CAN id standard or extended
 * @param data Pointer to the data
 * @param size Size of the data
 */
C_LINKAGE u32 yggdrasil_CAN_Write(can_t can, u32 id, void *data, size_t size);

/**
 * @brief Standard ID filter configuration function
 *
 * @param can CAN handle
 * @param bank Filterbank 0 to 28
 * @param id Standard ID 0 to 0x7FF
 * @param mask Filtermask 0 to 0x7FF
 * @return True when successfully set, false when not
 */
C_LINKAGE bool yggdrasil_CAN_SetStdFilter(can_t can, u8 bank, u16 id, u16 mask);

/**
 * @brief Filter bank disable
 *
 * @param can CAN handle
 * @param bank Filterbank number
 * @return True when successfully disabled, false when not
 */
C_LINKAGE bool yggdrasil_CAN_DisableFilter(can_t can, u8 bank);


