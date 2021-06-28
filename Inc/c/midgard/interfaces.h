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
#include <c/midgard/driver/uart.h>
#include <c/midgard/driver/timer.h>
#include <c/midgard/driver/display.h>
#include <c/midgard/driver/hash.h>
#include <c/midgard/driver/rng.h>

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

	extern UART_HandleTypeDef huart4;
	extern UART_HandleTypeDef huart8;
	extern UART_HandleTypeDef huart2;
	/** @} */


	/**
	 * @brief User LEDs and buttons definitions
	 * @{
	 */
	const static gpio_t LD1 = { GPIOJ, 0 };									///< Alias for LDA
	const static gpio_t LDA = LD1;											///< LDA
	const static gpio_t LedBlue = LD1;										///< Alias for LDA
	const static gpio_t LD2 = { GPIOJ, 1 };									///< Alias for LDB
	const static gpio_t LDB = LD2;											///< LDB
	const static gpio_t LedRed = LD2;										///< Alias for LDB
	const static gpio_t LD3 = { GPIOJ, 2 };									///< Alias for LDC
	const static gpio_t LDC = LD3;											///< LDC
	const static gpio_t LedYellow = LD3;									///< Alias for LDC
	const static gpio_t LD4 = { GPIOJ, 3 };									///< Alias for LDD
	const static gpio_t LDD = LD4;											///< LDD
	const static gpio_t LedGreen = LD4;										///< Alias for LDD

	const static gpio_t Heartbeat = { GPIOA, 10 };							///< Heartbeat led

	const static gpio_t EncoderButton  = { GPIOK, 3, LOW_ACTIVE };			///< Encoder Button

	const static gpio_t LeftJoyStickButton = { GPIOG, 10, LOW_ACTIVE };		///< JoystickA Button
	const static gpio_t ButtonJoystickA = LeftJoyStickButton;				///< JoystickA Button
	const static gpio_t RightJoyStickButton = { GPIOG, 11, LOW_ACTIVE };	///< JoystickB Button
	const static gpio_t ButtonJoystickB = RightJoyStickButton;				///< JoystickB Button

	const static gpio_t ButtonA = { GPIOK, 4, LOW_ACTIVE };					///< Button A
	const static gpio_t ButtonB = { GPIOK, 5, LOW_ACTIVE };					///< Button B
	const static gpio_t ButtonC = { GPIOK, 6, LOW_ACTIVE };					///< Button C
	const static gpio_t ButtonD = { GPIOK, 7, LOW_ACTIVE };					///< Button D

	const static gpio_t DriverA = { GPIOC, 13 };							///< Sink driver pin A
	const static gpio_t LD5 = DriverA;										///< Alias for Sink driver pin A
	const static gpio_t LDE = DriverA;										///< Alias for Sink driver pin A
	const static gpio_t DriverB = { GPIOI, 8 };								///< Sink driver pin B
	const static gpio_t LD6 = DriverB;										///< Alias for Sink driver pin B
	const static gpio_t LDF = DriverB;										///< Alias for Sink driver pin B
	const static gpio_t DriverC = { GPIOB, 0 };								///< Sink driver pin C
	const static gpio_t LD7 = DriverC;										///< Alias for Sink driver pin C
	const static gpio_t LDG = DriverC;										///< Alias for Sink driver pin C
	const static gpio_t DriverD = { GPIOB, 1 };								///< Sink driver pin D
	const static gpio_t LD8 = DriverD;										///< Alias for Sink driver pin D
	const static gpio_t LDH = DriverD;										///< Alias for Sink driver pin D
	/** @} */

	/**
	 * @brief ADC channel definitions
	 * @{
	 */
	const static adc_t ADCA = { &hadc1, 3,  0, 1 << 12 };					///< ADCA on Analog header
	const static adc_t ADCB = { &hadc1, 10, 0, 1 << 12 };					///< ADCB on Analog header
	const static adc_t ADCC = { &hadc3, 14, 0, 1 << 12 };					///< ADCC on Analog header
	const static adc_t ADCD = { &hadc3, 15, 0, 1 << 12 };					///< ADCD on Analog header
	const static adc_t ADCPotentiometer = { &hadc2, 13, 0, 1 << 12 };		///< Potentiometer
	const static adc_t ADCTemperature = { &hadc1, 18, 0, 1 << 12 };			///< Internal temperature sensor
	/** @} */

	/**
	 * @brief DAC channel definitions
	 * @{
	 */
	const static dac_t  DACA = { &hdac, 1, 0, 1 << 12 };					///< DACA on Analog header
	const static dac_t  DACB = { &hdac, 2, 0, 1 << 12 };					///< DACB on Analog header
	/** @} */

	/**
	 * @brief 7-Segment definitions
	 * @{
	 */
	const static gpio_t SevenSegment_A  = { GPIOG, 0 };						///< 7-Segment segment A
	const static gpio_t SevenSegment_B  = { GPIOG, 1 };						///< 7-Segment segment B
	const static gpio_t SevenSegment_C  = { GPIOG, 2 };						///< 7-Segment segment C
	const static gpio_t SevenSegment_D  = { GPIOG, 3 };						///< 7-Segment segment D
	const static gpio_t SevenSegment_E  = { GPIOG, 4 };						///< 7-Segment segment E
	const static gpio_t SevenSegment_F  = { GPIOG, 5 };						///< 7-Segment segment F
	const static gpio_t SevenSegment_G  = { GPIOG, 6 };						///< 7-Segment segment G
	const static gpio_t SevenSegment_DP = { GPIOG, 7 };						///< 7-Segment segment DP

	const static gpio_t SevenSegment_Select0 = { GPIOJ, 12 };				///< 7-Segment enable pin 0
	const static gpio_t SevenSegment_Select1 = { GPIOJ, 13 };				///< 7-Segment enable pin 1
	const static gpio_t SevenSegment_Select2 = { GPIOJ, 14 };				///< 7-Segment enable pin 2
	const static gpio_t SevenSegment_Select3 = { GPIOJ, 15 };				///< 7-Segment enable pin 3
	/** @} */

	/**
	 * @brief I2C definitions
	 * @{
	 */
	const static i2c_t I2CA = { &hi2c2 };									///< I2CA on board Sensors, Seeed, Raspberry, PMod
	const static i2c_t I2CB = { &hi2c4 };									///< I2CB Seeed, Raspberry, PMod
	const static i2c_t I2CC = { &hi2c3 };									///< I2Cc Touch sensor
	const static i2c_t I2CD = { &hi2c1 };									///< I2CD DCMI, USB C and USB Hub (NC), Audio Codec
	/** @} */

	/**
	 * @brief SPI definitions
	 * @{
	 */
	const static spi_t SPIA = { &hspi2 };									///< SPI A onboard only
	const static spi_t SPIB = { &hspi4 };									///< SPI B on Raspberry
	const static spi_t SPIC = { &hspi5 };									///< SPI C on Raspberry, PMod

	const static gpio_t SPIACE = { GPIOI, 0, LOW_ACTIVE };					///< SPI A chip enable
	const static gpio_t SK9822_EN = { GPIOD, 9 };							///< SPI A chip enable for SK9822 RGB LEDs
	const static gpio_t SPIBCE = { GPIOE, 11, LOW_ACTIVE };					///< SPI B chip enable
	const static gpio_t SPICCE = { GPIOH, 5, LOW_ACTIVE };					///< SPI C chip enable
	/** @} */

	/**
	 * @brief UART definitions
	 * @{
	 */
	const static uart_t UARTA = { &huart2 };								///< USART 2 on Raspberry, PMod
	const static uart_t UARTB = { &huart8 };								///< UART 8 on Raspberry, PMod
	const static uart_t UARTC = { &huart4 };								///< UART 4 onboard to STLINK-V3
	const static uart_t UASRTST = UARTC;									///< UART ST onboard to STLINK-V3
	/** @} */

	/**
	 * @brief CAN definitions
	 * @{
	 */
	const static can_t CANA = { &hcan1 };									///< CAN A
	const static can_t CANB = { &hcan2 };									///< CAN B
	/** @} */

	/**
	 * @brief Timer definitions
	 * @{
	 */
	const static tim_t TimerA = { &htim12, sizeof(u16) };					///< PWM on Raspberry / PMod
	const static tim_t TimerB = { &htim4, sizeof(u16) };					///< PWM on Motor Driver / Raspberry / PMod
	const static tim_t TimerC = { &htim5, sizeof(u32) };					///< PWM on Raspberry / PMod
	const static tim_t TimerD = { &htim3, sizeof(u16) };					///< PWM on Sink Driver
	const static tim_t TimerE = { &htim11, sizeof(u16) };					///< PWM for LCD Backlight Control
	const static tim_t TimerF = { &htim8, sizeof(u16) };					///< Encoder
	const static tim_t TimerG = { &htim2, sizeof(u32) };					///< Profile Counter

	const static tim_t SinkDriverTimerA = TimerD;							///< Timer for sink driver A
	const static tim_t SinkDriverTimerB = TimerD;							///< Timer for sink driver B
	const static tim_t SinkDriverTimerC = TimerD;							///< Timer for sink driver C
	const static tim_t SinkDriverTimerD = TimerD;							///< Timer for sink driver D
	/** @} */

	/**
	 * @brief Timer channel definitions
	 * @{
	 */
	const static tim_channel_t TimerACHA = { TimerA, 1 };					///< PMod A Pin 2 / Raspberry Pin 33

	const static tim_channel_t TimerBCHA = { TimerB, 1 };					///< Motor Driver / Raspberry Pin 26
	const static tim_channel_t TimerBCHB = { TimerB, 2 };					///< Motor Driver / Raspberry Pin 28
	const static tim_channel_t TimerBCHC = { TimerB, 3 };					///< Motor Driver / PMod B Pin 2 / Raspberry Pin 32
	const static tim_channel_t TimerBCHD = { TimerB, 4 };					///< Motor Driver / Raspberry Pin 36

	const static tim_channel_t TimerCCHA = { TimerC, 1 };					///< PMod A Pin 4 / Raspberry Pin 27

	const static tim_channel_t TimerDCHA = { SinkDriverTimerA, 2 };			///< Sink driver A
	const static tim_channel_t TimerDCHB = { SinkDriverTimerB, 1 };			///< Sink driver B
	const static tim_channel_t TimerDCHC = { SinkDriverTimerC, 3 };			///< Sink driver C
	const static tim_channel_t TimerDCHD = { SinkDriverTimerD, 4 };			///< Sink driver D

	const static tim_t Encoder = TimerF;									///< Encoder

	const static tim_t ProfileCounter = TimerG;								///< Profilecounter
	/** @} */

	/**
	 * @brief Motor driver control pin definitions
	 * @{
	 */
	const static gpio_t TC78Mode = { GPIOI, 12 };							///< Motor driver mode pin
	const static gpio_t TC78Err  = { GPIOI, 13, LOW_ACTIVE };				///< Motor driver error pin
	const static gpio_t TC78Stby = { GPIOI, 14, LOW_ACTIVE };				///< Motor driver standby pin
	/** @} */

	/**
	 * @brief Random hardware acceleration definitions
	 * @{
	 */
	const static rng_t Random = { };										///< RNG hardware
	/** @} */

	#endif
