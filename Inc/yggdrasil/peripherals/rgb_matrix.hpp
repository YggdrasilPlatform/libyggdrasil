/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Peripherals -                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/rgb_matrix.hpp   	            		*
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief API to use the SK9822 RGB Led							*
  *  			                                                    *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#pragma once

#include <common/attributes.hpp>
#include <common/types.hpp>
#include <common/utils.hpp>

#include <array>

namespace bsp::ygg::prph {

	class RGBMatrix {
	private:
		constexpr static inline u8 NumLEDs = 9;

	public:
		RGBMatrix() = delete;


		/**
		 * @brief Initialization of the SK9822 led
		 *
		 * @return
		 * @note
		 */

		static void enable() {
			RGBA8 color = {0};
			RGB_EN = 1;
			for(u8 i = 1; i <= NumLEDs; i++){
				setLed(i, color);
			}
		}

		static void clear() {
			RGBA8 color = {0};
			for(u8 i = 1; i <= NumLEDs; i++){
				setLed(i, color);
			}
		}



		static void setLed(uint8_t index, RGBA8 color) {
			if (index >= 0 && index <= NumLEDs){
				RGBMatrix::s_LEDs[index * 4 + 0] = (0xE0 | color.a);
				RGBMatrix::s_LEDs[index * 4 + 1] = color.b;
				RGBMatrix::s_LEDs[index * 4 + 2] = color.g;
				RGBMatrix::s_LEDs[index * 4 + 3] = color.r;
			}
		}

		static void setLeds(std::array<u8, NumLEDs> leds, RGBA8 color) {
			for(u8 cnt = 0; cnt < leds.size(); cnt++){
				setLed(leds[cnt], color);
			}
		}

		static void setLedMasked(uint16_t enableMask, RGBA8 color) {
			for(u16 index = 0; index < NumLEDs; index++){
				if(((enableMask >> index) & 0b1) == 0b1){
					setLed(index, color);
				} else {
					setLed(index, { 0x0000'0000 });
				}
			}
		}

		static void dice(u8 index, RGBA8 color) {
			clear();

			switch (index) {
				case 1:	setLedMasked(0b000'010'000, color); break;
				case 2:	setLedMasked(0b001'000'100, color); break;
				case 3:	setLedMasked(0b001'010'100, color); break;
				case 4:	setLedMasked(0b101'000'101, color); break;
				case 5:	setLedMasked(0b101'010'101, color); break;
				case 6:	setLedMasked(0b101'101'101, color); break;
			}
		}

		static void flush(){
			 sendStartFrame();
			 bsp::SPIA::write(RGBMatrix::s_LEDs);
			 sendEndFrame();


		 }

	private:
		static inline std::array<u8, NumLEDs * 4> s_LEDs;

		static inline void sendStartFrame() {
			bsp::SPIA::write<std::array<u8, 4>>({ 0x00, 0x00, 0x00, 0x00 });
		}
		static inline void sendEndFrame() {
			bsp::SPIA::write<std::array<u8, 4>>({ 0xFF, 0xFF, 0xFF, 0xFF });
		}





	};

}
