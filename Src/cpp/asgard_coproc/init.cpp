 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Yggdrasil -                           *
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
  *  @file cpp/midgard/midgard/init.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Hardware initialization for midgard
  */


#include <yggdrasil.h>

#if BOARD == ASGARD_COPROC

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	C_LINKAGE init_result_t yggdrasil_init() {


		using namespace bsp;
		using namespace bsp::ygg::prph;

		gpio_config();

		/* GPIO initialization */
		if (!GPIOPortA::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortB::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortC::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortD::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortE::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortF::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortG::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortH::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortI::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortJ::init())
			return INITRESULT_GPIO_FAILURE;
		if (!GPIOPortK::init())
			return INITRESULT_GPIO_FAILURE;

		/* ADC initialization */
		if (!ADCA.init())
			return INITRESULT_ADC_FAILURE;
		if (!ADCB.init())
			return INITRESULT_ADC_FAILURE;
		if (!ADCC.init())
			return INITRESULT_ADC_FAILURE;
		if (!ADCD.init())
			return INITRESULT_ADC_FAILURE;
		if (!ADCPotentiometer.init())
			return INITRESULT_ADC_FAILURE;
		if (!ADCTemperature.init())
			return INITRESULT_ADC_FAILURE;

		/* DAC initialization */
		if (!DACA.init())
			return INITRESULT_DAC_FAILURE;
		if (!DACB.init())
			return INITRESULT_DAC_FAILURE;

		/* CAN initialization */
		if (!CANA::init())
			return INITRESULT_CAN_FAILURE;
		if (!CANB::init())
			return INITRESULT_CAN_FAILURE;

		/* I2C initialization */
		if (!I2CA::init())
			return INITRESULT_I2C_FAILURE;
		if (!I2CB::init())
			return INITRESULT_I2C_FAILURE;
		if (!I2CD::init())
			return INITRESULT_I2C_FAILURE;

		/* SPI initialization */
		if (!SPIA::init())
			return INITRESULT_SPI_FAILURE;
		if (!SPIB::init())
			return INITRESULT_SPI_FAILURE;
		if (!SPIC::init())
			return INITRESULT_SPI_FAILURE;

		/* Timer initialization */
		if (!TimerA::init())
			return INITRESULT_TIMER_FAILURE;
		if (!TimerB::init())
			return INITRESULT_TIMER_FAILURE;
		if (!TimerC::init())
			return INITRESULT_TIMER_FAILURE;
		if (!TimerD::init())
			return INITRESULT_TIMER_FAILURE;
		if (!TimerE::init())
			return INITRESULT_TIMER_FAILURE;
		if (!TimerF::init())
			return INITRESULT_TIMER_FAILURE;
		if (!TimerG::init())
			return INITRESULT_TIMER_FAILURE;

		/* UART initialization */
		if (!UARTA::init())
			return INITRESULT_UART_FAILURE;
		if (!UARTB::init())
			return INITRESULT_UART_FAILURE;
		if (!UARTC::init())
			return INITRESULT_UART_FAILURE;

		/* Hash initialization */
		if (!Hash::init())
			return INITRESULT_HASH_FAILURE;

		/* RNG initialization */
		if (!Random::init())
			return INITRESULT_RNG_FAILURE;


		/* Yggdrasil's peripheral initialization */

		/* Color sensor initialization */
		if (!ColorSensor::init())
			return INITRESULT_COLORSENSOR_FAILURE;

		/* Humidity initialization */
		if (!HumiditySensor::init())
			return INITRESULT_HUMIDITYSENSOR_FAILURE;

		/* Joystick initialization */
		if (!Joystick::init())
			return INITRESULT_JOYSTICK_FAILURE;

		/* Motor driver initialization */
		if (!MotorDriver::init())
			return INITRESULT_MOTORDRIVER_FAILURE;

		/* Pressure sensor initialization */
		if (!PressureSensor::init())
			return INITRESULT_PRESSURESENSOR_FAILURE;

		/* RGB matrix initialization */
		if (!RGBMatrix::init())
			return INITRESULT_RGBMATRIX_FAILURE;

		/* RTC initialization */
		if (!RealTimeClock::init())
			return INITRESULT_RTC_FAILURE;

		/* 7 Segment initialization */
		if (!SevenSegment::init())
			return INITRESULT_SEVENSEGMENT_FAILURE;

		/* Sink driver initialization */
		if (!SinkDriver::init())
			return INITRESULT_SINKDRIVER_FAILURE;

		/* 6-Axis initialization */
		if (!SixAxisSensor::init())
			return INITRESULT_SIXAXISSENSOR_FAILURE;

		return INITRESULT_SUCCESS;

	}

	static void gpio_config() {


		GPIO_InitTypeDef GPIO_InitStruct = {0};


		GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

	}


#endif

