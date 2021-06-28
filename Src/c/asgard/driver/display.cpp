 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Asgard -                              *
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
  *  @file c/asgard/driver/display.cpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Display abstraction implementation for Asgard
  */

#include <yggdrasil.h>

#if BOARD == ASGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/asgard/driver/display.h>

	#include <math.h>

	C_LINKAGE bool yggdrasil_Display_Init() {
		return bsp::Display::init();
	}

	bool yggdrasil_Display_Deinit() {
		return bsp::Display::deinit();
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

	C_LINKAGE void * yggdrasil_Display_GetFrameBufferAddress(void) {
		return bsp::Display::getFramebufferAddress();
	}

	C_LINKAGE void yggdrasil_Display_Clear(u16 color) {
		bsp::Display::clear(color);
	}

	C_LINKAGE void yggdrasil_Display_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color){
		bsp::Display::drawRectangle(x1, y1, x2, y2, color);
	}

	C_LINKAGE void yggdrasil_Display_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color){
		bsp::Display::fillRectangle(x1, y1, x2, y2, color);
	}

	C_LINKAGE void yggdrasil_Display_DrawPixel(u16 x, u16 y, u16 color) {
		bsp::Display::drawPixel(x, y, color);
	}

	C_LINKAGE void yggdrasil_Display_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color) {
		bsp::Display::drawLine(x1, y1, x2, y2, color);
	}

	C_LINKAGE void yggdrasil_Display_DrawCircle(i16 centerX, i16 centerY, u16 radius, u16 color) {
		bsp::Display::drawCircle(centerX, centerY, radius, color);
	}

	C_LINKAGE void yggdrasil_Display_FillCircle(i16 centerX, i16 centerY, u16 radius, u16 color) {
		bsp::Display::fillCircle(centerX, centerY, radius, color);
	}

	C_LINKAGE void yggdrasil_Display_DrawCharacter(u16 x, u16 y, char c, u16 color, Font *font) {
		bsp::Display::drawCharacter(x, y, c, color, *font);
	}

	C_LINKAGE void yggdrasil_Display_DrawString(u16 x, u16 y, const char *string, u16 color, Font *font) {
		bsp::Display::drawString(x, y, string, color, *font);
	}


#endif
