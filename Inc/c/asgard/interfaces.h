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

#include <c/asgard/core/cortex.h>

#include <c/asgard/driver/gpio.h>
#include <c/asgard/driver/i2c.h>
#include <c/asgard/driver/display.h>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	const static gpio_t LeftJoyStickButton = { 73, LOW_ACTIVE };
	const static gpio_t RightJoyStickButton = { 71, LOW_ACTIVE };

	const static gpio_t LD1 = { 144 };
	const static gpio_t LDA = LD1;
	const static gpio_t LedBlue = LD1;
	const static gpio_t LD2 = { 145 };
	const static gpio_t LDB = LD2;
	const static gpio_t LedRed = LD2;
	const static gpio_t LD3 = { 146 };
	const static gpio_t LDC = LD3;
	const static gpio_t LedYellow = LD3;
	const static gpio_t LD4 = { 147 };
	const static gpio_t LDD = LD4;
	const static gpio_t LedGreen = LD4;

	const static gpio_t ButtonA = { 148, LOW_ACTIVE };
	const static gpio_t ButtonB = { 149, LOW_ACTIVE };
	const static gpio_t ButtonC = { 150, LOW_ACTIVE };
	const static gpio_t ButtonD = { 151, LOW_ACTIVE };

	const static gpio_t DriverA = { 19 };
	const static gpio_t LD5 = DriverA;
	const static gpio_t LDE = DriverA;
	const static gpio_t DriverB = { 20 };
	const static gpio_t LD6 = DriverB;
	const static gpio_t LDF = DriverB;
	const static gpio_t DriverC = { 30 };
	const static gpio_t LD7 = DriverC;
	const static gpio_t LDG = DriverC;
	const static gpio_t DriverD = { 31 };
	const static gpio_t LD8 = DriverD;
	const static gpio_t LDH = DriverD;

	const static gpio_t SevenSegment_A  = { 160 };
	const static gpio_t SevenSegment_B  = { 161 };
	const static gpio_t SevenSegment_C  = { 162 };
	const static gpio_t SevenSegment_D  = { 163 };
	const static gpio_t SevenSegment_E  = { 164 };
	const static gpio_t SevenSegment_F  = { 165 };
	const static gpio_t SevenSegment_G  = { 166 };
	const static gpio_t SevenSegment_DP = { 167 };

	const static gpio_t SevenSegment_Select0 = { 140 };
	const static gpio_t SevenSegment_Select1 = { 141 };
	const static gpio_t SevenSegment_Select2 = { 142 };
	const static gpio_t SevenSegment_Select3 = { 143 };


	const static gpio_t SK9822_EN = { 74 };
	const static gpio_t SPIACE = { 128 };

	const static gpio_t TC78Mode = { 83 };
	const static gpio_t TC78Err  = { 105 };
	const static gpio_t TC78Stby = { 138 };

	const static i2c_t I2CA = { 1 };
	const static i2c_t I2CB = { 3 };
	const static i2c_t I2CC = { 4 };
	const static i2c_t I2CD = { 0 };

	const static gpio_t EncoderButton  = { 65, LOW_ACTIVE };

	#endif
