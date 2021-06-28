 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file cpp/asg_coproc/interfaces.hpp
  *  @ingroup asg_coproc
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Interface definitions for Asgard
  */

#pragma once

#include <stm32mp1xx_hal.h>

#include <cpp/asgard_coproc/driver/gpio.hpp>
#include <cpp/asgard_coproc/driver/adc.hpp>
#include <cpp/asgard_coproc/driver/dac.hpp>
#include <cpp/asgard_coproc/driver/uart.hpp>
#include <cpp/asgard_coproc/driver/i2c.hpp>
#include <cpp/asgard_coproc/driver/spi.hpp>
#include <cpp/asgard_coproc/driver/can.hpp>
#include <cpp/asgard_coproc/driver/timer.hpp>
#include <cpp/asgard_coproc/driver/rng.hpp>
#include <cpp/asgard_coproc/driver/hash.hpp>


#include <cpp/asgard_coproc/core/cortex.hpp>
#include <cpp/asgard_coproc/core/instructions.hpp>

#include <tuple>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	/**
	 * @brief External HandleTypeDef definitions
	 * @{
	 */
	extern I2C_HandleTypeDef hi2c1;
	extern I2C_HandleTypeDef hi2c2;
	extern I2C_HandleTypeDef hi2c5;

	extern SPI_HandleTypeDef hspi2;
	extern SPI_HandleTypeDef hspi4;
	extern SPI_HandleTypeDef hspi5;

	extern TIM_HandleTypeDef htim1;
	extern TIM_HandleTypeDef htim2;
	extern TIM_HandleTypeDef htim3;
	extern TIM_HandleTypeDef htim4;
	extern TIM_HandleTypeDef htim5;
	extern TIM_HandleTypeDef htim6;
	extern TIM_HandleTypeDef htim12;
	extern TIM_HandleTypeDef htim16;

	extern ADC_HandleTypeDef hadc1;
	extern ADC_HandleTypeDef hadc2;

	extern DAC_HandleTypeDef hdac1;

	extern FDCAN_HandleTypeDef hfdcan1;
	extern FDCAN_HandleTypeDef hfdcan2;
	/** @} */

	namespace bsp {

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using GPIOPortA = bsp::drv::GPIOPort<0x5000'2000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port A
		using GPIOPortB = bsp::drv::GPIOPort<0x5000'3000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port B
		using GPIOPortC = bsp::drv::GPIOPort<0x5000'4000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port C
		using GPIOPortD = bsp::drv::GPIOPort<0x5000'5000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port A
		using GPIOPortE = bsp::drv::GPIOPort<0x5000'6000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port E
		using GPIOPortF = bsp::drv::GPIOPort<0x5000'7000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port F
		using GPIOPortG = bsp::drv::GPIOPort<0x5000'8000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port G
		using GPIOPortH = bsp::drv::GPIOPort<0x5000'9000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port H
		using GPIOPortI = bsp::drv::GPIOPort<0x5000'A000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port I
		using GPIOPortJ = bsp::drv::GPIOPort<0x5000'B000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port J
		using GPIOPortK = bsp::drv::GPIOPort<0x5000'C000, bsp::asg_coproc::drv::GPIOPort>;		///< GPIO Port K
		/** @} */

		/**
		 * @brief User LEDs and buttons definitions
		 * @{
		 */
		static constexpr auto& LD1 = GPIOPortJ::Pin<0>;											///< Alias for LDA
		static constexpr auto& LDA = LD1;														///< LDA
		static constexpr auto& LedBlue = LD1;													///< Alias for LDA
		static constexpr auto& LD2 = GPIOPortJ::Pin<1>;											///< Alias for LDB
		static constexpr auto& LDB = LD2;														///< LDB
		static constexpr auto& LedRed = LD2;													///< Alias for LDB
		static constexpr auto& LD3 = GPIOPortJ::Pin<2>;											///< Alias for LDC
		static constexpr auto& LDC = LD3;														///< LDC
		static constexpr auto& LedYellow = LD3;													///< Alias for LDC
		static constexpr auto& LD4 = GPIOPortJ::Pin<3>;											///< Alias for LDD
		static constexpr auto& LDD = LD4;														///< LDD
		static constexpr auto& LedGreen = LD4;													///< Alias for LDD

		static constexpr auto& Heartbeat = GPIOPortD::Pin<11>;									///< Heartbeat led

		static constexpr auto& EncoderButton = GPIOPortK::Pin<3, drv::Active::Low>;				///< Encoder Button

		static constexpr auto& LeftJoyStickButton = GPIOPortE::Pin<9, drv::Active::Low>;		///< JoystickA Button
		static constexpr auto& ButtonJoystickA = LeftJoyStickButton;							///< Alias for JoystickA Button
		static constexpr auto& RightJoyStickButton = GPIOPortE::Pin<7, drv::Active::Low>;		///< JoystickB Button
		static constexpr auto& ButtonJoystickB = RightJoyStickButton;							///< Alias for JoystickB Button

		static constexpr auto& ButtonA = GPIOPortJ::Pin<4, drv::Active::Low>;					///< Button A
		static constexpr auto& ButtonB = GPIOPortJ::Pin<5, drv::Active::Low>;					///< Button B
		static constexpr auto& ButtonC = GPIOPortJ::Pin<6, drv::Active::Low>;					///< Button C
		static constexpr auto& ButtonD = GPIOPortJ::Pin<7, drv::Active::Low>;					///< Button D

		static constexpr auto& DriverA = GPIOPortB::Pin<3>;										///< Sink driver pin A
		static constexpr auto& LD5 = DriverA;													///< Alias for Sink driver pin A
		static constexpr auto& LDE = DriverA;													///< Alias for Sink driver pin A
		static constexpr auto& DriverB = GPIOPortB::Pin<4>;										///< Sink driver pin B
		static constexpr auto& LD6 = DriverB;													///< Alias for Sink driver pin B
		static constexpr auto& LDF = DriverB;													///< Alias for Sink driver pin B
		static constexpr auto& DriverC = GPIOPortB::Pin<14>;									///< Sink driver pin C
		static constexpr auto& LD7 = DriverC;													///< Alias for Sink driver pin C
		static constexpr auto& LDG = DriverC;													///< Alias for Sink driver pin C
		static constexpr auto& DriverD = GPIOPortB::Pin<15>;									///< Sink driver pin D
		static constexpr auto& LD8 = DriverD;													///< Alias for Sink driver pin D
		static constexpr auto& LDH = DriverD;													///< Alias for Sink driver pin D
		/** @} */

		/**
		 * @brief ADC definitions
		 * @{
		 */
		using ADConverter1 = bsp::drv::ADConverter<&hadc1, bsp::asg_coproc::drv::ADCChannel>;	///< ADC1
		using ADConverter2 = bsp::drv::ADConverter<&hadc2, bsp::asg_coproc::drv::ADCChannel>;	///< ADC2
		/** @} */

		/**
		 * @brief ADC channel definitions
		 * @{
		 */
		static constexpr auto& ADCA 				= ADConverter1::Channel<0>;					///< ADCA on Analog header
		static constexpr auto& ADCB 				= ADConverter1::Channel<1>;					///< ADCB on Analog header
		static constexpr auto& ADCC 				= ADConverter1::Channel<2>;					///< ADCC on Analog header
		static constexpr auto& ADCD 				= ADConverter1::Channel<6>;					///< ADCD on Analog header
		static constexpr auto& ADCPotentiometer 	= ADConverter1::Channel<15>;				///< Potentiometer
		static constexpr auto& ADCTemperature 		= ADConverter2::Channel<12>;				///< Internal temperature sensor
		/** @} */

		/**
		 * @brief DAC definitions
		 * @{
		 */
		using DAConverter1 = bsp::drv::DAConverter<&hdac1, bsp::asg_coproc::drv::DACChannel>;	///< DAC1
		/** @} */

		/**
		 * @brief DAC channel definitions
		 * @{
		 */
		static constexpr auto& DACA	= DAConverter1::Channel<1>;									///< DACA on Analog header
		static constexpr auto& DACB	= DAConverter1::Channel<2>;									///< DACB on Analog header
		/** @} */

		/**
		 * @brief 7-Segment definitions
		 * @{
		 */
		namespace seven_segment {

			static constexpr auto& A  = GPIOPortK::Pin<0>;										///< 7-Segment segment A
			static constexpr auto& B  = GPIOPortK::Pin<1>;										///< 7-Segment segment B
			static constexpr auto& C  = GPIOPortK::Pin<2>;										///< 7-Segment segment C
			static constexpr auto& D  = GPIOPortK::Pin<3>;										///< 7-Segment segment D
			static constexpr auto& E  = GPIOPortK::Pin<4>;										///< 7-Segment segment E
			static constexpr auto& F  = GPIOPortK::Pin<5>;										///< 7-Segment segment F
			static constexpr auto& G  = GPIOPortK::Pin<6>;										///< 7-Segment segment G
			static constexpr auto& DP = GPIOPortK::Pin<7>;										///< 7-Segment segment DP

			static constexpr auto& All = GPIOPortK::Out<0,7>;									///< 7-Segment segments

			static constexpr auto& Select0 = GPIOPortJ::Pin<12>;								///< 7-Segment enable pin 0
			static constexpr auto& Select1 = GPIOPortJ::Pin<13>;								///< 7-Segment enable pin 1
			static constexpr auto& Select2 = GPIOPortJ::Pin<14>;								///< 7-Segment enable pin 2
			static constexpr auto& Select3 = GPIOPortJ::Pin<15>;								///< 7-Segment enable pin 3

			static constexpr auto& SelectAll = GPIOPortJ::Out<12,15>;							///< 7-Segment enable pins

		}
		/** @} */

		/**
		 * @brief I2C definitions
		 * @{
		 */
		using I2CA = bsp::drv::I2C<&hi2c2, bsp::asg_coproc::drv::I2C>;							///< I2CA on board Sensors, Seeed, Raspberry, PMod
		using I2CB = bsp::drv::I2C<&hi2c5, bsp::asg_coproc::drv::I2C>;							///< I2CB Seeed, Raspberry, PMod
		using I2CD = bsp::drv::I2C<&hi2c1, bsp::asg_coproc::drv::I2C>;							///< I2CD DCMI, USB C and USB Hub (NC), Audio Codec
		/** @} */

		/**
		 * @brief SPI definitions
		 * @{
		 */
		using SPIA = bsp::drv::SPI<&hspi2, bsp::asg_coproc::drv::SPI>;							///< SPI A onboard only
		using SPIB = bsp::drv::SPI<&hspi4 , bsp::asg_coproc::drv::SPI>;							///< SPI B on Raspberry
		using SPIC = bsp::drv::SPI<&hspi5, bsp::asg_coproc::drv::SPI>;							///< SPI C on Raspberry

		static constexpr auto& SPIACE = GPIOPortI::Pin<0, drv::Active::Low>;					///< SPI A chip enable
		static constexpr auto& SK9822_EN = GPIOPortE::Pin<10>;									///< SPI A chip enable for SK9822 RGB LEDs
		static constexpr auto& SPIBCE = GPIOPortF::Pin<5, drv::Active::Low>;					///< SPI B chip enable
		static constexpr auto& SPICCE = GPIOPortH::Pin<5, drv::Active::Low>;					///< SPI C chip enable
		/** @} */

		/**
		 * @brief UART definitions
		 * @{
		 */
		using UARTA = bsp::drv::UART<0x4000'E000, bsp::asg_coproc::drv::UART>;	 				///< USART 2 on Raspberry, PMod
		using UARTB = bsp::drv::UART<0x4001'9000, bsp::asg_coproc::drv::UART>;					///< UART 8 on Raspberry, PMod
		using UARTC = bsp::drv::UART<0x4001'0000, bsp::asg_coproc::drv::UART>;					///< UART 4 onboard to STLINK-V3
		using UARTST = UARTC;																	///< UART ST onboard to STLINK-V3
		/** @} */

		/**
		 * @brief CAN definitions
		 * @{
		 */
		using CANA = bsp::drv::CAN<&hfdcan1, bsp::asg_coproc::drv::CAN>;						///< CAN A
		using CANB = bsp::drv::CAN<&hfdcan2, bsp::asg_coproc::drv::CAN>;						///< CAN B
		/** @} */

		/**
		 * @brief Timer definitions
		 * @{
		 */
		using TimerA = bsp::drv::Timer<&htim2, bsp::asg_coproc::drv::Timer, u32>;				///< PWM on Raspberry / PMod / Sink Driver
		using TimerB = bsp::drv::Timer<&htim4, bsp::asg_coproc::drv::Timer, u16>;				///< PWM on Motor Driver / Raspberry / PMod
		using TimerC = bsp::drv::Timer<&htim16, bsp::asg_coproc::drv::Timer, u16>;				///< PWM on Raspberry / PMod
		using TimerD = bsp::drv::Timer<&htim12, bsp::asg_coproc::drv::Timer, u16>;				///< PWM on Sink Driver
		using TimerE = bsp::drv::Timer<&htim3, bsp::asg_coproc::drv::Timer, u16>;				///< PWM for Sink Driver / LCD Backlight Control
		using TimerF = bsp::drv::Timer<&htim1, bsp::asg_coproc::drv::Timer, u16>;				///< Encoder
		using TimerG = bsp::drv::Timer<&htim5, bsp::asg_coproc::drv::Timer, u32>;				///< Profile Counter

		using SinkDriverTimerA = TimerA;														///< Timer for sink driver A
		using SinkDriverTimerB = TimerE;														///< Timer for sink driver B
		using SinkDriverTimerC = TimerD;														///< Timer for sink driver C
		using SinkDriverTimerD = TimerD;														///< Timer for sink driver D
		/** @} */

		/**
		 * @brief Timer channel definitions
		 * @{
		 */
		static constexpr auto& TimerACHA = TimerA::Channel<3>;									///< PMod A Pin 2 / Raspberry Pin 33

		static constexpr auto& TimerBCHA = TimerB::Channel<1>;									///< Motor Driver / Raspberry Pin 26
		static constexpr auto& TimerBCHB = TimerB::Channel<2>;									///< Motor Driver / Raspberry Pin 28
		static constexpr auto& TimerBCHC = TimerB::Channel<3>;									///< Motor Driver / PMod B Pin 2 / Raspberry Pin 32
		static constexpr auto& TimerBCHD = TimerB::Channel<4>;									///< Motor Driver / Raspberry Pin 36

		static constexpr auto& TimerCCHA = TimerC::Channel<1>;									///< PMod A Pin 4 / Raspberry Pin 27

		static constexpr auto& SinkDriverTimerCHA = SinkDriverTimerA::Channel<2>;				///< Sink driver A
		static constexpr auto& SinkDriverTimerCHB = SinkDriverTimerB::Channel<1>;				///< Sink driver B
		static constexpr auto& SinkDriverTimerCHC = SinkDriverTimerC::Channel<1>;				///< Sink driver C
		static constexpr auto& SinkDriverTimerCHD = SinkDriverTimerD::Channel<2>;				///< Sink driver D

		static constexpr auto& Encoder = TimerF::Encoder;										///< Encoder

		static constexpr auto& ProfileCounter = TimerG::ProfileCounter;							///< Profilecounter
		/** @} */

		/**
		 * @brief Motor driver control pin definitions
		 * @{
		 */
		static constexpr auto& TC78Mode = GPIOPortF::Pin<3>;									///< Motor driver mode pin
		static constexpr auto& TC78Err  = GPIOPortG::Pin<9, drv::Active::Low>;					///< Motor driver error pin
		static constexpr auto& TC78Stby = GPIOPortI::Pin<10, drv::Active::Low>;					///< Motor driver standby pin
		/** @} */

		/**
		 * @brief Random hardware acceleration definitions
		 * @{
		 */
		using Random = bsp::drv::Random<0x5400'3000, bsp::asg_coproc::drv::Random>;				///< MCU RNG1 hardware
		/** @} */

		/**
		 * @brief CRC hardware acceleration definitions
		 * @{
		 */
		using Hash	 = bsp::drv::Hash<0x5400'2000, bsp::asg_coproc::drv::Hash>;					///< MCU CRC1 hardware
		/** @} */




	}

#endif
