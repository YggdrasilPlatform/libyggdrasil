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
	 *
	 * @tparam BaseAddress CRC Peripheral base address
	 */
	template<addr_t BaseAddress>
	struct Hash {
		Hash() = delete;
		Hash(const Hash&) = delete;
		auto operator=(const Hash&) = delete;

		/**
		 * @brief Hardware accelerated CRC8 caluclation
		 *
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
		 *
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
		 *
		 * @param data Data to calculate CRC of
		 * @param initValue Start value
		 * @param polynomial Used polynomial
		 */
		static u32 getCRC32(const auto &data, u32 initValue = 0x00, u32 polynomial = 0x04C11DB7) noexcept {
			POLYSIZE = 0b00;	// 32 Bit polynomial
			return calculate(data, initValue, polynomial) & 0xFFFF'FFFF;
		}

	private:
		/**
		 * @brief Register map
		 */
		enum class RegisterMap : u8 {
			DR 		= 0x00,			///< Data register
			IDR 	= 0x04,			///< Independent data register
			CR 		= 0x08,			///< Control register
			INIT 	= 0x10,			///< Initial CRC value
			POL 	= 0x14			///< CRC polynomial
		};

	    using DR 	= Register<BaseAddress, RegisterMap::DR, u32>;
	    using IDR 	= Register<BaseAddress, RegisterMap::IDR, u32>;
	    using CR 	= Register<BaseAddress, RegisterMap::CR, u32>;
	    using INIT 	= Register<BaseAddress, RegisterMap::INIT, u32>;
	    using POL 	= Register<BaseAddress, RegisterMap::POL, u32>;

	    static inline auto Data		= typename DR::template Field<0, 31>();			///< Data register

	    static inline auto RESET	= typename IDR::template Field<0, 0>();			///< Reset bit
	    static inline auto POLYSIZE	= typename IDR::template Field<3, 4>();			///< Polynomial size (7, 8, 16 or 32 bit)

	    static inline auto InitialValue = typename INIT::template Field<0, 31>();	///< Used to write the CRC initial value.
	    static inline auto Polynomial 	= typename POL::template Field<0, 31>(); 	///< Used to write the coefficients of the polynomial to be used for CRC calculation


	    /**
	     * @brief Calculates CRC32
	     *
	     * @param data Input data
	     * @param initValue initial value
	     * @param polynomial CRC polynomial
	     * @return CRC32 result
	     */
	    static u32 calculate(const auto &data, u32 initValue, u32 polynomial) noexcept {
	    	InitialValue = initValue;			// Set the initial value register
	    	Polynomial = polynomial;			// Set the polynomial to the register
	    	RESET = true;						// Reset to force the CRC to update the set registers

	    	std::array<u8, sizeof(data)> bytes;
	    	std::memcpy(bytes.data(), &data, bytes.size());

	    	for (u32 i = 0; i < bytes.size(); i += sizeof(u32)) {
	    		if (bytes.size() >= sizeof(u32))							// Check if 4 or more bytes are left
	    			Data = byteSwap(*reinterpret_cast<u32*>(&bytes[i]));	// Write new data to the CRC
	    		else {														// When less than 4 bytes are left
	    			u32 value = 0;
	    			std::memcpy(&value, &bytes[i], bytes.size() - i);		// Copy the left bytes to the local 32 bit variable
	    			Data = byteSwap(value);									// Write the last bytes to the CRC
	    		}
	    	}

	    	return Data;													// Return the calculated CRC
	    }

	};

}
