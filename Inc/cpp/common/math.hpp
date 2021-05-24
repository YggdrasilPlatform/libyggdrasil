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
  *  @file cpp/common/math.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Commonly used math functions
  */

#pragma once

#include <array>
#include <cmath>
#include <numeric>
#include <type_traits>

#include <cpp/common/attributes.hpp>
#include <cpp/common/types.hpp>

namespace bsp::math {

	/**
	 * @brief Pi constant
	 * @note Replace with version in std library once it becomes available in toolchain
	 *
	 * @tparam T Precision type
	 */
	template<typename T>
	constexpr static inline T Pi = T(3.14159265358979323846264338327950288419716939937510);

	/**
	 * @brief e constant
	 * @note Replace with version in std library once it becomes available in toolchain
	 *
	 * @tparam T Precision type
	 */
	template<typename T>
	constexpr static inline T e  = T(2.71828182845904523536028747135266249775724709369995);


	/**
	 * @brief Clamps a input value between a min and max value
	 *
	 * @param value Input
	 * @param min Min value
	 * @param max Max value
	 * @return Clamped value
	 */
	template<typename T>
	constexpr T clamp(T value, T min, T max) {
		return std::min(std::max(value, min), max);
	}

	/**
	 * @brief Conversion between degree and radian
	 *
	 * @param deg Degree
	 * @return Radians
	 */
	template<typename T>
	constexpr T degreeToRadian(T deg) {
		return (deg / 360.0) * 2 * Pi<T>;
	}

	/**
	 * @brief Conversion between radian and degree
	 *
	 * @param rad Radians
	 * @return Degrees
	 */
	template<typename T>
	constexpr T radianToDegree(T rad) {
		return (rad / (2 * Pi<T>)) * 360.0;
	}

	/**
	 * @brief Kibibyte literal
	 */
    ALWAYS_INLINE constexpr u64 operator ""_kB(u64 n) {
        return n * u64(1024);
    }

    /**
     * @brief Mibibyte literal
     */
    ALWAYS_INLINE constexpr u64 operator ""_MB(u64 n) {
        return operator""_kB(n) * u64(1024);
    }

    /**
     * @brief Gibibyte literal
     */
    ALWAYS_INLINE constexpr u64 operator ""_GB(u64 n) {
        return operator""_MB(n) * u64(1024);
    }

    /**
     * @brief Calculates the CRC16 Checksum of the data in a container
     * @note There is also a hardware CRC module
     *
     * @tparam Polynomial Polynomial used to calculate LUT
     * @param data Iterateable Container type
     * @param initialValue Value to start at
     * @return CRC16 checksum
     */
    template<u16 Polynomial = 0x8005>
    constexpr u16 crc16(const auto &data, u16 initialValue = 0x00) {
    	// Lookup table generation
    	constexpr auto Table = [] {
            std::array<u16, 256> table;

            for (u16 i = 0; i < 256; i++) {
                u16 crc = 0;
                u16 c = i;

                for (u16 j = 0; j < 8; j++) {
                    if (((crc ^ c) & 0x0001U) != 0)
                        crc = (crc >> 1U) ^ Polynomial;
                    else
                        crc >>= 1U;

                    c >>= 1U;
                }

                table[i] = crc;
            }

            return table;
        }();

        // CRC16 calculation
        u16 crc = initialValue;
        for (u8 byte : data) {
            crc = (crc >> 8) ^ Table[(crc ^ u16(byte)) & 0x00FF];
        }

        return crc;
    }

    /**
     * @brief Calculates the CRC32 Checksum of the data in a container
     *
     * @tparam Polynomial Polynomial used to calculate LUT
     * @param data Iterateable Container type
     * @param initialValue Value to start at
     * @return CRC32 checksum
     */
    template<u32 Polynomial = 0x04C11DB7>
    u32 crc32(const auto &data, u32 initialValue = 0x00) {
    	// Lookup table generation
        constexpr auto Table = [] {
            std::array<u32, 256> table = {0};

            for (u32 i = 0; i < 256; i++) {
                u32 c = i;
                for (size_t j = 0; j < 8; j++) {
                    if (c & 1)
                        c = Polynomial ^ (c >> 1);
                    else
                        c >>= 1;
                }
                table[i] = c;
            }

            return table;
        }();

        // CRC32 calculation
        u32 crc = initialValue;
        for (u8 byte : data) {
            crc = Table[(crc ^ byte) & 0xFF] ^ (crc >> 8);
        }

        return ~crc;
    }

    /**
     * @brief Converts a Binary Coded Decimal value to Binary
     *
     * @param bcd BCD input
     * @return Binary representation
     */
	ALWAYS_INLINE constexpr u8 bcdToBinary(u8 bcd) {
	    return (bcd & 0x0F) + 10 * ((bcd >> 4) & 0x0F);
	}

    /**
     * @brief Converts a Binary value to Binary Coded Decimal
     *
     * @param bin Binary input
     * @return BCD representation
     */
	ALWAYS_INLINE constexpr u8 binaryToBcd(u8 bin) {
	    return (bin % 10) | ((bin / 10) << 4);
	}

}
