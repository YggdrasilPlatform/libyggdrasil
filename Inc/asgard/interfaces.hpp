/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file midgard/midgard.hpp                                      *
  *  @ingroup midgard                                               *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Top-level include file for Asgard					    *
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

#include <stm32mp1xx_hal.h>

#include <asgard/driver/gpio.hpp>
/*#include <asgard/driver/adc.hpp>
#include <asgard/driver/uart.hpp>*/
#include <asgard/driver/i2c.hpp>

#include <asgard/core/cache.hpp>
#include <asgard/core/cortex.hpp>
#include <asgard/core/instructions.hpp>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	extern "C" I2C_HandleTypeDef hi2c1;
	extern "C" I2C_HandleTypeDef hi2c2;
	extern "C" I2C_HandleTypeDef hi2c5;

	namespace bsp {

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using GPIOPortA = bsp::drv::GPIOPort<0x5000'2000, bsp::asg::drv::GPIOPort>;
		using GPIOPortB = bsp::drv::GPIOPort<0x5000'3000, bsp::asg::drv::GPIOPort>;
		using GPIOPortC = bsp::drv::GPIOPort<0x5000'4000, bsp::asg::drv::GPIOPort>;
		using GPIOPortD = bsp::drv::GPIOPort<0x5000'5000, bsp::asg::drv::GPIOPort>;
		using GPIOPortE = bsp::drv::GPIOPort<0x5000'6000, bsp::asg::drv::GPIOPort>;
		using GPIOPortF = bsp::drv::GPIOPort<0x5000'7000, bsp::asg::drv::GPIOPort>;
		using GPIOPortG = bsp::drv::GPIOPort<0x5000'8000, bsp::asg::drv::GPIOPort>;
		using GPIOPortH = bsp::drv::GPIOPort<0x5000'9000, bsp::asg::drv::GPIOPort>;
		using GPIOPortI = bsp::drv::GPIOPort<0x5000'A000, bsp::asg::drv::GPIOPort>;
		using GPIOPortJ = bsp::drv::GPIOPort<0x5000'B000, bsp::asg::drv::GPIOPort>;
		using GPIOPortK = bsp::drv::GPIOPort<0x5000'C000, bsp::asg::drv::GPIOPort>;
		using GPIOPortZ = bsp::drv::GPIOPort<0x5400'4000, bsp::asg::drv::GPIOPort>;

		/** @} */

		static constexpr auto& LeftJoyStickButton = GPIOPortE::Pin<9>;
		static constexpr auto& RightJoyStickButton = GPIOPortE::Pin<7>;

		static constexpr auto& LD1 = GPIOPortJ::Pin<0>;
		static constexpr auto& LDA = LD1;
		static constexpr auto& LedBlue = LD1;
		static constexpr auto& LD2 = GPIOPortJ::Pin<1>;
		static constexpr auto& LDB = LD2;
		static constexpr auto& LedRed = LD2;
		static constexpr auto& LD3 = GPIOPortJ::Pin<2>;
		static constexpr auto& LDC = LD3;
		static constexpr auto& LedYellow = LD3;
		static constexpr auto& LD4 = GPIOPortJ::Pin<3>;
		static constexpr auto& LDD = LD4;
		static constexpr auto& LedGreen = LD4;

		static constexpr auto& ButtonA = GPIOPortJ::Pin<4>;
		static constexpr auto& ButtonB = GPIOPortJ::Pin<5>;
		static constexpr auto& ButtonC = GPIOPortJ::Pin<6>;
		static constexpr auto& ButtonD = GPIOPortJ::Pin<7>;

		static constexpr auto& DriverA = GPIOPortB::Pin<3>;
		static constexpr auto& LD5 = DriverA;
		static constexpr auto& LDE = DriverA;
		static constexpr auto& DriverB = GPIOPortB::Pin<4>;
		static constexpr auto& LD6 = DriverB;
		static constexpr auto& LDF = DriverB;
		static constexpr auto& DriverC = GPIOPortB::Pin<14>;
		static constexpr auto& LD7 = DriverC;
		static constexpr auto& LDG = DriverC;
		static constexpr auto& DriverD = GPIOPortB::Pin<15>;
		static constexpr auto& LD8 = DriverD;
		static constexpr auto& LDH = DriverD;

		namespace seven_segment {
			static constexpr auto& A = GPIOPortK::Pin<0>;
			static constexpr auto& B = GPIOPortK::Pin<1>;
			static constexpr auto& C = GPIOPortK::Pin<2>;
			static constexpr auto& D = GPIOPortK::Pin<3>;
			static constexpr auto& E = GPIOPortK::Pin<4>;
			static constexpr auto& F = GPIOPortK::Pin<5>;
			static constexpr auto& G = GPIOPortK::Pin<6>;
			static constexpr auto& DP = GPIOPortK::Pin<7>;

			static constexpr auto& All = GPIOPortK::Out<0,7>;

			static constexpr auto& Select0 = GPIOPortJ::Pin<12>;
			static constexpr auto& Select1 = GPIOPortJ::Pin<13>;
			static constexpr auto& Select2 = GPIOPortJ::Pin<14>;
			static constexpr auto& Select3 = GPIOPortJ::Pin<15>;

			static constexpr auto& SelectAll = GPIOPortJ::Out<12,15>;


		}


		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using I2CA = bsp::drv::I2C<&hi2c2, bsp::asg::drv::I2C>;
		using I2CB = bsp::drv::I2C<&hi2c5, bsp::asg::drv::I2C>;
		// using I2CC = bsp::drv::I2C<&hi2c6, bsp::asg::drv::I2C>;
		using I2CD = bsp::drv::I2C<&hi2c1, bsp::asg::drv::I2C>;
		/** @} */

	}

#endif
