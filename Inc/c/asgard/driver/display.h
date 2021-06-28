 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file c/asgard/driver/display.h
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Display abstraction implementation for Asgard
  */

#include <c/common/types.h>

#include <c/resources/fonts/fonts.h>

/**
 * @brief Predefined colors
 */
enum Color {
	Color_Black 	= 0b0000000000000000,
	Color_Navy 		= 0b0000000000010000,
	Color_Blue		= 0b0000000000011000,
	Color_Green		= 0b0000001100000000,
	Color_Teal		= 0b0000001000001000,
	Color_Lime		= 0b0000011100000000,
	Color_Aqua		= 0b0000011100011000,
	Color_Maroon	= 0b0110000000000000,
	Color_Purple	= 0b0110000000011000,
	Color_Olive		= 0b0110001100000000,
	Color_Gray		= 0b0100001000001000,
	Color_Red		= 0b1110000000000000,
	Color_Fuchsia	= 0b1110000000011000,
	Color_Yellow	= 0b1110011100000000,
	Color_Orange	= 0b1110010000000000,
	Color_White		= 0b1110011100011000,
};

/*
 * @brief Display initialization
 *
 * @return True when successful, false when not
 */
C_LINKAGE bool yggdrasil_Display_Init(void);

/*
 * @brief Display deinitialization
 *
 * @return True when successful, false when not
 */
C_LINKAGE bool yggdrasil_Display_Deinit(void);

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
 * @brief Get the framebuffer address
 *
 * @return framebuffer address
 */
C_LINKAGE void* yggdrasil_Display_GetFrameBufferAddress(void);

/**
 * @brief Clear the display to a color
 *
 * @param color RGB565 Color
 */
C_LINKAGE void yggdrasil_Display_Clear(u16 color);

/**
 * @brief Draw a rectangle
 *
 * @param x1 X Start coordinate
 * @param y1 Y Start coordinate
 * @param x2 X End coordinate
 * @param y2 Y End coordinate
 * @param color RGB565 Color
 */
C_LINKAGE void yggdrasil_Display_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

/**
 * @brief Draw a filled rectangle
 *
 * @param x1 X Start coordinate
 * @param y1 Y Start coordinate
 * @param x2 X End coordinate
 * @param y2 Y End coordinate
 * @param color RGB565 Color
 */
C_LINKAGE void yggdrasil_Display_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

/**
 * @brief Draw a single pixel
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param color RGB565 Color
 */
C_LINKAGE void yggdrasil_Display_DrawPixel(u16 x, u16 y, u16 color);

/**
 * @brief Draw a line
 *
 * @param x1 X Start coordinate
 * @param y1 Y Start coordinate
 * @param x2 X End coordinate
 * @param y2 Y End coordinate
 * @param color RGB565 Color
*/
C_LINKAGE void yggdrasil_Display_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

/**
 * @brief Draw a cricle
 *
 * @param centerX X Position of the center
 * @param centerY Y Position of the center
 * @param radius Radius
 * @param color RGB565 Color
 */
C_LINKAGE void yggdrasil_Display_DrawCircle(i16 centerX, i16 centerY, u16 radius, u16 color);

/**
 * @brief Draw a filled circle
 *
 * @param centerX X Position of the center
 * @param centerY Y Position of the center
 * @param radius Radius
 * @param color RGB565 Color
 */
C_LINKAGE void yggdrasil_Display_FillCircle(i16 centerX, i16 centerY, u16 radius, u16 color);

/**
 * @brief Draw a single character
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param c Character
 * @param color RGB565 Color
 * @param font Font
 */
C_LINKAGE void yggdrasil_Display_DrawCharacter(u16 x, u16 y, char c, u16 color, Font *font);

/**
 * @brief Draw a string
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param string String view
 * @param color RGB565 Color
 * @param font Font
 */
C_LINKAGE void yggdrasil_Display_DrawString(u16 x, u16 y, const char *string, u16 color, Font *font);



