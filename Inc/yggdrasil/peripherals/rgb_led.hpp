/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Peripherals -                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/rgb_led.hpp   	            		*
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

#include "../../Core/Inc/main.h"

extern SPI_HandleTypeDef hspi2;



namespace bsp::ygg::prph {


	static inline uint8_t m_LEDs[9][4];

	class RGBLed {
	public:
		RGBLed() = delete;


		/**
		 * @brief Initialization of the SK9822 led
		 *
		 * @return
		 * @note
		 */

		static void enable() {
			RGBA8 color = {0};
			RGB_EN = 1;
			for(u8 i = 1; i <= MAXLED; i++){
				setLED(i, color);
			}
		}

		static void clear() {
			RGBA8 color = {0};
			for(u8 i = 1; i <= MAXLED; i++){
				setLED(i, color);
			}
		}



		static void setLED(uint8_t number, RGBA8 color) {
			if (number > 0 && number <= MAXLED){
				m_LEDs[(number - 1)][0] = (0xE0 | color.a);
				m_LEDs[(number - 1)][1] = color.b;
				m_LEDs[(number - 1)][2] = color.g;
				m_LEDs[(number - 1)][3] = color.r;
			}
		}

		static void setLED(uint8_t *arryOfNumbers, RGBA8 color) {
			for(u8 cnt = 0; cnt < sizeof(arryOfNumbers); cnt++){
				u8 number = arryOfNumbers[cnt];
				if (number > 0 && number <= MAXLED){
					m_LEDs[(number - 1)][0] = (0xE0 | color.a);
					m_LEDs[(number - 1)][1] = color.b;
					m_LEDs[(number - 1)][2] = color.g;
					m_LEDs[(number - 1)][3] = color.r;
				}
			}
		}

		static void setLEDmasked(uint16_t enableMask, RGBA8 color) {
			for(u8 cnt = 0; cnt < MAXLED; cnt++){
				if((enableMask >> cnt ) & 1){
					m_LEDs[cnt][0] = (0xE0 | color.a);
					m_LEDs[cnt][1] = color.b;
					m_LEDs[cnt][2] = color.g;
					m_LEDs[cnt][3] = color.r;
				}
			}
		}
		static void dice(uint8_t number, RGBA8 color) {
			clear();
			switch (number) {
				case 1:	setLEDmasked(0x0010, color); break;
				case 2:	setLEDmasked(0x0044, color); break;
				case 3:	setLEDmasked(0x0111, color); break;
				case 4:	setLEDmasked(0x0145, color); break;
				case 5:	setLEDmasked(0x0155, color); break;
				case 6:	setLEDmasked(0x016D, color); break;

				default: setLEDmasked(0, color); break;

			}
		}




		static void flush(){
			 SPIsendStartFrame();
			 bsp::SPIA::write<u8[9][4]>(m_LEDs);
			 //HAL_SPI_Transmit(&hspi2, *m_LEDs, (MAXLED*4), 50);
			 SPIsendEndFrame();


		 }



	private:

		constexpr static inline u8 MAXLED = 9;



		static inline void SPIsendStartFrame() {
			uint8_t StartFrame[1][4] = { { 0x00, 0x00, 0x00, 0x00 } };
			HAL_SPI_Transmit(&hspi2, *StartFrame, 4, 50);
		}
		static inline void SPIsendEndFrame() {
			uint8_t EndFrame[1][4] = { { 0xFF, 0xFF, 0xFF, 0xFF } };
			HAL_SPI_Transmit(&hspi2, *EndFrame, 4, 50);
		}





	};

}
