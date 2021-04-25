/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file midgard/midgard.hpp                                      *
  *  @ingroup midgard                                               *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Top-level include file for Midgard					    *
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

#include <stm32f7xx_hal.h>

#include <midgard/driver/gpio.hpp>
#include <midgard/driver/adc.hpp>
#include <midgard/driver/uart.hpp>
#include <midgard/driver/i2c.hpp>

#include <midgard/core/cache.hpp>
#include <midgard/core/cortex.hpp>
#include <midgard/core/instructions.hpp>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	extern "C" I2C_HandleTypeDef hi2c1;
	extern "C" I2C_HandleTypeDef hi2c2;
	extern "C" I2C_HandleTypeDef hi2c3;
	extern "C" I2C_HandleTypeDef hi2c4;

	namespace bsp {

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using GPIOPortA = bsp::drv::GPIOPort<0x4002'0000, bsp::mid::drv::GPIOPort>;
		using GPIOPortB = bsp::drv::GPIOPort<0x4002'0400, bsp::mid::drv::GPIOPort>;
		using GPIOPortC = bsp::drv::GPIOPort<0x4002'0800, bsp::mid::drv::GPIOPort>;
		using GPIOPortD = bsp::drv::GPIOPort<0x4002'0C00, bsp::mid::drv::GPIOPort>;
		using GPIOPortE = bsp::drv::GPIOPort<0x4002'1000, bsp::mid::drv::GPIOPort>;
		using GPIOPortF = bsp::drv::GPIOPort<0x4002'1400, bsp::mid::drv::GPIOPort>;
		using GPIOPortG = bsp::drv::GPIOPort<0x4002'1800, bsp::mid::drv::GPIOPort>;
		using GPIOPortH = bsp::drv::GPIOPort<0x4002'1C00, bsp::mid::drv::GPIOPort>;
		using GPIOPortI = bsp::drv::GPIOPort<0x4002'2000, bsp::mid::drv::GPIOPort>;
		using GPIOPortJ = bsp::drv::GPIOPort<0x4002'2400, bsp::mid::drv::GPIOPort>;
		using GPIOPortK = bsp::drv::GPIOPort<0x4002'2800, bsp::mid::drv::GPIOPort>;
		/** @} */

		static constexpr auto& LeftJoyStickButton = GPIOPortG::Pin<10>;
		static constexpr auto& RightJoyStickButton = GPIOPortG::Pin<11>;

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

		static constexpr auto& EncoderButton = GPIOPortK::Pin<3>;
		static constexpr auto& ButtonA = GPIOPortK::Pin<4>;
		static constexpr auto& ButtonB = GPIOPortK::Pin<5>;
		static constexpr auto& ButtonC = GPIOPortK::Pin<6>;
		static constexpr auto& ButtonD = GPIOPortK::Pin<7>;

		static constexpr auto& DriverA = GPIOPortC::Pin<13>;
		static constexpr auto& LD5 = DriverA;
		static constexpr auto& LDE = DriverA;
		static constexpr auto& DriverB = GPIOPortI::Pin<8>;
		static constexpr auto& LD6 = DriverB;
		static constexpr auto& LDF = DriverB;
		static constexpr auto& DriverC = GPIOPortB::Pin<0>;
		static constexpr auto& LD7 = DriverC;
		static constexpr auto& LDG = DriverC;
		static constexpr auto& DriverD = GPIOPortB::Pin<1>;
		static constexpr auto& LD8 = DriverD;
		static constexpr auto& LDH = DriverD;

		namespace seven_segment {
			static constexpr auto& A = GPIOPortG::Pin<0>;
			static constexpr auto& B = GPIOPortG::Pin<1>;
			static constexpr auto& C = GPIOPortG::Pin<2>;
			static constexpr auto& D = GPIOPortG::Pin<3>;
			static constexpr auto& E = GPIOPortG::Pin<4>;
			static constexpr auto& F = GPIOPortG::Pin<5>;
			static constexpr auto& G = GPIOPortG::Pin<6>;
			static constexpr auto& DP = GPIOPortG::Pin<7>;

			static constexpr auto& All = GPIOPortG::Out<0,7>;

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
		using I2CA = bsp::drv::I2C<&hi2c2, bsp::mid::drv::I2C>;
		using I2CB = bsp::drv::I2C<&hi2c4, bsp::mid::drv::I2C>;
		/** @} */

	}

#endif
