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
  *  @file c/yggdrasil/peripherals/seven_segment.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the Seven segment display
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Initialization function
 *
 * @return Success
 */
C_LINKAGE void yggdrasil_SevenSegment_Init(void);

/**
 * @brief Display a unsigned value from 0 to 9999 on the 7 segments
 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
 *
 * @param value Value to display
 */
C_LINKAGE void yggdrasil_SevenSegment_SetUnsigned(u16 value);

/**
 * @brief Display a signed value from -999 to 999 on the 7 segments
 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
 *
 * @param value Value to display
 */
C_LINKAGE void yggdrasil_SevenSegment_SetSigned(i16 value);

/**
 * @brief Display a unsigned value from 0 to 0xFFFF in hexadecimal on the 7 segments
 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
 *
 * @param value Value to display in hexadecimal
 */
C_LINKAGE void yggdrasil_SevenSegment_SetHexadecimal(u16 value);

/**
 * @brief Display a floating point value from -99.9 to 99.9 on the 7 segments, the function will show as many decimal places as possible
 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
 *
 * @param value Value to display
 */
C_LINKAGE void yggdrasil_SevenSegment_SetFloatingPoint(float value);

/**
 * @brief Set the segments to the given value, supports hexadecimal, '-' for minus and ' ' for an empty segment
 * @note The function does not enable any segment
 *
 * @param value Digit to set
 */
C_LINKAGE void yggdrasil_SevenSegment_SetDigit(char value);

/**
 * @brief Enable one single segment
 *
 * @param number Digit to enable
 */
C_LINKAGE void yggdrasil_SevenSegment_EnableDigit(u8 number);

/**
 * @brief Disable all segments
 */
C_LINKAGE void yggdrasil_SevenSegment_Disable(void);
