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
  *  @file cpp/asgard/driver/display.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Display abstraction implementation for Asgard
  */

#pragma once

#include <cpp/common/frontend/display.hpp>

#include <cmath>

#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

namespace bsp::drv {

	enum class Color : u16 {
		Black 	= 0b00000'000000'00000,
		Navy 	= 0b00000'000000'10000,
		Blue	= 0b00000'000000'11000,
		Green	= 0b00000'011000'00000,
		Teal	= 0b00000'010000'01000,
		Lime	= 0b00000'111000'00000,
		Aqua	= 0b00000'111000'11000,
		Maroon	= 0b01100'000000'00000,
		Purple	= 0b01100'000000'11000,
		Olive	= 0b01100'011000'00000,
		Gray	= 0b01000'010000'01000,
		Red		= 0b11100'000000'00000,
		Fuchsia	= 0b11100'000000'11000,
		Yellow	= 0b11100'111000'00000,
		Orange	= 0b11100'100000'00000,
		White	= 0b11100'111000'11000,
	};

}

namespace bsp::asg::drv {

	template<auto Context>
	struct Display {
		Display(const Display&) = delete;

		/*
		 * @brief Display initialization
		 *
		 * @param orientation Display orientation
		 * @return True when successful, false when not
		 */
		static bool init() noexcept {
			int fd = open("/dev/fb0", O_RDWR);
			if (fd == -1) return false;
			
			ON_SCOPE_EXIT { close(fd); };

			if (ioctl(fd, FBIOGET_FSCREENINFO, &Display::s_finfo) == -1) return false;

			if (ioctl(fd, FBIOGET_VSCREENINFO, &Display::s_vinfo) == -1) return false;

			Display::s_xSize = Display::s_vinfo.xres;
			Display::s_ySize = Display::s_vinfo.yres;
			Display::s_bpp   = Display::s_vinfo.bits_per_pixel;

			Display::s_framebufferAddress = (u32)mmap(nullptr, Display::s_finfo.line_length * Display::s_vinfo.yres, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
			if (Display::s_framebufferAddress == 0xFFFF'FFFF) return false;

			Display::clear(bsp::drv::Color::Black);
			Display::turnOn();

			return true;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return True when successfully stopped, false when not
		 */
		static bool deinit() {
			munmap(getFramebufferAddress(), Display::s_xSize * Display::s_ySize * Display::s_bpp / 8);
			return true;
		}

		/*
		 * @brief Display reset
		 */
		static void reset() noexcept {

		}

		/*
		 * @brief Enable the display
		 */
		static void turnOn() noexcept {

		}

		/*
		 * @brief Disable the display
		 */
		static void turnOff() noexcept {

		}

		/*
		 * @brief Get the display width
		 *
		 * @return display width
		 */
		static inline u16 getWidth() {
			return Display::s_xSize;
		}

		/*
		 * @brief Get the display height
		 *
		 * @return display height
		 */
		static inline u16 getHeight() {
			return Display::s_ySize;
		}

		/*
		 * @brief Set the color palette
		 *
		 * @param palettet Color palette
		 */
		static inline void setPalette(const std::array<u32, 256> &palette) {

		}

		/*
		 * @brief Get the default color palette
		 *
		 * @return Default color palette
		 */
		static std::array<u32, 256> getDefaultPalette() {
			return { };
		}

		/*
		 * @brief Get the framebuffer address
		 *
		 * @return framebuffer address
		 */
		ALWAYS_INLINE static void* getFramebufferAddress() {
			return reinterpret_cast<void*>(Display::s_framebufferAddress);
		}

		/*
		 * @brief Set a Pixel
		 *
		 * @param x X coordinate
		 * @param y Y coordinate
		 * @param paletteIndex Index for the color
		 */
		ALWAYS_INLINE static void setPixel(u16 x, u16 y, u32 color) {
			u32 offset = (x + Display::s_vinfo.xoffset) * (Display::s_bpp / 8) + (y + Display::s_vinfo.yoffset) * Display::s_finfo.line_length;

			std::memcpy(reinterpret_cast<u8*>(getFramebufferAddress()) + offset, &color, Display::s_bpp / 8);		
		}


		/**
		 * @brief Clear the display to a color
		 *
		 * @param paletteIndex Index for the color
		 */
		ALWAYS_INLINE static void clear(auto color) {
			for (u32 x = 0; x < Display::s_xSize; x++)
				for (u32 y = 0; y < Display::s_ySize; y++) 
					Display::setPixel(x, y, static_cast<u32>(color));
		}

	private:
		Display() = default;

		static inline u32 s_framebufferAddress;

		static inline u16 s_xSize, s_ySize;
		static inline u8 s_bpp;

		static inline fb_fix_screeninfo s_finfo;
		static inline fb_var_screeninfo s_vinfo;

		/**
		 * @brief Declare Display frontend as friend
		 */
		template<auto, template<auto> typename>
		friend struct bsp::drv::Display;
	};

}
