/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file common/registers.hpp                                     *
  *  @ingroup common                                                *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Zero-cost abstraction for accessing registers and 		*
  *  bits / bitfields within a register.                       		*
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

#include <common/types.hpp>
#include <common/attributes.hpp>

#include <type_traits>	// Type traits

namespace bsp {

	/**
	 * @brief Bitfield abstraction. Provides a way to read from, write to and pass
	 * around bitfields within registers as if they were normal variables.
	 * @tparam BaseAddress Register base address
	 * @tparam SizeType Register size
	 * @tparam From First bit to include in bitfield
	 * @tparam To Last bit to include in bitfield
	 */
	template<u32 BaseAddress, typename SizeType, u8 From, u8 To>
	struct BitField {
		/** @brief Mask to access the bitfield's bits */
		static constexpr SizeType Mask = ((1 << (To - From + 1)) - 1) << From;

		BitField() = default;

		/**
		 * @brief SizeType conversion operator overload
		 * @return Value in bitfield
		 */
		[[nodiscard]] ALWAYS_INLINE constexpr operator SizeType() const {
			return (*reinterpret_cast<IO<SizeType>*>(BaseAddress) & Mask) >> From;
		}

		/**
		 * @brief Assignment operator overload
		 * @tparam T Type of parameter. Must be unsigned
		 * @param value Value to assign to bitfield
		 * @return new value in bitfield
		 */
		template<typename T>
		ALWAYS_INLINE constexpr T operator=(T value) const {

			IO<SizeType>& registerRef = *reinterpret_cast<IO<SizeType>*>(BaseAddress);
			SizeType bitfieldValue = (registerRef & ~Mask) | ((static_cast<SizeType>(value) << From) & Mask);

			registerRef = bitfieldValue;

			return bitfieldValue;
		}

		static_assert(From <= To, "Start bit needs to be lower than end bit");
	};

	/**
	 * @brief MMIO Register abstraction. Gives access to bitfields within the register as well as
	 * a reference to the register value itself.
	 * @tparam BaseAddress Register block base address
	 * @tparam Offset Register offset from register block base address
	 * @tparam SizeType Register size
	 */
	template<addr_t BaseAddress, auto Offset, typename SizeType = reg_t>
	struct Register {
		/** @brief Reference to the register value*/
		static inline auto& Value = *reinterpret_cast<IO<SizeType>*>(BaseAddress + static_cast<addr_t>(Offset));

		/**
		 * @brief Bitfield access
		 * @tparam From First bit to include in bitfield
		 * @tparam To Last bit to include in bitfield
		 */
		template<u8 From, u8 To>
		using Field = BitField<BaseAddress, SizeType, From, To>;

		static_assert((BaseAddress % sizeof(SizeType)) == 0, "MMIO Register address is not correctly aligned");
	};

}
