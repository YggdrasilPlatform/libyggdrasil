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
	DisplayOrientation_Portrait	= 0x00,
};

/**
 * @brief Predefined colors
 */
enum Color {
	Color_Black 	= 0b00000000,
	Color_Navy 		= 0b00000010,
	Color_Blue		= 0b00000011,
	Color_Green		= 0b00001100,
	Color_Teal		= 0b00001001,
	Color_Lime		= 0b00011100,
	Color_Aqua		= 0b00011111,
	Color_Maroon	= 0b01100000,
	Color_Purple	= 0b01100011,
	Color_Olive		= 0b01101100,
	Color_Gray		= 0b01001001,
	Color_Red		= 0b11100000,
	Color_Fuchsia	= 0b11100011,
	Color_Yellow	= 0b11111100,
	Color_Orange	= 0b11110000,
	Color_White		= 0b11111111,
};

/*
 * @brief Display initialization
 *
 * @param orientation Display orientation
 * @return True when successful, false when not
 */
C_LINKAGE bool yggdrasil_Display_Init(enum DisplayOrientation orientation);

/*
 * @brief Display reset
 */
C_LINKAGE void yggdrasil_Display_Reset(void);

/*
 * @brief Enable the display
 */
C_LINKAGE void yggdrasil_Display_TurnOn(void);

/*
 * @brief Disable the display
 */
C_LINKAGE void yggdrasil_Display_TurnOff(void);

/*
 * @brief Get the display width
 *
 * @return display width
 */
C_LINKAGE u16  yggdrasil_Display_getWidth(void);

/*
 * @brief Get the display height
 *
 * @return display height
 */
C_LINKAGE u16  yggdrasil_Display_getHeight(void);

/*
 * @brief Set the color palette
 *
 * @param palettet Color palette
 */
C_LINKAGE void yggdrasil_Display_SetPalette(palette_t *palette);

/*
 * @brief Get the default color palette
 *
 * @return Default color palette
 */
C_LINKAGE palette_t yggdrasil_Display_GetDefaultPalette(void);

/*
 * @brief Get the framebuffer address
 *
 * @return framebuffer address
 */
C_LINKAGE void * yggdrasil_Display_GetFrameBufferAddress(void);

/**
 * @brief Clear the display to a color
 *
 * @param paletteIndex Index for the color
 */
C_LINKAGE void yggdrasil_Display_Clear(u8 paletteIndex);

/**
 * @brief Draw a rectangle
 *
 * @param x1 X Start coordinate
 * @param y1 Y Start coordinate
 * @param x2 X End coordinate
 * @param y2 Y End coordinate
 * @param colorIndex Index for the color
 */
C_LINKAGE void yggdrasil_Display_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex);

/**
 * @brief Draw a filled rectangle
 *
 * @param x1 X Start coordinate
 * @param y1 Y Start coordinate
 * @param x2 X End coordinate
 * @param y2 Y End coordinate
 * @param colorIndex Index for the color
 */
C_LINKAGE void yggdrasil_Display_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex);

/**
 * @brief Draw a single pixel
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param colorIndex Index for the color
 */
C_LINKAGE void yggdrasil_Display_DrawPixel(u16 x, u16 y, u8 colorIndex);

/**
 * @brief Draw a line
 *
 * @param x1 X Start coordinate
 * @param y1 Y Start coordinate
 * @param x2 X End coordinate
 * @param y2 Y End coordinate
 * @param colorIndex Index for the color
*/
C_LINKAGE void yggdrasil_Display_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex);

/**
 * @brief Draw a cricle
 *
 * @param centerX X Position of the center
 * @param centerY Y Position of the center
 * @param readius Radius
 * @param colorIndex Index for the color
 */
C_LINKAGE void yggdrasil_Display_DrawCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex);

/**
 * @brief Draw a filled cricle
 *
 * @param centerX X Position of the center
 * @param centerY Y Position of the center
 * @param readius Radius
 * @param colorIndex Index for the color
 */
C_LINKAGE void yggdrasil_Display_FillCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex);

/**
 * @brief Draw a single character
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param c Charachter
 * @param colorIndex Index for the color
 * @param font Font
 */
C_LINKAGE void yggdrasil_Display_DrawCharacter(u16 x, u16 y, char c, u8 colorIndex, Font *font);

/**
 * @brief Draw a string
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param string String view
 * @param colorIndex Index for the color
 * @param font Font
 */
C_LINKAGE void yggdrasil_Display_DrawString(u16 x, u16 y, const char *string, u8 colorIndex, Font *font);



