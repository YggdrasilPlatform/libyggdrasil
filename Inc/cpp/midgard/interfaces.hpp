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

#include <cpp/midgard/driver/gpio.hpp>
#include <cpp/midgard/driver/adc.hpp>
#include <cpp/midgard/driver/dac.hpp>
#include <cpp/midgard/driver/uart.hpp>
#include <cpp/midgard/driver/i2c.hpp>
#include <cpp/midgard/driver/spi.hpp>
#include <cpp/midgard/driver/can.hpp>
#include <cpp/midgard/driver/timer.hpp>
#include <cpp/midgard/driver/rng.hpp>
#include <cpp/midgard/driver/hash.hpp>
#include <cpp/midgard/driver/display.hpp>

#include <cpp/midgard/core/cache.hpp>
#include <cpp/midgard/core/cortex.hpp>
#include <cpp/midgard/core/instructions.hpp>

#include <tuple>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	/**
	 * @brief External HandleTypeDef definitions
	 * @{
	 */
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
	/** @} */

	namespace bsp {

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using GPIOPortA = bsp::drv::GPIOPort<0x4002'0000, bsp::mid::drv::GPIOPort>;		///< GPIO Port A
		using GPIOPortB = bsp::drv::GPIOPort<0x4002'0400, bsp::mid::drv::GPIOPort>;		///< GPIO Port B
		using GPIOPortC = bsp::drv::GPIOPort<0x4002'0800, bsp::mid::drv::GPIOPort>;		///< GPIO Port C
		using GPIOPortD = bsp::drv::GPIOPort<0x4002'0C00, bsp::mid::drv::GPIOPort>;		///< GPIO Port D
		using GPIOPortE = bsp::drv::GPIOPort<0x4002'1000, bsp::mid::drv::GPIOPort>;		///< GPIO Port E
		using GPIOPortF = bsp::drv::GPIOPort<0x4002'1400, bsp::mid::drv::GPIOPort>;		///< GPIO Port F
		using GPIOPortG = bsp::drv::GPIOPort<0x4002'1800, bsp::mid::drv::GPIOPort>;		///< GPIO Port G
		using GPIOPortH = bsp::drv::GPIOPort<0x4002'1C00, bsp::mid::drv::GPIOPort>;		///< GPIO Port H
		using GPIOPortI = bsp::drv::GPIOPort<0x4002'2000, bsp::mid::drv::GPIOPort>;		///< GPIO Port I
		using GPIOPortJ = bsp::drv::GPIOPort<0x4002'2400, bsp::mid::drv::GPIOPort>;		///< GPIO Port J
		using GPIOPortK = bsp::drv::GPIOPort<0x4002'2800, bsp::mid::drv::GPIOPort>;		///< GPIO Port K
		/** @} */

		/**
		 * @brief User LEDs and buttons definitions
		 * @{
		 */
		static constexpr auto& LD1 = GPIOPortJ::Pin<0>;									///< Alias for LDA
		static constexpr auto& LDA = LD1;												///< LDA
		static constexpr auto& LedBlue = LD1;											///< Alias for LDA
		static constexpr auto& LD2 = GPIOPortJ::Pin<1>;									///< Alias for LDB
		static constexpr auto& LDB = LD2;												///< LDB
		static constexpr auto& LedRed = LD2;											///< Alias for LDB
		static constexpr auto& LD3 = GPIOPortJ::Pin<2>;									///< Alias for LDC
		static constexpr auto& LDC = LD3;												///< LDC
		static constexpr auto& LedYellow = LD3;											///< Alias for LDC
		static constexpr auto& LD4 = GPIOPortJ::Pin<3>;									///< Alias for LDD
		static constexpr auto& LDD = LD4;												///< LDD
		static constexpr auto& LedGreen = LD4;											///< Alias for LDD

		static constexpr auto& Heartbeat = GPIOPortA::Pin<10>;							///< Heartbeat led

		static constexpr auto& EncoderButton = GPIOPortK::Pin<3, drv::Active::Low>;		///< Encoder Button

		static constexpr auto& LeftJoyStickButton = GPIOPortG::Pin<10, drv::Active::Low>;	///< JoystickA Button
		static constexpr auto& ButtonJoystickA = LeftJoyStickButton;						///< Alias for JoystickA Button
		static constexpr auto& RightJoyStickButton = GPIOPortG::Pin<11, drv::Active::Low>;	///< JoystickB Button
		static constexpr auto& ButtonJoystickB = RightJoyStickButton;						///< Alias for JoystickB Button

		static constexpr auto& ButtonA = GPIOPortK::Pin<4, drv::Active::Low>;			///< Button A
		static constexpr auto& ButtonB = GPIOPortK::Pin<5, drv::Active::Low>;			///< Button B
		static constexpr auto& ButtonC = GPIOPortK::Pin<6, drv::Active::Low>;			///< Button C
		static constexpr auto& ButtonD = GPIOPortK::Pin<7, drv::Active::Low>;			///< Button D

		static constexpr auto& DriverA = GPIOPortC::Pin<13>;							///< Sink driver pin A
		static constexpr auto& LD5 = DriverA;											///< Alias for Sink driver pin A
		static constexpr auto& LDE = DriverA;											///< Alias for Sink driver pin A
		static constexpr auto& DriverB = GPIOPortI::Pin<8>;								///< Sink driver pin B
		static constexpr auto& LD6 = DriverB;											///< Alias for Sink driver pin B
		static constexpr auto& LDF = DriverB;											///< Alias for Sink driver pin B
		static constexpr auto& DriverC = GPIOPortB::Pin<0>;								///< Sink driver pin C
		static constexpr auto& LD7 = DriverC;											///< Alias for Sink driver pin C
		static constexpr auto& LDG = DriverC;											///< Alias for Sink driver pin C
		static constexpr auto& DriverD = GPIOPortB::Pin<1>;								///< Sink driver pin D
		static constexpr auto& LD8 = DriverD;											///< Alias for Sink driver pin D
		static constexpr auto& LDH = DriverD;											///< Alias for Sink driver pin D
		/** @} */

		/**
		 * @brief ADC definitions
		 * @{
		 */
		using ADConverter1 = bsp::drv::ADConverter<&hadc1, bsp::mid::drv::ADCChannel>;	///< ADC1
		using ADConverter2 = bsp::drv::ADConverter<&hadc2, bsp::mid::drv::ADCChannel>;	///< ADC2
		using ADConverter3 = bsp::drv::ADConverter<&hadc3, bsp::mid::drv::ADCChannel>;	///< ADC3
		/** @} */

		/**
		 * @brief ADC channel definitions
		 * @{
		 */
		static constexpr auto& ADCA 				= ADConverter1::Channel<3>;			///< ADCA on Analog header
		static constexpr auto& ADCB 				= ADConverter1::Channel<10>;		///< ADCB on Analog header
		static constexpr auto& ADCC 				= ADConverter3::Channel<14>;		///< ADCC on Analog header
		static constexpr auto& ADCD 				= ADConverter3::Channel<15>;		///< ADCD on Analog header
		static constexpr auto& ADCPotentiometer 	= ADConverter2::Channel<13>;		///< Potentiometer
		static constexpr auto& ADCTemperature 		= ADConverter1::Channel<18>;		///< Internal temperature sensor
		/** @} */

		/**
		 * @brief DAC definitions
		 * @{
		 */
		using DAConverter = bsp::drv::DAConverter<&hdac, bsp::mid::drv::DACChannel>;	///< DAC
		/** @} */

		/**
		 * @brief DAC channel definitions
		 * @{
		 */
		static constexpr auto& DACA	= DAConverter::Channel<1>;							///< DACA on Analog header
		static constexpr auto& DACB	= DAConverter::Channel<2>;							///< DACB on Analog header
		/** @} */

		/**
		 * @brief 7-Segment definitions
		 * @{
		 */
		namespace seven_segment {

			static constexpr auto& A  = GPIOPortG::Pin<0>;								///< 7-Segment segment A
			static constexpr auto& B  = GPIOPortG::Pin<1>;								///< 7-Segment segment B
			static constexpr auto& C  = GPIOPortG::Pin<2>;								///< 7-Segment segment C
			static constexpr auto& D  = GPIOPortG::Pin<3>;								///< 7-Segment segment D
			static constexpr auto& E  = GPIOPortG::Pin<4>;								///< 7-Segment segment E
			static constexpr auto& F  = GPIOPortG::Pin<5>;								///< 7-Segment segment F
			static constexpr auto& G  = GPIOPortG::Pin<6>;								///< 7-Segment segment G
			static constexpr auto& DP = GPIOPortG::Pin<7>;								///< 7-Segment segment DP

			static constexpr auto& All = GPIOPortG::Out<0,7>;							///< 7-Segment segments

			static constexpr auto& Select0 = GPIOPortJ::Pin<12>;						///< 7-Segment enable pin 0
			static constexpr auto& Select1 = GPIOPortJ::Pin<13>;						///< 7-Segment enable pin 1
			static constexpr auto& Select2 = GPIOPortJ::Pin<14>;						///< 7-Segment enable pin 2
			static constexpr auto& Select3 = GPIOPortJ::Pin<15>;						///< 7-Segment enable pin 3

			static constexpr auto& SelectAll = GPIOPortJ::Out<12,15>;					///< 7-Segment enable pins

		}
		/** @} */

		/**
		 * @brief I2C definitions
		 * @{
		 */
		using I2CA = bsp::drv::I2C<&hi2c2, bsp::mid::drv::I2C>;							///< I2CA on board Sensors, Seeed, Raspberry, PMod
		using I2CB = bsp::drv::I2C<&hi2c4, bsp::mid::drv::I2C>;							///< I2CB Seeed, Raspberry, PMod
		using I2CC = bsp::drv::I2C<&hi2c3, bsp::mid::drv::I2C>;							///< I2CC display touch screen
		using I2CD = bsp::drv::I2C<&hi2c1, bsp::mid::drv::I2C>;							///< I2CD DCMI, USB C and USB Hub (NC), Audio Codec
		/** @} */

		/**
		 * @brief SPI definitions
		 * @{
		 */
		using SPIA = bsp::drv::SPI<&hspi2, bsp::mid::drv::SPI>;							///< SPI A onboard only
		using SPIB = bsp::drv::SPI<&hspi4 , bsp::mid::drv::SPI>;						///< SPI B on Raspberry
		using SPIC = bsp::drv::SPI<&hspi5, bsp::mid::drv::SPI>;							///< SPI C on Raspberry

		static constexpr auto& SPIACE = GPIOPortI::Pin<0, drv::Active::Low>;			///< SPI A chip enable
		static constexpr auto& SK9822_EN = GPIOPortD::Pin<9>;							///< SPI A chip enable for SK9822 RGB LEDs
		static constexpr auto& SPIBCE = GPIOPortE::Pin<11, drv::Active::Low>;			///< SPI B chip enable
		static constexpr auto& SPICCE = GPIOPortH::Pin<5, drv::Active::Low>;			///< SPI C chip enable
		/** @} */

		/**
		 * @brief UART definitions
		 * @{
		 */
		using UARTA = bsp::drv::UART<0x4000'4400, bsp::mid::drv::UART>;	 				///< USART 2 on Raspberry, PMod
		using UARTB = bsp::drv::UART<0x4000'7C00, bsp::mid::drv::UART>;					///< UART 8 on Raspberry, PMod
		using UARTC = bsp::drv::UART<0x4000'4C00, bsp::mid::drv::UART>;					///< UART 4 onboard to STLINK-V3
		using UARTST = UARTC;															///< UART ST onboard to STLINK-V3
		/** @} */

		/**
		 * @brief CAN definitions
		 * @{
		 */
		using CANA = bsp::drv::CAN<&hcan1, bsp::mid::drv::CAN>;							///< CAN A
		using CANB = bsp::drv::CAN<&hcan2, bsp::mid::drv::CAN>;							///< CAN B
		/** @} */

		/**
		 * @brief Timer definitions
		 * @{
		 */
		using TimerA = bsp::drv::Timer<&htim12, bsp::mid::drv::Timer, u16>;				///< PWM on Raspberry / PMod
		using TimerB = bsp::drv::Timer<&htim4, bsp::mid::drv::Timer, u16>;				///< PWM on Motor Driver / Raspberry / PMod
		using TimerC = bsp::drv::Timer<&htim5, bsp::mid::drv::Timer, u32>;				///< PWM on Raspberry / PMod
		using TimerD = bsp::drv::Timer<&htim3, bsp::mid::drv::Timer, u16>;				///< PWM on Sink Driver
		using TimerE = bsp::drv::Timer<&htim11, bsp::mid::drv::Timer, u16>;				///< PWM for LCD Backlight Control
		using TimerF = bsp::drv::Timer<&htim8, bsp::mid::drv::Timer, u16>;				///< Encoder
		using TimerG = bsp::drv::Timer<&htim2, bsp::mid::drv::Timer, u32>;				///< Profile Counter

		using SinkDriverTimerA = TimerD;												///< Timer for sink driver A
		using SinkDriverTimerB = TimerD;												///< Timer for sink driver B
		using SinkDriverTimerC = TimerD;												///< Timer for sink driver C
		using SinkDriverTimerD = TimerD;												///< Timer for sink driver D
		/** @} */

		/**
		 * @brief Timer channel definitions
		 * @{
		 */
		static constexpr auto& TimerACHA = TimerA::Channel<1>;							///< PMod A Pin 2 / Raspberry Pin 33

		static constexpr auto& TimerBCHA = TimerB::Channel<1>;							///< Motor Driver / Raspberry Pin 26
		static constexpr auto& TimerBCHB = TimerB::Channel<2>;							///< Motor Driver / Raspberry Pin 28
		static constexpr auto& TimerBCHC = TimerB::Channel<3>;							///< Motor Driver / PMod B Pin 2 / Raspberry Pin 32
		static constexpr auto& TimerBCHD = TimerB::Channel<4>;							///< Motor Driver / Raspberry Pin 36

		static constexpr auto& TimerCCHA = TimerC::Channel<1>;							///< PMod A Pin 4 / Raspberry Pin 27

		static constexpr auto& SinkDriverTimerCHA = SinkDriverTimerA::Channel<1>;		///< Sink driver A
		static constexpr auto& SinkDriverTimerCHB = SinkDriverTimerB::Channel<2>;		///< Sink driver B
		static constexpr auto& SinkDriverTimerCHC = SinkDriverTimerC::Channel<3>;		///< Sink driver C
		static constexpr auto& SinkDriverTimerCHD = SinkDriverTimerD::Channel<4>;		///< Sink driver D

		static constexpr auto& Encoder = TimerF::Encoder;								///< Encoder

		static constexpr auto& ProfileCounter = TimerG::ProfileCounter;					///< Profilecounter
		/** @} */

		/**
		 * @brief Motor driver control pin definitions
		 * @{
		 */
		static constexpr auto& TC78Mode = GPIOPortI::Pin<12>;							///< Motor driver mode pin
		static constexpr auto& TC78Err  = GPIOPortI::Pin<13, drv::Active::Low>;			///< Motor driver error pin
		static constexpr auto& TC78Stby = GPIOPortI::Pin<14, drv::Active::Low>;			///< Motor driver standby pin
		/** @} */

		/**
		 * @brief Random hardware acceleration definitions
		 * @{
		 */
		using Random = bsp::drv::Random<0x5006'0800, bsp::mid::drv::Random>;			///< MCU RNG hardware
		/** @} */

		/**
		 * @brief CRC hardware acceleration definitions
		 * @{
		 */
		using Hash	 = bsp::drv::Hash<0x4002'3000, bsp::mid::drv::Hash>;				///< MCU CRC hardware
		/** @} */

		/**
		 * @brief Display definitions
		 * @{
		 */
		using Display = bsp::drv::Display<std::make_tuple(&hltdc, &hdsi, &hdma2d), bsp::mid::drv::Display>;	///< LCD Display
		/** @} */

	}

#endif
