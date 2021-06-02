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
  *  @file midgard/driver/display.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Display abstraction implementation for Midgard
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS) && BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/display.h>

	#include <yggdrasil.h>

	#include <math.h>

	C_LINKAGE bool yggdrasil_Display_Init(enum DisplayOrientation orientation) {
		return bsp::Display::init(static_cast<bsp::Display::Impl::Orientation>(orientation));
	}

	C_LINKAGE void yggdrasil_Display_Reset(void) {
		bsp::Display::reset();
	}

	C_LINKAGE void yggdrasil_Display_TurnOn(void) {
		bsp::Display::turnOn();
	}


	C_LINKAGE void yggdrasil_Display_TurnOff(void) {
		bsp::Display::turnOff();
	}

	C_LINKAGE u16  yggdrasil_Display_getWidth(void) {
		return bsp::Display::getWidth();
	}

	C_LINKAGE u16  yggdrasil_Display_getHeight(void) {
		return bsp::Display::getHeight();
	}

	C_LINKAGE void yggdrasil_Display_SetPalette(palette_t *palette) {
		std::array<u32, 256> data;
		std::copy(palette->colors, palette->colors + sizeof(palette->colors), data.begin());
		bsp::Display::setPalette(data);
	}

	C_LINKAGE palette_t yggdrasil_Display_GetDefaultPalette(void) {
		palette_t result;
		auto palette = bsp::Display::getDefaultPalette();
		std::copy(palette.begin(), palette.end(), result.colors);
		return result;
	}

	C_LINKAGE void * yggdrasil_Display_GetFrameBufferAddress(void) {
		return bsp::Display::getFramebufferAddress();
	}

	C_LINKAGE void yggdrasil_Display_Clear(u8 paletteIndex) {
		bsp::Display::clear(paletteIndex);
	}

	C_LINKAGE void yggdrasil_Display_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex){
		bsp::Display::drawRectangle(x1, y1, x2, y2, colorIndex);
	}

	C_LINKAGE void yggdrasil_Display_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex){
		bsp::Display::fillRectangle(x1, y1, x2, y2, colorIndex);
	}

	C_LINKAGE void yggdrasil_Display_DrawPixel(u16 x, u16 y, u8 colorIndex) {
		bsp::Display::drawPixel(x, y, colorIndex);
	}

	C_LINKAGE void yggdrasil_Display_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex) {
		bsp::Display::drawLine(x1, y1, x2, y2, colorIndex);
	}

	C_LINKAGE void yggdrasil_Display_DrawCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex) {
		bsp::Display::drawCircle(centerX, centerY, radius, colorIndex);
	}

	C_LINKAGE void yggdrasil_Display_FillCircle(i16 centerX, i16 centerY, u16 radius, u8 colorIndex) {
		bsp::Display::fillCircle(centerX, centerY, radius, colorIndex);
	}

	C_LINKAGE void yggdrasil_Display_DrawCharacter(u16 x, u16 y, char c, u8 colorIndex, Font *font) {
		bsp::Display::drawCharacter(x, y, c, colorIndex, *font);
	}

	C_LINKAGE void yggdrasil_Display_DrawString(u16 x, u16 y, const char *string, u8 colorIndex, Font *font) {
		bsp::Display::drawString(x, y, string, colorIndex, *font);
	}


#endif
