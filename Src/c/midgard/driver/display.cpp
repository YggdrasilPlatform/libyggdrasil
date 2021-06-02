 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Midgard -                             *
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
  *  @file midgard/driver/spi.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief SPI abstraction implementation for Midgard
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS) && BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/display.h>

	#include <yggdrasil.h>

	#include <math.h>

	/*
	 * @brief Display initialization
	 *
	 * @param orientation Display orientation
	 * @return True when successful, false when not
	 */
	C_LINKAGE bool yggdrasil_Display_Init(enum DisplayOrientation orientation) {
		return bsp::Display::init(static_cast<bsp::Display::Impl::Orientation>(orientation));
	}

	/*
	 * @brief Display reset
	 */
	C_LINKAGE void yggdrasil_Display_Reset(void) {
		bsp::Display::reset();
	}

	/*
	 * @brief Enable the display
	 */
	C_LINKAGE void yggdrasil_Display_TurnOn(void) {
		bsp::Display::turnOn();
	}

	/*
	 * @brief Disable the display
	 */
	C_LINKAGE void yggdrasil_Display_TurnOff(void) {
		bsp::Display::turnOff();
	}

	/*
	 * @brief Get the display width
	 *
	 * @return display width
	 */
	C_LINKAGE u16  yggdrasil_Display_getWidth(void) {
		return bsp::Display::getWidth();
	}

	/*
	 * @brief Get the display height
	 *
	 * @return display height
	 */
	C_LINKAGE u16  yggdrasil_Display_getHeight(void) {
		return bsp::Display::getHeight();
	}

	/*
	 * @brief Set the color palette
	 *
	 * @param palettet Color palette
	 */
	C_LINKAGE void yggdrasil_Display_SetPalette(palette_t *palette) {
		std::array<u32, 256> data;
		std::copy(palette->colors, palette->colors + sizeof(palette->colors), data.begin());
		bsp::Display::setPalette(data);
	}

	/*
	 * @brief Get the default color palette
	 *
	 * @return Default color palette
	 */
	C_LINKAGE palette_t yggdrasil_Display_GetDefaultPalette(void) {
		palette_t result;
		auto palette = bsp::Display::getDefaultPalette();
		std::copy(palette.begin(), palette.end(), result.colors);
		return result;
	}

	/*
	 * @brief Get the framebuffer address
	 *
	 * @return framebuffer address
	 */
	C_LINKAGE void * yggdrasil_Display_GetFrameBufferAddress(void) {
		return bsp::Display::getFramebufferAddress();
	}

	/**
	 * @brief Clear the display to a color
	 *
	 * @param paletteIndex Index for the color
	 */
	C_LINKAGE void yggdrasil_Display_Clear(u8 paletteIndex) {
		bsp::Display::clear(paletteIndex);
	}

	/**
	 * @brief Draw a rectangle
	 *
	 * @param x1 X Start coordinate
	 * @param y1 Y Start coordinate
	 * @param x2 X End coordinate
	 * @param y2 Y End coordinate
	 * @param colorIndex Index for the color
	 */
	C_LINKAGE void yggdrasil_Display_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex){
		bsp::Display::drawRectangle(x1, y1, x2, y2, colorIndex);
	}

	/**
	 * @brief Draw a filled rectangle
	 *
	 * @param x1 X Start coordinate
	 * @param y1 Y Start coordinate
	 * @param x2 X End coordinate
	 * @param y2 Y End coordinate
	 * @param colorIndex Index for the color
	 */
	C_LINKAGE void yggdrasil_Display_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex){
		bsp::Display::fillRectangle(x1, y1, x2, y2, colorIndex);
	}

	/**
	 * @brief Draw a single pixel
	 *
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param colorIndex Index for the color
	 */
	C_LINKAGE void yggdrasil_Display_DrawPixel(u16 x, u16 y, u8 colorIndex) {
		bsp::Display::drawPixel(x, y, colorIndex);
	}

	/**
	 * @brief Draw a line
	 *
	 * @param x1 X Start coordinate
	 * @param y1 Y Start coordinate
	 * @param x2 X End coordinate
	 * @param y2 Y End coordinate
	 * @param colorIndex Index for the color
		 */
	C_LINKAGE void yggdrasil_Display_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex) {
		bsp::Display::drawLine(x1, y1, x2, y2, colorIndex);
	}

	/**
	 * @brief Draw a cricle
	 *
	 * @param centerX X Position of the center
	 * @param centerY Y Position of the center
	 * @param readius Radius
	 * @param colorIndex Index for the color
	 */
	C_LINKAGE void yggdrasil_Display_DrawCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex) {
		bsp::Display::drawCircle(centerX, centerY, radius, colorIndex);
	}

	/**
	 * @brief Draw a filled cricle
	 *
	 * @param centerX X Position of the center
	 * @param centerY Y Position of the center
	 * @param readius Radius
	 * @param colorIndex Index for the color
	 */
	C_LINKAGE void yggdrasil_Display_FillCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex) {
		bsp::Display::fillCircle(centerX, centerY, radius, colorIndex);
	}

	/**
	 * @brief Draw a single character
	 *
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param c Charachter
	 * @param colorIndex Index for the color
	 * @param font Font
	 */
	C_LINKAGE void yggdrasil_Display_DrawCharacter(u16 x, u16 y, char c, u8 colorIndex, Font *font) {
		bsp::Display::drawCharacter(x, y, c, colorIndex, *font);
	}


	/**
	 * @brief Draw a string
	 *
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param string String view
	 * @param colorIndex Index for the color
	 * @param font Font
	 */
	C_LINKAGE void yggdrasil_Display_DrawString(u16 x, u16 y, const char *string, u8 colorIndex, Font *font) {
		bsp::Display::drawString(x, y, string, colorIndex, *font);
	}


#endif
