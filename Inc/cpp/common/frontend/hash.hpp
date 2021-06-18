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
  *  @file cpp/common/frontend/hash.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the HASH abstraction
  */

#pragma once

#include <cpp/common/registers.hpp>
#include <cpp/common/attributes.hpp>

#include <array>

namespace bsp::drv {

	/**
	 * @brief Base class for the Hash abstraction
	 *
	 * @tparam Context Hash context
	 * @tparam HashImpl Hash Implementation
	 */
	template<auto Context, template<addr_t> typename HashImpl>
	struct Hash {
		Hash() = delete;
		Hash(const Hash&) = delete;
		auto operator=(const Hash&) = delete;

		using Impl = HashImpl<Context>;

		/**
		 * @brief Init function
		 *
		 * @return True when successfully started, false when not
		 */
		static auto init(auto ... args) {
			return Impl::init(args...);
		}

		/**
		 * @brief Deinit function
		 *
		 * @return True when successfully stopped, false when not
		 */
		static auto deinit(auto ... args) {
			return Impl::deinit(args...);
		}

		/**
		 * @brief Hardware accelerated CRC8 caluclation
		 *
		 * @param data Data to calculate CRC of
		 * @param initValue Start value
		 * @param polynomial Used polynomial
		 * @param xorOut Value to xor result value with
		 * @note By default this function uses the CRC-8 settings
		 */
		[[nodiscard]] static u8 getCRC8(const auto &data, u8 initValue = 0x00, u8 polynomial = 0x07, u8 xorOut = 0x00) noexcept {
			return Impl::getCRC8(data, initValue, polynomial) ^ xorOut;
		}

		/**
		 * @brief Hardware accelerated CRC16 caluclation
		 *
		 * @param data Data to calculate CRC of
		 * @param initValue Start value
		 * @param polynomial Used polynomial
		 * @param xorOut Value to xor result value with
		 * @note By default this function uses the CRC-16/ARC settings
		 */
		[[nodiscard]] static u16 getCRC16(const auto &data, u16 initValue = 0x0000, u16 polynomial = 0x8005, u16 xorOut = 0x0000) noexcept {
			return Impl::getCRC16(data, initValue, polynomial) ^ xorOut;
		}

		/**
		 * @brief Hardware accelerated CRC32 caluclation
		 *
		 * @param data Data to calculate CRC of
		 * @param initValue Start value
		 * @param polynomial Used polynomial
		 * @param xorOut Value to xor result value with
		 * @note By default this function uses the CRC-32 (ethernet) settings
		 */
		[[nodiscard]] static u32 getCRC32(const auto &data, u32 initValue = 0xFFFF'FFFF, u32 polynomial = 0x04C11DB7, u32 xorOut = 0xFFFFFFFF) noexcept {
			return Impl::getCRC32(data, initValue, polynomial) ^ xorOut;
		}

	};

}
