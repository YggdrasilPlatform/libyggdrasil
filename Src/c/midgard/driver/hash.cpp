 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Midgard -                             *
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
  *  @file midgard/driver/hash.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Hash abstraction implementation for Midgard
  */

#if BOARD == MIDGARD

	#include <cpp/common/registers.hpp>
	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/hash.h>

	#include <yggdrasil.h>

	#include <math.h>

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

	using DR 	= bsp::Register<0x4002'3000, RegisterMap::DR, u32>;
	using IDR 	= bsp::Register<0x4002'3000, RegisterMap::IDR, u32>;
	using CR 	= bsp::Register<0x4002'3000, RegisterMap::CR, u32>;
	using INIT 	= bsp::Register<0x4002'3000, RegisterMap::INIT, u32>;
	using POL 	= bsp::Register<0x4002'3000, RegisterMap::POL, u32>;

	static inline auto Data			= typename DR::template Field<0, 31>();			///< Data register

	static inline auto HASHRESET	= typename IDR::template Field<0, 0>();			///< Reset bit
	static inline auto POLYSIZE		= typename IDR::template Field<3, 4>();			///< Polynomial size (7, 8, 16 or 32 bit)

	static inline auto InitialValue = typename INIT::template Field<0, 31>();		///< Used to write the CRC initial value.
	static inline auto Polynomial 	= typename POL::template Field<0, 31>(); 		///< Used to write the coefficients of the polynomial to be used for CRC calculation


	/**
	 * @brief Calculates CRC32
	 *
	 * @param data Input data
	 * @param initValue initial value
	 * @param polynomial CRC polynomial
	 * @return CRC32 result
	 */
	static u32 calculate(void *data, size_t size, u32 initValue, u32 polynomial) noexcept {
		InitialValue = initValue;			// Set the initial value register
		Polynomial = polynomial;			// Set the polynomial to the register
		HASHRESET = true;						// Reset to force the CRC to update the set registers
		u8 *bytes = static_cast<u8 *>(data);


		for (u32 i = 0; i < size; i += sizeof(u32)) {
			if (size >= sizeof(u32))									// Check if 4 or more bytes are left
				Data = bsp::byteSwap(*reinterpret_cast<u32*>(&bytes[i]));	// Write new data to the CRC
			else {														// When less than 4 bytes are left
				u32 value = 0;
				std::memcpy(&value, &bytes[i], size - i);				// Copy the left bytes to the local 32 bit variable
				Data = bsp::byteSwap(value);									// Write the last bytes to the CRC
			}
		}

		return Data;													// Return the calculated CRC
	}

	C_LINKAGE bool yggdrasil_HASH_Init(void){
		return bsp::Hash::init();
	}

	C_LINKAGE bool yggdrasil_HASH_Deinit(void){
		return bsp::Hash::deinit();
	}

	C_LINKAGE u8   yggdrasil_HASH_getCRC8(void *data, size_t size, u8 initValue, u8 polynomial, u8 xorOut) {
		POLYSIZE = 0b10;	// 8 Bit polynomial
		return (calculate(data, size, initValue, polynomial) & 0xFF) ^ xorOut;
	}

	C_LINKAGE u16  yggdrasil_HASH_getCRC16(void *data, size_t size, u16 initValue, u16 polynomial, u16 xorOut) {
		POLYSIZE = 0b01;	// 16 Bit polynomial
		return (calculate(data, size, initValue, polynomial) & 0xFFFF) ^ xorOut;
	}

	C_LINKAGE u32  yggdrasil_HASH_getCRC32(void *data, size_t size, u32 initValue, u32 polynomial, u32 xorOut) {
		POLYSIZE = 0b00;	// 32 Bit polynomial
		return (calculate(data, size, initValue, polynomial) & 0xFFFF'FFFF) ^ xorOut;
	}


#endif
