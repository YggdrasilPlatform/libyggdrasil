/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Peripherals -                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/color_sensor.hpp   	            *
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
			RGB_EN = 1;
		}


		static void setLED(uint8_t number, RGBA8 color) {
			if (number > 0 && number <= MAXLED){
				m_LEDs[(number - 1)][0] = (0xE0 | color.a);
				m_LEDs[(number - 1)][1] = color.b;
				m_LEDs[(number - 1)][2] = color.g;
				m_LEDs[(number - 1)][3] = color.r;
			}
		}




		static void flush(){
			 SPIsendStartFrame();
			 HAL_SPI_Transmit(&hspi2, *m_LEDs, (MAXLED*4), 50);
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
