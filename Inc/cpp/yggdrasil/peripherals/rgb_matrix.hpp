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
  *  @file cpp/yggdrasil/peripherals/rgb_matrix.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the SK9822 RGB Led (APA102 clone)
  */

#pragma once

#include <cpp/common/attributes.hpp>
#include <cpp/common/types.hpp>
#include <cpp/common/utils.hpp>

#include <array>

namespace bsp::ygg::prph {

	/**
	 * @brief RGB Led driver SK9822 through SPI
	 * @note Use flush() to write the leds
	 */
	class RGBMatrix {
	private:
		constexpr static inline u8 NumLEDs = 9;		///< Number of led on the board

	public:
		RGBMatrix() = delete;


		/**
		 * @brief Initialization of the SK9822 led
		 */
		static void enable() {
			RGBA8 color = {0};
			bsp::SPIA::setMode(bsp::drv::SPIMode::_3);
			RGB_EN = 1;
			for(u8 i = 1; i <= NumLEDs; i++){
				setLed(i, color);
			}
		}

		/**
		 * @brief Disable the SK9822 led
		 */
		static void disable() {
			RGB_EN = 0;
		}

		/**
		 * @brief Clear all leds
		 */
		static void clear() {
			RGBA8 color = {0};
			for(u8 i = 1; i <= NumLEDs; i++){
				setLed(i, color);
			}
		}


		/**
		 * @brief set a single led to RGBA8 color
		 *
		 * @param index Led number from 0 to 8
		 * @param color RGBA8 color
		 */
		static void setLed(u8 index, RGBA8 color) {
			if (index >= 0 && index <= NumLEDs){
				RGBMatrix::s_LEDs[index * 4 + 0] = (0xE0 | color.a);
				RGBMatrix::s_LEDs[index * 4 + 1] = color.b;
				RGBMatrix::s_LEDs[index * 4 + 2] = color.g;
				RGBMatrix::s_LEDs[index * 4 + 3] = color.r;
			}
		}

		/**
		 * @brief set multiple leds to RGBA8 color using an array with the led number
		 *
		 * @param led Array of index numbers
		 * @param color RGBA8 color
		 */
		static void setLeds(std::array<u8, NumLEDs> leds, RGBA8 color) {
			for(u8 cnt = 0; cnt < leds.size(); cnt++){
				setLed(leds[cnt], color);
			}
		}

		/**
		 * @brief set multiple leds to RGBA8 color using a bit mask
		 *
		 * @param enableMask Bitmask to enabled the leds
		 * @param color RGBA8 color
		 */
		static void setLedMasked(u16 enableMask, RGBA8 color) {
			for(u16 index = 0; index < NumLEDs; index++){
				if(((enableMask >> index) & 0b1) == 0b1){
					setLed(index, color);
				} else {
					setLed(index, { 0x0000'0000 });
				}
			}
		}

		/**
		 * @brief Function to display a dice
		 *
		 * @param number Number to display
		 * @param color RGBA8 color
		 */
		static void dice(u8 number, RGBA8 color) {
			clear();

			switch (number) {
				case 1:	setLedMasked(0b000'010'000, color); break;
				case 2:	setLedMasked(0b001'000'100, color); break;
				case 3:	setLedMasked(0b001'010'100, color); break;
				case 4:	setLedMasked(0b101'000'101, color); break;
				case 5:	setLedMasked(0b101'010'101, color); break;
				case 6:	setLedMasked(0b101'101'101, color); break;
			}
		}

		/**
		 * @brief Sends the saved color values to the leds
		 */
		static void flush(){
			 sendStartFrame();
			 bsp::SPIA::write(RGBMatrix::s_LEDs);
			 sendEndFrame();
		 }

	private:
		static inline std::array<u8, NumLEDs * 4> s_LEDs;

		/**
		 * @brief Start frame for the SK9822 leds
		 */
		static inline void sendStartFrame() {
			bsp::SPIA::write<std::array<u8, 4>>({ 0x00, 0x00, 0x00, 0x00 });
		}

		/**
		 * @brief End frame for the SK9822 leds
		 */
		static inline void sendEndFrame() {
			bsp::SPIA::write<std::array<u8, 4>>({ 0xFF, 0xFF, 0xFF, 0xFF });
		}

	};

}
