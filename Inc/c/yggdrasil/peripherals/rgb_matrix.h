 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Yggdrasil -                           *
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
  *  @file c/yggdrasil/peripherals/rgb_matrix.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the SK9822 RGB Led (APA102 clone)
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Initialization function
 *
 * @return Success
 */
C_LINKAGE void yggdrasil_RGBMatrix_Init(void);

/**
 * @brief Enables the SK9822 led
 */
C_LINKAGE void yggdrasil_RGBMatrix_Enable(void);

/**
 * @brief Disable the SK9822 led
 */
C_LINKAGE void yggdrasil_RGBMatrix_Disable(void);

/**
 * @brief Clear all leds
 */
C_LINKAGE void yggdrasil_RGBMatrix_Clear(void);

/**
 * @brief set a single led to RGBA8 color
 *
 * @param index Led number from 0 to 8
 * @param color RGBA8 color
 */
C_LINKAGE void yggdrasil_RGBMatrix_SetLed(u8 index, RGBA8 color);

/**
 * @brief set multiple leds to RGBA8 color using a bit mask
 *
 * @param enableMask Bitmask to enabled the leds
 * @param color RGBA8 color
 */
C_LINKAGE void yggdrasil_RGBMatrix_SetLedMasked(u16 enableMask, RGBA8 color);

/**
 * @brief Function to display a dice
 *
 * @param number Number to display
 * @param color RGBA8 color
 */
C_LINKAGE void yggdrasil_RGBMatrix_Dice(u8 number, RGBA8 color);

/**
 * @brief Send the saved color values to the leds
 */
C_LINKAGE void yggdrasil_RGBMatrix_Flush(void);
