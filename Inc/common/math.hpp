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

#include <array>
#include <cmath>
#include <numeric>
#include <type_traits>

#include <common/attributes.hpp>
#include <common/types.hpp>

namespace bsp::math {

	template<typename T>
	constexpr static inline T Pi = T(3.14159265358979323846264338327950288419716939937510);

	template<typename T>
	constexpr static inline T e  = T(2.71828182845904523536028747135266249775724709369995);



	template<typename T>
	constexpr T clamp(T value, T min, T max) {
		return std::max(std::min(value, min), max);
	}

	template<typename T>
	constexpr T degreeToRadian(T deg) {
		return (deg / 360.0) * 2 * Pi<T>;
	}

	template<typename T>
	constexpr T radianToDegree(T rad) {
		return (rad / (2 * Pi<T>)) * 360.0;
	}

    ALWAYS_INLINE constexpr u64 operator ""_kB(u64 n) {
        return n * u64(1024);
    }

    ALWAYS_INLINE constexpr u64 operator ""_MB(u64 n) {
        return operator""_kB(n) * u64(1024);
    }

    ALWAYS_INLINE constexpr u64 operator ""_GB(u64 n) {
        return operator""_MB(n) * u64(1024);
    }

    template<u16 Polynomial = 0x8005>
    u16 crc16(const auto &data, u16 initialValue = 0x00) {
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

        u16 crc = initialValue;
        for (u8 byte : data) {
            crc = (crc >> 8) ^ Table[(crc ^ u16(byte)) & 0x00FF];
        }

        return crc;
    }

    template<u32 Polynomial = 0x04C11DB7>
    u32 crc32(const auto &data, u32 initialValue = 0x00) {
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

        u32 crc = initialValue;
        for (u8 byte : data) {
            crc = Table[(crc ^ byte) & 0xFF] ^ (crc >> 8);
        }

        return ~crc;
    }

}
