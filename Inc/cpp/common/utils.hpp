 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
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
  *  @file cpp/common/utils.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Commonly used helper functions
  */

#pragma once

#include <cpp/common/attributes.hpp>

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
	 *
	 * Example use: auto cleanup = SCOPE_GUARD { doCleanup(); };
	 */
	#define SCOPE_GUARD ::bsp::scope_guard::ScopeGuardOnExit() + [&]()

	/**
	 * @brief Scope Guard for always executing code when exiting the current scope
	 *
	 * Example use: ON_SCOPE_EXIT { doCleanup(); };
	 */
	#define ON_SCOPE_EXIT auto ANONYMOUS_VARIABLE(SCOPE_EXIT_) = SCOPE_GUARD

	namespace scope_guard {

		/**
		 * @brief Scope Guard implementation
		 */
		template<class F>
		class ScopeGuardImpl {
		private:
			F m_func;
			bool m_active;
		public:
			constexpr ScopeGuardImpl(F func) : m_func(std::move(func)), m_active(true) { }
			~ScopeGuardImpl() { if (this->m_active) { this->m_func(); } }

			/**
			 * @brief Releases the scope guard and prevents it from being executed when going out of scope
			 */
			void release() { this->m_active = false; }

			ScopeGuardImpl(ScopeGuardImpl &&other) noexcept : m_func(std::move(other.m_func)), m_active(other.m_active) {
				other.cancel();
			}

			ScopeGuardImpl& operator=(ScopeGuardImpl &&) = delete;
		};

		enum class ScopeGuardOnExit { };

		/**
		 * Helper operator overload to easily generate a scope guard
		 */
		template <typename F>
		constexpr ScopeGuardImpl<F> operator+(ScopeGuardOnExit, F&& f) {
			return ScopeGuardImpl<F>(std::forward<F>(f));
		}

	}

	/**
	 * @brief std::bit_cast implementation for doing reinterpret_cast-style conversion
	 * without invoking undefined behaviour
	 * @warning This is a terrible bit_cast implementation! Replace this with actual std::bit_cast once the toolchain supports it (GCC 11.1+)
	 *
	 * @tparam To Type to cast to
	 * @param src Value to bit-cast to type of To
	 */
	template <typename To, typename From>
	To bit_cast(const From& src) noexcept {
		return *reinterpret_cast<const To*>(&src);
	}

	/**
	 * @brief Signals the compiler that it is impossible to reach this line of code
	 * Useful for optimization
	 * @warning If used incorrectly and this line is reached anyways, the program is undefined
	 */
	NO_RETURN ALWAYS_INLINE static void unreachable() {
		__builtin_unreachable();
	}

	/**
	 * @brief Swaps bytes of input value to convert between big and little endian
	 * @param value Integral value to swap
	 * @tparam T Type of value to swap
	 */
	template<typename T>
	constexpr T byteSwap(T value) {
		static_assert(std::is_integral<T>::value, "Only integral types can be byte swapped");
		static_assert(sizeof(T) <= sizeof(u64), "Value cannot be bigger than 64 bit");

	    if constexpr (sizeof(T) == 1) 		return value;
	    else if constexpr (sizeof(T) == 2) 	return __builtin_bswap16(value);
	    else if constexpr (sizeof(T) == 4) 	return __builtin_bswap32(value);
	    else if constexpr (sizeof(T) == 8) 	return __builtin_bswap64(value);
	    else bsp::unreachable();
	}

	/**
	 * @brief Casts a scoped enum type into its underlying value
	 *
	 * @tparam T Enum type
	 * @param value Enum value
	 * @return Underlying value
	 */
	template<typename T>
	auto enumValue(T value) {
		static_assert(std::is_enum<T>::value, "Cannot get value of non-enum type");

		return static_cast<typename std::underlying_type<T>::type>(value);
	}

	/**
	 * @brief Helper class to store the data of a given type in reverse order
	 * @tparam T Type stored
	 */
	template<typename T>
	struct PACKED ByteSwapped {
	    constexpr ByteSwapped() : m_value(0) {}
	    constexpr ByteSwapped(T value) : m_value(byteSwap(value)) {}

	    /**
	     * @brief Transparently return byte swapped value
	     *
	     * @return Byte swapped value
	     */
	    constexpr operator T() const noexcept {
	        return byteSwap(this->m_value);
	    }

	    /**
	     * @brief Transparently assign value and store it byte swapped
	     *
	     * @param value Value
	     * @return Current object
	     */
	    constexpr auto operator=(T value) {
	        this->m_value = byteSwap(value);

	        return *this;
	    }

	    /**
	     * @brief Copy assignment operator
	     *
	     * @param value Other value
	     * @return Current object
	     */
	    constexpr auto operator=(const ByteSwapped &value) {
	        this->m_value = value.m_value;

	        return *this;
	    }
	private:
	    T m_value;
	};

	/**
	 * @brief Confuses the compiler to prevent it from optimizing out a variable. Helpful for debugging
	 *
	 * @param value Variable to prevent optimization of
	 */
	ALWAYS_INLINE void doNotOptimize(const auto& value) {
	  asm volatile("" : : "r,m"(value) : "memory");
	}
}
