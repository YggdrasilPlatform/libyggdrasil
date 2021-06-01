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
  *  @brief Driver to use the LPS22HBTR pressure sensor
  */

#pragma once

#include <c/yggdrasil/types.h>

C_LINKAGE void yggdrasil_RGBMatrix_Enable();
C_LINKAGE void yggdrasil_RGBMatrix_Disable();
C_LINKAGE void yggdrasil_RGBMatrix_Clear();
C_LINKAGE void yggdrasil_RGBMatrix_SetLed(u8 index, RGBA8 color);
C_LINKAGE void yggdrasil_RGBMatrix_SetLedMasked(u16 enableMask, RGBA8 color);
C_LINKAGE void yggdrasil_RGBMatrix_Dice(u8 number, RGBA8 color);
C_LINKAGE void yggdrasil_RGBMatrix_Flush();
