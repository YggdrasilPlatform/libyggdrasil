 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
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
  *  @file cpp/common/frontend/display.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the Display abstraction
  */

#pragma once

#include <cpp/common/registers.hpp>
#include <cpp/common/attributes.hpp>
#include <cpp/common/math.hpp>

#include <c/resources/fonts/fonts.h>

namespace bsp::drv {

	using Palette = std::array<u32, 256>;

	/**
	 * @brief Base class for Display abstraction
	 *
	 * @tparam Context Display context
	 * @tparam DisplayImpl Display implementation
	 */
	template<auto Context, template<auto> typename DisplayImpl>
	struct Display {
		Display() = delete;
		Display(const Display&) = delete;
		Display(Display &&) = delete;

		using Impl = DisplayImpl<Context>;

		/*
		 * @brief Display initialization
		 *
		 * @param orientation Display orientation
		 * @return Success
		 */
		static auto init(auto ... args) {
			return Impl::init(args...);
		}

		/**
		 * @brief Deinit function
		 *
		 * @return Success
		 */
		static auto deinit(auto ... args) {
			return Impl::deinit(args...);
		}

		/*
		 * @brief Display reset
		 */
		static void reset() {
			Impl::reset();
		}

		/*
		 * @brief Get the display width
		 *
		 * @return display width
		 */
		static auto getWidth() {
			return Impl::getWidth();
		}

		/*
		 * @brief Get the display height
		 *
		 * @return display height
		 */
		static auto getHeight() {
			return Impl::getHeight();
		}

		/*
		 * @brief Get the default color palette
		 *
		 * @return Default color palette
		 */
		static Palette getDefaultPalette() {
			return Impl::getDefaultPalette();
		}

		/*
		 * @brief Get the framebuffer address
		 *
		 * @return framebuffer address
		 */
		static void* getFramebufferAddress() {
			return Impl::getFramebufferAddress();
		}

		/*
		 * @brief Set the color palette
		 *
		 * @param palettet Color palette
		 */
		static void setPalette(const Palette &palette) {
			Impl::setPalette(palette);
		}

		/*
		 * @brief Enable the display
		 */
		static void turnOn() {
			Impl::turnOn();
		}

		/*
		 * @brief Disable the display
		 */
		static void turnOff() {
			Impl::turnOff();
		}

		/**
		 * @brief Clear the display to a color
		 *
		 * @param colorIndex Index for the color
		 */
		static void clear(auto colorIndex) {
			Impl::clear(static_cast<u8>(colorIndex));
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
		static void drawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, auto colorIndex) {
			x1 = math::clamp<u16>(x1, 0, Display::getWidth() - 1);
			y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
			x2 = math::clamp<u16>(x2, 0, Display::getWidth() - 1);
			y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);

			for (u16 x = x1; x < x2; x++)
				Display::drawPixel(x, y1, colorIndex);
			for (u16 x = x1; x < x2; x++)
				Display::drawPixel(x, y2, colorIndex);
			for (u16 y = y1; y < y2; y++)
				Display::drawPixel(x1, y, colorIndex);
			for (u16 y = y1; y < y2; y++)
				Display::drawPixel(x2, y, colorIndex);
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
		static void fillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, auto colorIndex) {
			x1 = math::clamp<u16>(x1, 0, Display::getWidth() - 1);
			y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
			x2 = math::clamp<u16>(x2, 0, Display::getWidth() - 1);
			y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);

