 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
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
  *  @file cpp/midgard/interfaces.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Interface definitions for Midgard
  */

#pragma once

#include <stm32f7xx_hal.h>

#include <c/midgard/core/cortex.h>

#include <c/midgard/driver/gpio.h>
#include <c/midgard/driver/adc.h>
#include <c/midgard/driver/dac.h>
#include <c/midgard/driver/can.h>
#include <c/midgard/driver/spi.h>
#include <c/midgard/driver/i2c.h>
#include <c/midgard/driver/timer.h>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	extern I2C_HandleTypeDef hi2c1;
	extern I2C_HandleTypeDef hi2c2;
	extern I2C_HandleTypeDef hi2c3;
	extern I2C_HandleTypeDef hi2c4;

	extern SPI_HandleTypeDef hspi2;
	extern SPI_HandleTypeDef hspi4;
	extern SPI_HandleTypeDef hspi5;

	extern TIM_HandleTypeDef htim2;
	extern TIM_HandleTypeDef htim3;
	extern TIM_HandleTypeDef htim4;
	extern TIM_HandleTypeDef htim5;
	extern TIM_HandleTypeDef htim8;
	extern TIM_HandleTypeDef htim11;
	extern TIM_HandleTypeDef htim12;

	extern ADC_HandleTypeDef hadc1;
	extern ADC_HandleTypeDef hadc2;
	extern ADC_HandleTypeDef hadc3;

	extern DAC_HandleTypeDef hdac;

	extern LTDC_HandleTypeDef  hltdc;
	extern DSI_HandleTypeDef   hdsi;
	extern DMA2D_HandleTypeDef hdma2d;

	extern CAN_HandleTypeDef hcan1;
	extern CAN_HandleTypeDef hcan2;



	const static gpio_t LeftJoyStickButton = { GPIOG, 10, LOW_ACTIVE };
	const static gpio_t RightJoyStickButton = { GPIOG, 11, LOW_ACTIVE };

	const static gpio_t LD1 = { GPIOJ, 0 };
	const static gpio_t LDA = LD1;
	const static gpio_t LedBlue = LD1;
	const static gpio_t LD2 = { GPIOJ, 1 };
	const static gpio_t LDB = LD2;
	const static gpio_t LedRed = LD2;
	const static gpio_t LD3 = { GPIOJ, 2 };
	const static gpio_t LDC = LD3;
	const static gpio_t LedYellow = LD3;
	const static gpio_t LD4 = { GPIOJ, 3 };
	const static gpio_t LDD = LD4;
	const static gpio_t LedGreen = LD4;

	const static gpio_t EncoderButton = { GPIOK, 3, LOW_ACTIVE };
	const static gpio_t ButtonA = { GPIOK, 4, LOW_ACTIVE };
	const static gpio_t ButtonB = { GPIOK, 5, LOW_ACTIVE };
	const static gpio_t ButtonC = { GPIOK, 6, LOW_ACTIVE };
	const static gpio_t ButtonD = { GPIOK, 7, LOW_ACTIVE };

	const static gpio_t DriverA = { GPIOC, 13 };
	const static gpio_t LD5 = DriverA;
	const static gpio_t LDE = DriverA;
	const static gpio_t DriverB = { GPIOI, 8 };
	const static gpio_t LD6 = DriverB;
	const static gpio_t LDF = DriverB;
	const static gpio_t DriverC = { GPIOB, 0 };
	const static gpio_t LD7 = DriverC;
	const static gpio_t LDG = DriverC;
	const static gpio_t DriverD = { GPIOB, 1 };
	const static gpio_t LD8 = DriverD;
	const static gpio_t LDH = DriverD;

	const static adc_t ADCA = { &hadc1, 3,  0, 1 << 12 };
	const static adc_t ADCB = { &hadc1, 10, 0, 1 << 12 };
	const static adc_t ADCC = { &hadc3, 14, 0, 1 << 12 };
	const static adc_t ADCD = { &hadc3, 15, 0, 1 << 12 };
	const static adc_t ADCPotentiometer = { &hadc2, 13, 0, 1 << 12 };
	const static adc_t ADCTemperature = { &hadc1, 18, 0, 1 << 12 };

	const static dac_t  DACA = { &hdac, 1, 0, 1 << 12 };
	const static dac_t  DACB = { &hdac, 2, 0, 1 << 12 };

	const static gpio_t SevenSegment_A  = { GPIOG, 0 };
	const static gpio_t SevenSegment_B  = { GPIOG, 1 };
	const static gpio_t SevenSegment_C  = { GPIOG, 2 };
	const static gpio_t SevenSegment_D  = { GPIOG, 3 };
	const static gpio_t SevenSegment_E  = { GPIOG, 4 };
	const static gpio_t SevenSegment_F  = { GPIOG, 5 };
	const static gpio_t SevenSegment_G  = { GPIOG, 6 };
	const static gpio_t SevenSegment_DP = { GPIOG, 7 };

	const static gpio_t SevenSegment_Select0 = { GPIOJ, 12 };
	const static gpio_t SevenSegment_Select1 = { GPIOJ, 13 };
	const static gpio_t SevenSegment_Select2 = { GPIOJ, 14 };
	const static gpio_t SevenSegment_Select3 = { GPIOJ, 15 };


	const static gpio_t RGB_EN = { GPIOD, 9 };


	const static gpio_t SPIACE = { GPIOI, 0, LOW_ACTIVE };


	const static gpio_t TC78Mode = { GPIOI, 12 };
	const static gpio_t TC78Err  = { GPIOI, 13, LOW_ACTIVE };
	const static gpio_t TC78Stby = { GPIOI, 14, LOW_ACTIVE };

	const static can_t CANA = { &hcan1 };
	const static can_t CANB = { &hcan2 };

	#endif
