/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file midgard/driver/hash.hpp                                  *
  *  @ingroup midgard                                               *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief hash abstraction implementation for Midgard 			*
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

#include <common/driver/hash.hpp>

#include <common/registers.hpp>
#include <common/attributes.hpp>

#include <array>
#include <cmath>
#include <type_traits>

namespace bsp::mid::drv {

	/**
	 * @brief CRC abstraction
	 * @tparam BaseAddress CRC Peripheral base address
	 */
	template<addr_t BaseAddress>
	struct Hash {
		Hash() = delete;
		Hash(const Hash&) = delete;
		auto operator=(const Hash&) = delete;

		/**
		 * @brief Hardware accelerated CRC8 caluclation
		 * @param data Data to calculate CRC of
		 * @param initValue Start value
		 * @param polynomial Used polynomial
		 */
		static u8 getCRC8(const auto &data, u8 initValue = 0x00, u8 polynomial = 0xD5) noexcept {
			POLYSIZE = 0b10;	// 8 Bit polynomial
			return calculate(data, initValue, polynomial) & 0xFF;
		}

		/**
		 * @brief Hardware accelerated CRC16 caluclation
		 * @param data Data to calculate CRC of
		 * @param initValue Start value
		 * @param polynomial Used polynomial
		 */
		static u16 getCRC16(const auto &data, u16 initValue = 0x00, u16 polynomial = 0x8005) noexcept {
			POLYSIZE = 0b01;	// 16 Bit polynomial
			return calculate(data, initValue, polynomial) & 0xFFFF;
		}

		/**
		 * @brief Hardware accelerated CRC32 caluclation
		 * @param data Data to calculate CRC of
		 * @param initValue Start value
		 * @param polynomial Used polynomial
		 */
		static u32 getCRC32(const auto &data, u32 initValue = 0x00, u32 polynomial = 0x04C11DB7) noexcept {
			POLYSIZE = 0b00;	// 32 Bit polynomial
			return calculate(data, initValue, polynomial) & 0xFFFF'FFFF;
		}

	private:
		enum class RegisterMap : u8 {
			DR 		= 0x00,
			IDR 	= 0x04,
			CR 		= 0x08,
			INIT 	= 0x10,
			POL 	= 0x14
		};

	    using DR 	= Register<BaseAddress, RegisterMap::DR, u32>;
	    using IDR 	= Register<BaseAddress, RegisterMap::IDR, u32>;
	    using CR 	= Register<BaseAddress, RegisterMap::CR, u32>;
	    using INIT 	= Register<BaseAddress, RegisterMap::INIT, u32>;
	    using POL 	= Register<BaseAddress, RegisterMap::POL, u32>;

	    static inline auto Data		= typename DR::template Field<0, 31>();

	    static inline auto RESET	= typename IDR::template Field<0, 0>();
	    static inline auto POLYSIZE	= typename IDR::template Field<3, 4>();

	    static inline auto InitialValue = typename INIT::template Field<0, 31>();
	    static inline auto Polynomial 	= typename POL::template Field<0, 31>();


	    static u32 calculate(const auto &data, u32 initValue, u32 polynomial) noexcept {
	    	InitialValue = initValue;
	    	Polynomial = polynomial;
	    	RESET = true;

	    	std::array<u8, sizeof(data)> bytes;
	    	std::memcpy(bytes.data(), &data, bytes.size());

	    	for (u32 i = 0; i < bytes.size(); i += sizeof(u32)) {
	    		if (bytes.size() >= sizeof(u32))
	    			Data = byteSwap(*reinterpret_cast<u32*>(&bytes[i]));
	    		else {
	    			u32 value = 0;
	    			std::memcpy(&value, &bytes[i], bytes.size() - i);
	    			Data = byteSwap(value);
	    		}
	    	}

	    	return Data;
	    }

	};

}
