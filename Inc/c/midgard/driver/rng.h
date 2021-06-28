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
  *  @file c/midgard/driver/rng.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief RNG abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

/**
 * @brief RNG handle type
 */
typedef struct {

} rng_t;

/**
 * @brief RNG initialization
 *
 * @param rng RNG handel
 * @return Success
 */
C_LINKAGE bool yggdrasil_RNG_Init(rng_t rng);

/**
 * @brief RNG deinitialization
 *
 * @param rng RNG handel
 * @return Success
 */
C_LINKAGE bool yggdrasil_RNG_Deinit(rng_t rng);

/**
 * @brief Get a random u8
 *
 * @param rng RNG handel
 * @return u8 random number
 */
C_LINKAGE u8 yggdrasil_RNG_GetU8(rng_t rng);

/**
 * @brief Get a random u16
 *
 * @param rng RNG handel
 * @return u16 random number
 */
C_LINKAGE u16 yggdrasil_RNG_GetU16(rng_t rng);

/**
 * @brief Get a random u32
 *
 * @param rng RNG handel
 * @return u32 random number
 */
C_LINKAGE u32 yggdrasil_RNG_GetU32(rng_t rng);

