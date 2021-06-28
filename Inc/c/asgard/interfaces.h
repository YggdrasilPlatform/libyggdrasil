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
  *  @file cpp/asgard/interfaces.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Interface definitions for Asgard
  */

#pragma once

#include <c/asgard/core/cortex.h>

#include <c/asgard/driver/gpio.h>
#include <c/asgard/driver/i2c.h>
#include <c/asgard/driver/display.h>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	/**
	 * @brief User LEDs and buttons definitions
	 * @{
	 */
	const static gpio_t LD1 = { 144 };									///< Alias for LDA
	const static gpio_t LDA = LD1;										///< LDA
	const static gpio_t LedBlue = LD1;									///< Alias for LDA
	const static gpio_t LD2 = { 145 };									///< Alias for LDB
	const static gpio_t LDB = LD2;										///< LDB
	const static gpio_t LedRed = LD2;									///< Alias for LDB
	const static gpio_t LD3 = { 146 };									///< Alias for LDC
	const static gpio_t LDC = LD3;										///< LDC
	const static gpio_t LedYellow = LD3;								///< Alias for LDC
	const static gpio_t LD4 = { 147 };									///< Alias for LDD
	const static gpio_t LDD = LD4;										///< LDD
	const static gpio_t LedGreen = LD4;									///< Alias for LDD

	const static gpio_t EncoderButton  = { 65, LOW_ACTIVE };			///< Encoder Button

	const static gpio_t LeftJoyStickButton = { 73, LOW_ACTIVE };		///< JoystickA Button
	const static gpio_t ButtonJoystickA = LeftJoyStickButton;			///< JoystickA Button
	const static gpio_t RightJoyStickButton = { 71, LOW_ACTIVE };		///< JoystickB Button
	const static gpio_t ButtonJoystickB = RightJoyStickButton;			///< JoystickB Button

	const static gpio_t ButtonA = { 148, LOW_ACTIVE };					///< Button A
	const static gpio_t ButtonB = { 149, LOW_ACTIVE };					///< Button B
	const static gpio_t ButtonC = { 150, LOW_ACTIVE };					///< Button C
	const static gpio_t ButtonD = { 151, LOW_ACTIVE };					///< Button D

	const static gpio_t DriverA = { 19 };								///< Sink driver pin A
	const static gpio_t LD5 = DriverA;									///< Alias for Sink driver pin A
	const static gpio_t LDE = DriverA;									///< Alias for Sink driver pin A
	const static gpio_t DriverB = { 20 };								///< Sink driver pin B
	const static gpio_t LD6 = DriverB;									///< Alias for Sink driver pin B
	const static gpio_t LDF = DriverB;									///< Alias for Sink driver pin B
	const static gpio_t DriverC = { 30 };								///< Sink driver pin C
	const static gpio_t LD7 = DriverC;									///< Alias for Sink driver pin C
	const static gpio_t LDG = DriverC;									///< Alias for Sink driver pin C
	const static gpio_t DriverD = { 31 };								///< Sink driver pin D
	const static gpio_t LD8 = DriverD;									///< Alias for Sink driver pin D
	const static gpio_t LDH = DriverD;									///< Alias for Sink driver pin D
	/** @} */

	/**
	 * @brief 7-Segment definitions
	 * @{
	 */
	const static gpio_t SevenSegment_A  = { 160 };						///< 7-Segment segment A
	const static gpio_t SevenSegment_B  = { 161 };						///< 7-Segment segment B
	const static gpio_t SevenSegment_C  = { 162 };						///< 7-Segment segment C
	const static gpio_t SevenSegment_D  = { 163 };						///< 7-Segment segment D
	const static gpio_t SevenSegment_E  = { 164 };						///< 7-Segment segment E
	const static gpio_t SevenSegment_F  = { 165 };						///< 7-Segment segment F
	const static gpio_t SevenSegment_G  = { 166 };						///< 7-Segment segment G
	const static gpio_t SevenSegment_DP = { 167 };						///< 7-Segment segment DP

	const static gpio_t SevenSegment_Select0 = { 140 };					///< 7-Segment enable pin 0
	const static gpio_t SevenSegment_Select1 = { 141 };					///< 7-Segment enable pin 1
	const static gpio_t SevenSegment_Select2 = { 142 };					///< 7-Segment enable pin 2
	const static gpio_t SevenSegment_Select3 = { 143 };					///< 7-Segment enable pin 3
	/** @} */

	/**
	 * @brief SPI chip enable definitions
	 * @{
	 */
	const static gpio_t SPIACE = { 128, LOW_ACTIVE };					///< SPI A chip enable
	const static gpio_t SK9822_EN = { 74 };								///< SPI A chip enable for SK9822 RGB LEDs
	const static gpio_t SPIBCE = { 85, LOW_ACTIVE };					///< SPI B chip enable
	const static gpio_t SPICCE = { 117, LOW_ACTIVE };					///< SPI C chip enable
	/** @} */

	/**
	 * @brief Motor driver control pin definitions
	 * @{
	 */
	const static gpio_t TC78Mode = { 83 };								///< Motor driver mode pin
	const static gpio_t TC78Err  = { 105 };								///< Motor driver error pin
	const static gpio_t TC78Stby = { 138 };								///< Motor driver standby pin
	/** @} */

	/**
	 * @brief I2C definitions
	 * @{
	 */
	const static i2c_t I2CA = { 1 };									///< I2CA on board Sensors, Seeed, Raspberry, PMod
	const static i2c_t I2CB = { 3 };									///< I2CB Seeed, Raspberry, PMod
	const static i2c_t I2CC = { 4 };									///< I2CC Touch screen
	const static i2c_t I2CD = { 0 };									///< I2CD DCMI, USB C and USB Hub (NC), Audio Codec
	/** @} */


	#endif
