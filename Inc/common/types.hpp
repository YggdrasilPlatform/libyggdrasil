/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file common/types.hpp                                         *
  *  @ingroup common                                                *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Commonly used type definitions, helper templates and    *
  *  constants.                                                     *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#pragma once

#include <cstdint>	// Exact width integer definitions


/**
 * @brief Unsigned integer definitions
 * @{
 */
using u8	= std::uint8_t;
using u16	= std::uint16_t;
using u32	= std::uint32_t;
using u64	= std::uint64_t;
/** @} */

/**
 * @brief Signed integer definitions
 * @{
 */
using i8	= std::int8_t;
using i16	= std::int16_t;
using i32	= std::int32_t;
using i64	= std::int64_t;
/** @} */

namespace bsp {

	/**
	 * @brief MMIO type template
	 *
	 * @tparam T Type to access
	 */
	template<typename T>
	using IO = volatile T;

	/**
	 * @brief Helper class to create type-safe integral types
	 *
	 * @tparam T
	 */
	template<typename T>
	struct TypeSafe {
		TypeSafe() = default;
		TypeSafe(const TypeSafe&) = default;
		TypeSafe(TypeSafe &&) = default;

		explicit TypeSafe(T value) : value(value) {}
		explicit operator T() { return this->value; }
	private:
		T value;
	};

	/**
	 * @brief Creates a new, type-safe integral type
	 *
	 * @param T Type
	 * @example using TypeSafeU16 = TYPESAFE(u16);
	 */
	#define TYPESAFE(T) struct : public ::bsp::TypeSafe<int>{ using TypeSafe::TypeSafe; }

	/**
	 * @brief ARM32 specific types
	 * @{
	 */
	using addr_t 	= std::uint32_t;
	using reg_t 	= std::uint32_t;

	/**
	 * @brief ARM32 specific constants
	 * @{
	 */
	constexpr auto RegisterAlignment = alignof(reg_t);
	/** @} */

}
