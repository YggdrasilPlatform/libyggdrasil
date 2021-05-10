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
  *  @file common/driver/display.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Frontend for the Display abstraction
  */

#pragma once

#include <common/registers.hpp>
#include <common/attributes.hpp>
#include <common/math.hpp>

#include <common/resources/fonts/fonts.h>

namespace bsp::drv {

	/**
	 * @brief Base class for DAC abstraction
	 *
	 * @tparam Context DAC context
	 * @tparam DACChannelImpl DACChannel implementation
	 */
	template<auto Context, template<auto> typename DisplayImpl>
	struct Display {
		Display() = delete;
		Display(const Display&) = delete;
		Display(Display &&) = delete;

		using Impl = DisplayImpl<Context>;

		static void init() {
			Impl::init();
		}

		static void reset() {
			Impl::reset();
		}

		static auto getWidth() {
			return Impl::getWidth();
		}

		static auto getHeight() {
			return Impl::getHeight();
		}

		static void turnOn() {
			Impl::turnOn();
		}

		static void turnOff() {
			Impl::turnOff();
		}

		static void clear(u8 colorIndex) {
			Impl::clear(colorIndex);
		}

		static void drawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex) {
			x1 = math::clamp<u16>(x1, 0, Display::getWidth() - 1);
			y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
			x2 = math::clamp<u16>(x2, 0, Display::getWidth() - 1);
			y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);

			for (u16 x = x1; x < x2; x++)
				Impl::setPixel(x, y1, colorIndex);
			for (u16 x = x1; x < x2; x++)
				Impl::setPixel(x, y2, colorIndex);
			for (u16 y = y1; y < y2; y++)
				Impl::setPixel(x1, y, colorIndex);
			for (u16 y = y1; y < y2; y++)
				Impl::setPixel(x2, y, colorIndex);
		}

		static void fillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex) {
			x1 = math::clamp<u16>(x1, 0, Display::getWidth() - 1);
			y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
			x2 = math::clamp<u16>(x2, 0, Display::getWidth() - 1);
			y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);

			for (u16 x = x1; x < x2; x++)
				for (u16 y = y1; y < y2; y++)
					Impl::setPixel(x, y, colorIndex);
		}

		static void drawPixel(u16 x, u16 y, u8 colorIndex) {
			Impl::setPixel(x, y, colorIndex);
		}

		static void drawLine(u16 x1, u16 y1, u16 x2, u16 y2, u8 colorIndex) {
			x1 = math::clamp<u16>(x1, 0, Display::getWidth() - 1);
			y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
			x2 = math::clamp<u16>(x2, 0, Display::getWidth() - 1);
			y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);

			i16 deltaX =  std::abs(x2 - x1);
			i16 deltaY = -std::abs(y2 - y1);
			i16 speedX = x1 < x2 ? 1 : -1;
			i16 speedY = y1 < y2 ? 1 : -1;

			i16 error = deltaX + deltaY;

			while (!(x1 == x2 && y1 == y2)) {
				Impl::setPixel(x1, y1, colorIndex);

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

		static void drawCircle(i16 centerX, i16 centerY, i16 radius, u8 colorIndex) {
			auto setPixels = [](i16 centerX, i16 centerY, i16  x, i16 y, u8 colorIndex) {
				Impl::setPixel(centerX+x, centerY+y, colorIndex);
				Impl::setPixel(centerX-x, centerY+y, colorIndex);
				Impl::setPixel(centerX+x, centerY-y, colorIndex);
				Impl::setPixel(centerX-x, centerY-y, colorIndex);
				Impl::setPixel(centerX+y, centerY+x, colorIndex);
				Impl::setPixel(centerX-y, centerY+x, colorIndex);
				Impl::setPixel(centerX+y, centerY-x, colorIndex);
			    Impl::setPixel(centerX-y, centerY-x, colorIndex);
			};

		    i16 x = 0, y = radius;
		    i16 d = 3 - 2 * radius;
		    setPixels(centerX, centerY, x, y, colorIndex);
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

		static void fillCircle(u16 centerX, u16 centerY, u16 radius, u8 colorIndex) {
			i16 x = radius;
			i16 y = 0;
			i16 radiusError = 0;
			i16 xChange = 1 - (radius << 1);
			i16 yChange = 0;

			while (x >= y) {
				for (i16 i = centerX - x; i <= centerX + x; i++) {
					i16 y1 = centerY + y;
					i16 y2 = centerY - y;
					i16 x1 = i;

					y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
					y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);
					x1 = math::clamp<u16>(x1, 0, Display::getWidth() -1 );

					Impl::setPixel(x1, y1, colorIndex);
					Impl::setPixel(x1, y2, colorIndex);

				}

				for (i16 i = centerX - y; i <= centerX + y; i++) {
					i16 y1 = centerY + x;
					i16 y2 = centerY - x;
					i16 x1 = i;

					y1 = math::clamp<u16>(y1, 0, Display::getHeight() - 1);
					y2 = math::clamp<u16>(y2, 0, Display::getHeight() - 1);
					x1 = math::clamp<u16>(x1, 0, Display::getWidth() -1 );

					Impl::setPixel(x1, y1, colorIndex);
					Impl::setPixel(x1, y2, colorIndex);
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

		static void drawCharacter(u16 x, u16 y, char c, u8 colorIndex, Font &font) {
			x = math::clamp<u16>(x, 0, Display::getWidth() - 1);
			y = math::clamp<u16>(y, 0, Display::getHeight() - 1);

			u16 width = font.Width;
			u16 height = font.Height;

		const u8 *dataStart = &font.table[(c - ' ') * height * ((width + 7) / 8)];

			u8 offset = 8 * ((width + 7) / 8) - width;

			u32 line = 0;
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

		static void drawString(u16 x, u16 y, std::string_view string, u8 colorIndex, Font& font) {
			for (char c : string) {
				Display::drawCharacter(x, y, c, colorIndex, font);
				x += font.Width;
			}
		}
	};

}
