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
  *  @file cpp/asgard_coproc/core/instructions.hpp
  *  @ingroup asgard_coproc
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Assembly instruction wrapper functions
  */

#pragma once

#include <cpp/common/types.hpp>
#include <cpp/common/attributes.hpp>

namespace bsp::core {

	/**
	 * @brief Data barrier
	 */
	ALWAYS_INLINE static void DSB() {
		asm volatile("DSB");
	}

	/**
	 * @brief Instruction barrier
	 */
	ALWAYS_INLINE static void ISB() {
		asm volatile("ISB");
	}

	/**
	 * @brief Wait for Event
	 */
	ALWAYS_INLINE static void WFE() {
		asm volatile("WFE");
	}

	/**
	 * @brief Wait for Interrupt
	 */
	ALWAYS_INLINE static void WFI() {
		asm volatile("WFI");
	}

	/**
	 * @brief No operation
	 */
	ALWAYS_INLINE static void NOP() {
		asm volatile("NOP");
	}
}