			for (u16 x = x1; x < x2; x++)
				for (u16 y = y1; y < y2; y++)
					Display::drawPixel(x, y, colorIndex);
		}


		/**
		 * @brief Draw a single pixel
		 *
		 * @param x X coordinate
		 * @param y Y coordinate
		 * @param colorIndex Index for the color
		 */
		static void drawPixel(u16 x, u16 y, auto colorIndex) {
			u8 colorValue = static_cast<u8>(colorIndex);
			Impl::setPixel(x, y, colorValue);
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
		static void drawLine(u16 x1, u16 y1, u16 x2, u16 y2, auto colorIndex) {
			x1 = math::clamp<u16>(x1, 0, Display::getWidth() - 1);
			y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
			x2 = math::clamp<u16>(x2, 0, Display::getWidth() - 1);
			y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);

			i16 deltaX =  std::abs(x2 - x1);
			i16 deltaY = -std::abs(y2 - y1);
			i16 speedX = x1 < x2 ? 1 : -1;
			i16 speedY = y1 < y2 ? 1 : -1;

			i16 error = deltaX + deltaY;

			/* Bresenham */
			while (!(x1 == x2 && y1 == y2)) {
				Display::drawPixel(x1, y1, colorIndex);

				if ((error * 2) > deltaY) {
					error += deltaY;
					x1 += speedX;
				}
				if ((error * 2) < deltaX) {
					error += deltaX;
					y1 += speedY;
				}
			}
		}

		/**
		 * @brief Draw a cricle
		 *
		 * @param centerX X Position of the center
		 * @param centerY Y Position of the center
		 * @param readius Radius
		 * @param colorIndex Index for the color
		 */
		static void drawCircle(i16 centerX, i16 centerY, u16 radius, auto colorIndex) {
			auto setPixels = [](i16 centerX, i16 centerY, i16  x, i16 y, u8 colorIndex) {
				Display::drawPixel(centerX+x, centerY+y, colorIndex);
				Display::drawPixel(centerX-x, centerY+y, colorIndex);
				Display::drawPixel(centerX+x, centerY-y, colorIndex);
				Display::drawPixel(centerX-x, centerY-y, colorIndex);
				Display::drawPixel(centerX+y, centerY+x, colorIndex);
				Display::drawPixel(centerX-y, centerY+x, colorIndex);
				Display::drawPixel(centerX+y, centerY-x, colorIndex);
			    Display::drawPixel(centerX-y, centerY-x, colorIndex);
			};

		    i16 x = 0, y = radius;
		    i16 d = 3 - 2 * radius;
		    setPixels(centerX, centerY, x, y, colorIndex);

		    /* Bresenham */
		    while (y >= x) {
		        x++;

		        if (d > 0) {
		            y--;
		            d = d + 4 * (x - y) + 10;
		        } else {
		            d = d + 4 * x + 6;
		        }

		        setPixels(centerX, centerY, x, y, colorIndex);
		    }
		}

		/**
		 * @brief Draw a filled cricle
		 *
		 * @param centerX X Position of the center
		 * @param centerY Y Position of the center
		 * @param readius Radius
		 * @param colorIndex Index for the color
		 */
		static void fillCircle(i16 centerX, i16 centerY, u16 radius, auto colorIndex) {
			i16 x = radius;
			i16 y = 0;
			i16 radiusError = 0;
			i16 xChange = 1 - (radius << 1);
			i16 yChange = 0;

			/* Bresenham */
			while (x >= y) {
				for (i16 i = centerX - x; i <= centerX + x; i++) {
					i16 y1 = centerY + y;
					i16 y2 = centerY - y;
					i16 x1 = i;

					y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
					y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);
					x1 = math::clamp<u16>(x1, 0, Display::getWidth() -1 );

					Display::drawPixel(x1, y1, colorIndex);
					Display::drawPixel(x1, y2, colorIndex);

				}

				for (i16 i = centerX - y; i <= centerX + y; i++) {
					i16 y1 = centerY + x;
					i16 y2 = centerY - x;
					i16 x1 = i;

					y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
					y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);
					x1 = math::clamp<u16>(x1, 0, Display::getWidth() -1 );

					Display::drawPixel(x1, y1, colorIndex);
					Display::drawPixel(x1, y2, colorIndex);
				}

				y++;
				radiusError += yChange;
				yChange += 2;
				if (((radiusError << 1) + xChange) > 0) {
					x--;
					radiusError += xChange;
					xChange += 2;
				}
			}
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
		static void drawCharacter(u16 x, u16 y, char c, auto colorIndex, Font &font) {
			x = math::clamp<u16>(x, 0, Display::getWidth() - 1);
			y = math::clamp<u16>(y, 0, Display::getHeight() - 1);

			u16 width = font.Width;
			u16 height = font.Height;

		const u8 *dataStart = &font.table[(c - ' ') * height * ((width + 7) / 8)];

			u8 offset = 8 * ((width + 7) / 8) - width;

			u32 line = 0;

			/* Bresenham */
			for (u32 i = 0; i < height; i++) {
				const u8 *data = (dataStart + (width + 7) / 8 * i);

				switch ((width + 7) / 8) {
				case 1:
					line = data[0];
					break;
				case 2:
					line = data[0] << 8 | data[1];
					break;
				case 3:
				default:
					line = data[0] << 16 | data[1] << 8 | data[0];
					break;
				}

				for (u16 bit = 0; bit < width; bit++) {
					if (line & (1 << (width - bit + offset - 1)))
						Display::drawPixel(x + bit, y, colorIndex);
				}

				y++;
			}
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
		static void drawString(u16 x, u16 y, std::string_view string, auto colorIndex, Font& font) {
			for (char c : string) {
				Display::drawCharacter(x, y, c, colorIndex, font);
				x += font.Width;
			}
		}
	};

}
