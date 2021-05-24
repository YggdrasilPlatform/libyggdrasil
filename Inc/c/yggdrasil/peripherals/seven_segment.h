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

C_LINKAGE void yggdrasil_SevenSegment_SetUnsigned(u16 value);
C_LINKAGE void yggdrasil_SevenSegment_SetSigned(i16 value);
C_LINKAGE void yggdrasil_SevenSegment_SetHexadecimal(u16 value);
C_LINKAGE void yggdrasil_SevenSegment_SetFloatingPoint(float value);
C_LINKAGE void yggdrasil_SevenSegment_SetDigit(char value);
C_LINKAGE void yggdrasil_SevenSegment_EnableDigit(u8 number);
C_LINKAGE void yggdrasil_SevenSegment_Disable();
