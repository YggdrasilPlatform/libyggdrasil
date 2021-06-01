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

C_LINKAGE bool yggdrasil_CAN_Init(can_t can);
C_LINKAGE bool yggdrasil_CAN_Enable(can_t can);
C_LINKAGE bool yggdrasil_CAN_Disable(can_t can);
C_LINKAGE void yggdrasil_CAN_Read(can_t can, u32 *id, void *data, size_t size);
C_LINKAGE u32 yggdrasil_CAN_Write(can_t can, u32 id, void *data, size_t size);

C_LINKAGE bool yggdrasil_CAN_SetStdFilter(can_t can, u8 bank, u16 id, u16 mask);
C_LINKAGE bool yggdrasil_CAN_DisableFilter(can_t can, u8 bank);


