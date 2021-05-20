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
  *  @file midgard/interfaces.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Interface definitions for Midgard
  */

#pragma once

#include <stm32f7xx_hal.h>

#include <midgard/driver/gpio.hpp>
#include <midgard/driver/adc.hpp>
#include <midgard/driver/dac.hpp>
#include <midgard/driver/uart.hpp>
#include <midgard/driver/i2c.hpp>
#include <midgard/driver/spi.hpp>
#include <midgard/driver/can.hpp>
#include <midgard/driver/timer.hpp>
#include <midgard/driver/rng.hpp>
#include <midgard/driver/hash.hpp>
#include <midgard/driver/display.hpp>

#include <midgard/core/cache.hpp>
#include <midgard/core/cortex.hpp>
#include <midgard/core/instructions.hpp>

#include <tuple>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	extern "C" {

		extern I2C_HandleTypeDef hi2c1;
		extern I2C_HandleTypeDef hi2c2;
		extern I2C_HandleTypeDef hi2c3;
		extern I2C_HandleTypeDef hi2c4;


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

	}

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

		static constexpr auto& LeftJoyStickButton = GPIOPortG::Pin<10, drv::Active::Low>;
		static constexpr auto& RightJoyStickButton = GPIOPortG::Pin<11, drv::Active::Low>;

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

		static constexpr auto& EncoderButton = GPIOPortK::Pin<3, drv::Active::Low>;
		static constexpr auto& ButtonA = GPIOPortK::Pin<4, drv::Active::Low>;
		static constexpr auto& ButtonB = GPIOPortK::Pin<5, drv::Active::Low>;
		static constexpr auto& ButtonC = GPIOPortK::Pin<6, drv::Active::Low>;
		static constexpr auto& ButtonD = GPIOPortK::Pin<7, drv::Active::Low>;

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

		using ADConverter1 = bsp::drv::ADConverter<&hadc1, bsp::mid::drv::ADCChannel>;
		using ADConverter2 = bsp::drv::ADConverter<&hadc2, bsp::mid::drv::ADCChannel>;
		using ADConverter3 = bsp::drv::ADConverter<&hadc3, bsp::mid::drv::ADCChannel>;

		static constexpr auto& ADCA 				= ADConverter1::Channel<3>;
		static constexpr auto& ADCB 				= ADConverter1::Channel<10>;
		static constexpr auto& ADCC 				= ADConverter3::Channel<14>;
		static constexpr auto& ADCD 				= ADConverter3::Channel<15>;
		static constexpr auto& ADCPotentiometer 	= ADConverter2::Channel<13>;
		static constexpr auto& ADCTemperature 		= ADConverter1::Channel<18>;

		using DAConverter = bsp::drv::DAConverter<&hdac, bsp::mid::drv::DACChannel>;

		static constexpr auto& DACA	= DAConverter::Channel<1>;
		static constexpr auto& DACB	= DAConverter::Channel<2>;

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

		static constexpr auto& RGB_EN = GPIOPortD::Pin<9>;

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using I2CA = bsp::drv::I2C<&hi2c2, bsp::mid::drv::I2C>;
		using I2CB = bsp::drv::I2C<&hi2c4, bsp::mid::drv::I2C>;
		using I2CC = bsp::drv::I2C<&hi2c3, bsp::mid::drv::I2C>;
		using I2CD = bsp::drv::I2C<&hi2c1, bsp::mid::drv::I2C>;
		/** @} */


		using SPIA = bsp::drv::SPI<0x4000'3800, bsp::mid::drv::SPI>;
		using SPIB = bsp::drv::SPI<0x4001'3400 , bsp::mid::drv::SPI>;
		using SPIC = bsp::drv::SPI<0x4001'5000, bsp::mid::drv::SPI>;

		using CANA = bsp::drv::CAN<&hcan1, bsp::mid::drv::CAN>;
		using CANB = bsp::drv::CAN<&hcan2, bsp::mid::drv::CAN>;

		static constexpr auto& SPIACE = GPIOPortI::Pin<0, drv::Active::Low>;


		using TimerA = bsp::drv::Timer<&htim12, bsp::mid::drv::Timer, u16>;
		using TimerB = bsp::drv::Timer<&htim4, bsp::mid::drv::Timer, u16>;
		using TimerC = bsp::drv::Timer<&htim5, bsp::mid::drv::Timer, u32>;
		using TimerD = bsp::drv::Timer<&htim3, bsp::mid::drv::Timer, u16>;
		using TimerE = bsp::drv::Timer<&htim11, bsp::mid::drv::Timer, u16>;
		using TimerF = bsp::drv::Timer<&htim8, bsp::mid::drv::Timer, u16>;
		using TimerG = bsp::drv::Timer<&htim2, bsp::mid::drv::Timer, u32>;		// Profile Counter

		static constexpr auto& TimerACHA = TimerA::Channel<1>;


		static constexpr auto& TimerBCHB = TimerB::Channel<2>;
		static constexpr auto& TimerBCHC = TimerB::Channel<3>;


		static constexpr auto& TimerCCHA = TimerC::Channel<1>;

		static constexpr auto& TimerDCHA = TimerD::Channel<2>;
		static constexpr auto& TimerDCHB = TimerD::Channel<1>;
		static constexpr auto& TimerDCHC = TimerD::Channel<3>;
		static constexpr auto& TimerDCHD = TimerD::Channel<4>;

		static constexpr auto& Encoder = TimerF::Encoder;

		static constexpr auto& ProfileCounter = TimerG::ProfileCounter;

		static constexpr auto& TC78Mode = GPIOPortI::Pin<12>;
		static constexpr auto& TC78Err  = GPIOPortI::Pin<13>;
		static constexpr auto& TC78Stby = GPIOPortI::Pin<14>;
		static constexpr auto& PhaseA = GPIOPortD::Pin<15>;
		static constexpr auto& PhaseB = GPIOPortD::Pin<12>;

		using Random = bsp::drv::Random<0x5006'0800, bsp::mid::drv::Random>;
		using Hash	 = bsp::drv::Hash<0x4002'3000, bsp::mid::drv::Hash>;

		using UARTA = bsp::drv::UART<0x4000'4400, bsp::mid::drv::UART>;	 	// USART 2
		using UARTB = bsp::drv::UART<0x4000'7C00, bsp::mid::drv::UART>;		// UART 8
		using UARTC = bsp::drv::UART<0x4000'4C00, bsp::mid::drv::UART>;		// UART 4

		using Display = bsp::drv::Display<std::make_tuple(&hltdc, &hdsi, &hdma2d), bsp::mid::drv::Display>;

	}

#endif
