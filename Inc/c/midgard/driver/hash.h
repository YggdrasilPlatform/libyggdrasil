 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
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
  *  @file c/midgard/driver/hash.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Hash abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

/**
 * @brief Hash initialization
 */
C_LINKAGE bool yggdrasil_HASH_Init(void);

/**
 * @brief Hardware accelerated CRC8 caluclation
 *
 * @param data Data to calculate CRC of
 * @param size Size of the data
 * @param initValue Start value
 * @param polynomial Used polynomial
 * @param xorOut Value to xor result value with
 */
C_LINKAGE u8   yggdrasil_HASH_getCRC8(void *data, size_t size, u8 initValue, u8 polynomial, u8 xorOut);

/**
 * @brief Hardware accelerated CRC16 caluclation
 *
 * @param data Data to calculate CRC of
 * @param size Size of the data
 * @param initValue Start value
 * @param polynomial Used polynomial
 * @param xorOut Value to xor result value with
 */
C_LINKAGE u16  yggdrasil_HASH_getCRC16(void *data, size_t size, u16 initValue, u16 polynomial, u16 xorOut);

/**
 * @brief Hardware accelerated CRC32 caluclation
 *
 * @param data Data to calculate CRC of
 * @param size Size of the data
 * @param initValue Start value
 * @param polynomial Used polynomial
 * @param xorOut Value to xor result value with
 */
C_LINKAGE u32  yggdrasil_HASH_getCRC32(void *data, size_t size, u32 initValue, u32 polynomial, u32 xorOut);
