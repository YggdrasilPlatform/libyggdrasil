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
  *  @file c/midgard/driver/display.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Display abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>
#include <c/resources/fonts/fonts.h>

typedef struct {
	u32 colors[256];
} palette_t;

/**
 * @brief Display orientation
 */
enum DisplayOrientation {
	Portrait	= 0x00,
	Landscape	= 0x01
};

C_LINKAGE bool yggdrasil_Display_Init(enum DisplayOrientation orientation);
C_LINKAGE void yggdrasil_Display_Reset(void);
C_LINKAGE void yggdrasil_Display_TurnOn(void);
C_LINKAGE void yggdrasil_Display_TurnOff(void);
C_LINKAGE u16  yggdrasil_Display_getWidth(void);
C_LINKAGE u16  yggdrasil_Display_getHeight(void);
C_LINKAGE void yggdrasil_Display_SetPalette(palette_t *palette);
C_LINKAGE palette_t yggdrasil_Display_GetDefaultPalette(void);
C_LINKAGE void * yggdrasil_Display_GetFrameBufferAddress(void);
C_LINKAGE void yggdrasil_Display_Clear(u8 paletteIndex);
C_LINKAGE void yggdrasil_Display_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex);
C_LINKAGE void yggdrasil_Display_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex);
C_LINKAGE void yggdrasil_Display_DrawPixel(u16 x, u16 y, u8 colorIndex);
C_LINKAGE void yggdrasil_Display_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex);
C_LINKAGE void yggdrasil_Display_DrawCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex);
C_LINKAGE void yggdrasil_Display_FillCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex);
C_LINKAGE void yggdrasil_Display_DrawCharacter(u16 x, u16 y, char c, u8 colorIndex, Font *font);
C_LINKAGE void yggdrasil_Display_DrawString(u16 x, u16 y, const char *string, u8 colorIndex, Font *font);

