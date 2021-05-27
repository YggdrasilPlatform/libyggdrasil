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
  *  @file c/midgard/core/cortex.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Core control functions
  */

#pragma once

#include <c/common/types.h>
#include <c/common/attributes.h>

#include <core_cm7.h>

/**
 * @brief Disables all interrupts
 */
ALWAYS_INLINE void core_DisableInterrupts() {
	asm volatile ("cpsid i" : : : "memory");
}

/**
 * @brief Enables all interrupts
 */
ALWAYS_INLINE void core_EnableInterrupts() {
	asm volatile ("cpsie i" : : : "memory");
}

/**
 * @brief Sets the base address of the interrupt vector table
 * @param address Base address
 */
ALWAYS_INLINE void core_SetInterruptVectorBase(addr_t address) {
	SCB->VTOR = address;
}

/**
 * @brief Delays execution by a certain number of milliseconds
 * @param ms Number of milliseconds to wait
 */
ALWAYS_INLINE void core_Delay(u32 ms) {
	u32 startTime = HAL_GetTick();

	while (HAL_GetTick() < startTime + ms);
}
