#pragma once

#include <common/types.hpp>
#include <common/attributes.hpp>

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
