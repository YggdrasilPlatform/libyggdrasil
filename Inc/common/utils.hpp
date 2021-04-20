/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file common/utils.hpp                                         *
  *  @ingroup common                                                *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Commonly used helper functions						    *
  *  			                                                    *
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

#include <common/attributes.hpp>

#include <cstring>		// memcpy
#include <type_traits>	// Type trait checks
#include <utility>


#define TOKEN_CONCAT_IMPL(x, y) x ## y
#define TOKEN_CONCAT(x, y) TOKEN_CONCAT_IMPL(x, y)
#define ANONYMOUS_VARIABLE(prefix) TOKEN_CONCAT(prefix, __COUNTER__)


namespace bsp {

	/**
	 * @brief Helper type trait for using static_asserts that should always trigger an error when evaluated
	 */
	template<typename T>
	struct dependent_false : std::false_type {};

	template<typename T>
	constexpr auto dependent_false_v = dependent_false<T>::value;


	/**
	 * @brief Scope Guard for executing code when exiting the current scope with the ability to release it.
	 * @example auto cleanup = SCOPE_GUARD { doCleanup(); };
	 */
	#define SCOPE_GUARD ::bsp::scope_guard::ScopeGuardOnExit() + [&]()

	/**
	 * @brief Scope Guard for always executing code when exiting the current scope
	 * @example ON_SCOPE_EXIT { doCleanup(); };
	 */
	#define ON_SCOPE_EXIT auto ANONYMOUS_VARIABLE(SCOPE_EXIT_) = SCOPE_GUARD

	/**
	 * @brief Scope Guard implementation
	 */
	namespace scope_guard {

		template<class F>
		class ScopeGuardImpl {
		private:
			F m_func;
			bool m_active;
		public:
			constexpr ScopeGuardImpl(F func) : m_func(std::move(func)), m_active(true) { }
			~ScopeGuardImpl() { if (this->m_active) { this->m_func(); } }
			void release() { this->m_active = false; }

			ScopeGuardImpl(ScopeGuardImpl &&other) noexcept : m_func(std::move(other.m_func)), m_active(other.m_active) {
				other.cancel();
			}

			ScopeGuardImpl& operator=(ScopeGuardImpl &&) = delete;
		};

		enum class ScopeGuardOnExit { };

		template <typename F>
		constexpr ScopeGuardImpl<F> operator+(ScopeGuardOnExit, F&& f) {
			return ScopeGuardImpl<F>(std::forward<F>(f));
		}

	}

	/**
	 * @brief std::bit_cast implementation for doing reinterpret_cast-style conversion
	 * without invoking undefined behaviour
	 * @tparam To Type to cast to
	 * @param src Value to bit-cast to type of To
	 */
	template <typename To, typename From>
	constexpr To bit_cast(const From& src) noexcept {
		static_assert(sizeof(From) == sizeof(To), "Source and destination type must be the same size");
		static_assert(std::is_trivially_constructible_v<From>, "Source type needs to be trivially constructible");
		static_assert(std::is_trivially_constructible_v<To>, "Destination type needs to be trivially constructible");

		To dst = {0};
		std::memcpy(&dst, &src, sizeof(To));
		return dst;
	}

	/**
	 * @brief Signals the compiler that it is impossible to reach this line of code
	 * Useful for optimization
	 * @warn If used incorrectly and this line is reached anyways, the program is undefined
	 */
	NO_RETURN ALWAYS_INLINE static void unreachable() {
		__builtin_unreachable();
	}

	/**
	 * @brief Swaps bytes of input value to convert between big and little endian
	 * @param value 8 bit value
	 */
	ALWAYS_INLINE static u8 byteSwap(u8 value) {
		return value;
	}

	/**
	 * @brief Swaps bytes of input value to convert between big and little endian
	 * @param value 16 bit value
	 */
	ALWAYS_INLINE static u16 byteSwap(u16 value) {
		return __builtin_bswap16(value);
	}

	/**
	 * @brief Swaps bytes of input value to convert between big and little endian
	 * @param value 32 bit value
	 */
	ALWAYS_INLINE static u32 byteSwap(u32 value) {
		return __builtin_bswap32(value);
	}

	/**
	 * @brief Swaps bytes of input value to convert between big and little endian
	 * @param value 64 bit value
	 */
	ALWAYS_INLINE static u64 byteSwap(u64 value) {
		return __builtin_bswap64(value);
	}

	#undef assert

	WEAK void assertionFailed(const char *message, const char *file, const char *function, u32 line) {
		while (true);
	}

	[[maybe_unused]] static void assert(bool condition, const char *message, const char *file = __builtin_FILE(), const char *function = __builtin_FUNCTION(), u32 line = __builtin_LINE()) {
		if (!condition) {
			assertionFailed(message, file, function, line);
		}
	}

}
