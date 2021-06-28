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
  *  @file asgard/interfaces.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Interface definitions for Asgard
  */

#pragma once

#include <cpp/asgard/driver/gpio.hpp>
#include <cpp/asgard/driver/i2c.hpp>
#include <cpp/asgard/driver/spi.hpp>
#include <cpp/asgard/driver/adc.hpp>
#include <cpp/asgard/driver/dac.hpp>

#include <cpp/asgard/core/cortex.hpp>

#include <array>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	namespace bsp {

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using GPIOPortA = bsp::drv::GPIOPort<0, bsp::asg::drv::GPIOPort>;								///< GPIO Port A
		using GPIOPortB = bsp::drv::GPIOPort<16, bsp::asg::drv::GPIOPort>;								///< GPIO Port B
		using GPIOPortC = bsp::drv::GPIOPort<32, bsp::asg::drv::GPIOPort>;								///< GPIO Port C
		using GPIOPortD = bsp::drv::GPIOPort<48, bsp::asg::drv::GPIOPort>;								///< GPIO Port D
		using GPIOPortE = bsp::drv::GPIOPort<64, bsp::asg::drv::GPIOPort>;								///< GPIO Port E
		using GPIOPortF = bsp::drv::GPIOPort<80, bsp::asg::drv::GPIOPort>;								///< GPIO Port F
		using GPIOPortG = bsp::drv::GPIOPort<96, bsp::asg::drv::GPIOPort>;								///< GPIO Port G
		using GPIOPortH = bsp::drv::GPIOPort<112, bsp::asg::drv::GPIOPort>;								///< GPIO Port H
		using GPIOPortI = bsp::drv::GPIOPort<128, bsp::asg::drv::GPIOPort>;								///< GPIO Port I
		using GPIOPortJ = bsp::drv::GPIOPort<144, bsp::asg::drv::GPIOPort>;								///< GPIO Port J
		using GPIOPortK = bsp::drv::GPIOPort<160, bsp::asg::drv::GPIOPort>;								///< GPIO Port K
		/** @} */

		/**
		 * @brief User LEDs and buttons definitions
		 * @{
		 */
    	static constexpr auto& LD1 = GPIOPortJ::Pin<0>;													///< Alias for LDA
		static constexpr auto& LDA = LD1;																///< LDA
		static constexpr auto& LedBlue = LD1;															///< Alias for LDA
		static constexpr auto& LD2 = GPIOPortJ::Pin<1>;													///< Alias for LDB
		static constexpr auto& LDB = LD2;																///< LDB
		static constexpr auto& LedRed = LD2;															///< Alias for LDB
		static constexpr auto& LD3 = GPIOPortJ::Pin<2>;													///< Alias for LDC
		static constexpr auto& LDC = LD3;																///< LDC
		static constexpr auto& LedYellow = LD3;															///< Alias for LDC
		static constexpr auto& LD4 = GPIOPortJ::Pin<3>;													///< Alias for LDF
		static constexpr auto& LDD = LD4;																///< LDF
		static constexpr auto& LedGreen = LD4;															///< Alias for LDF

		static constexpr auto& LeftJoyStickButton = GPIOPortE::Pin<9, drv::Active::Low>;				///< JoystickA Button
		static constexpr auto& ButtonJoystickA = LeftJoyStickButton;									///< Alias for JoystickA Button
		static constexpr auto& RightJoyStickButton = GPIOPortE::Pin<7, drv::Active::Low>;				///< JoystickB Button
		static constexpr auto& ButtonJoystickB = RightJoyStickButton;									///< Alias for JoystickB Button

		static constexpr auto& ButtonA = GPIOPortJ::Pin<4, drv::Active::Low>;							///< Button A
		static constexpr auto& ButtonB = GPIOPortJ::Pin<5, drv::Active::Low>;							///< Button B
		static constexpr auto& ButtonC = GPIOPortJ::Pin<6, drv::Active::Low>;							///< Button C
		static constexpr auto& ButtonD = GPIOPortJ::Pin<7, drv::Active::Low>;							///< Button D

		static constexpr auto& DriverA = GPIOPortB::Pin<3>;												///< Sink driver pin A
		static constexpr auto& LD5 = DriverA;															///< Alias for Sink driver pin A
		static constexpr auto& LDE = DriverA;															///< Alias for Sink driver pin A
		static constexpr auto& DriverB = GPIOPortB::Pin<4>;												///< Sink driver pin B
		static constexpr auto& LD6 = DriverB;															///< Alias for Sink driver pin B
		static constexpr auto& LDF = DriverB;															///< Alias for Sink driver pin B
		static constexpr auto& DriverC = GPIOPortB::Pin<14>;											///< Sink driver pin C
		static constexpr auto& LD7 = DriverC;															///< Alias for Sink driver pin C
		static constexpr auto& LDG = DriverC;															///< Alias for Sink driver pin C
		static constexpr auto& DriverD = GPIOPortB::Pin<15>;											///< Sink driver pin D
		static constexpr auto& LD8 = DriverD;															///< Alias for Sink driver pin D
		static constexpr auto& LDH = DriverD;															///< Alias for Sink driver pin D
		/** @} */

		/**
		 * @brief ADC definitions
		 * @{
		 */
		using ADConverter1 = bsp::drv::ADConverter<2, bsp::mid::drv::ADCChannel>;						///<  ADC1
		/** @} */

		/**
		 * @brief ADC channel definitions
		 * @{
		 */
		static constexpr auto& ADCA 				= ADConverter1::Channel<0, 0, (1 << 16) - 1>;		///< ADCA on Analog header
		static constexpr auto& ADCB 				= ADConverter1::Channel<1, 0, (1 << 16) - 1>;		///< ADCB on Analog header
		static constexpr auto& ADCC 				= ADConverter1::Channel<2, 0, (1 << 16) - 1>;		///< ADCC on Analog header
		static constexpr auto& ADCD 				= ADConverter1::Channel<6, 0, (1 << 16) - 1>;		///< ADCD on Analog header
		static constexpr auto& ADCPotentiometer 	= ADConverter1::Channel<15, 0, (1 << 16) - 1>;		///< Potentiometer
		/** @} */

		/**
		 * @brief DAC definitions
		 * @{
		 */
		using DAConverter1 = bsp::drv::DAConverter<0, bsp::mid::drv::DACChannel>;						///< DAC1
		using DAConverter2 = bsp::drv::DAConverter<1, bsp::mid::drv::DACChannel>;						///< DAC2
		/** @} */

		/**
		 * @brief DAC channel definitions
		 * @{
		 */
		static constexpr auto& DACA	= DAConverter1::Channel<1, 0, (1 << 16) - 1>;						///< DACA on Analog header
		static constexpr auto& DACB	= DAConverter2::Channel<2, 0, (1 << 16) - 1>;						///< DACB on Analog header
		/** @} */

		/**
		 * @brief I2C definitions
		 * @{
		 */
		using I2CA = bsp::drv::I2C<1, bsp::asg::drv::I2C>;												///< I2CA on board Sensors, Seeed, Raspberry, PMod
		using I2CB = bsp::drv::I2C<3, bsp::asg::drv::I2C>;												///< I2CB Seeed, Raspberry, PMod
		using I2CC = bsp::drv::I2C<4, bsp::asg::drv::I2C>;												///< I2CC display touch screen
		using I2CD = bsp::drv::I2C<0, bsp::asg::drv::I2C>;												///< I2CD DCMI, USB C and USB Hub (NC), Audio Codec
		/** @} */

		/**
		 * @brief SPI definitions
		 * @{
		 */
		using SPIA = bsp::drv::SPI<std::array{ 0, 0 }, bsp::asg::drv::SPI>;								///< SPI A onboard only

		static constexpr auto& SPIACE = GPIOPortI::Pin<0>;												///< SPI A chip enable
		static constexpr auto& SK9822_EN = GPIOPortE::Pin<10>;											///< SPI A chip enable for SK9822 RGB LEDs
		/** @} */

		/**
		 * @brief Display definitions
		 * @{
		 */
		using Display = bsp::drv::Display<0, bsp::asg::drv::Display>;									///< LCD Display
		/** @} */

	}

#endif
