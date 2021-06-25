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
  *  @file cpp/midgard/asgard/init.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Hardware initialization for asgard
  */

#include <yggdrasil.h>

#if BOARD == ASGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	C_LINKAGE i8 bsp_init() {

		using namespace bsp;
		using namespace bsp::ygg::prph;

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

		/* DAC initialization */
		if (!DACA.init())
			return INITRESULT_DAC_FAILURE;
		if (!DACB.init())
			return INITRESULT_DAC_FAILURE;

		/* I2C initialization */
		if (!I2CA::init())
			return INITRESULT_I2C_FAILURE;
		if (!I2CB::init())
			return INITRESULT_I2C_FAILURE;
		if (!I2CC::init())
			return INITRESULT_I2C_FAILURE;
		if (!I2CD::init())
			return INITRESULT_I2C_FAILURE;

		/* SPI initialization */
		if (!SPIA::init())
			return INITRESULT_SPI_FAILURE;

		/* Display initialization */
		if (!Display::init())
			return INITRESULT_DISPLAY_FAILURE;


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

		/* Pressure sensor initialization */
		if (!PressureSensor::init())
			return INITRESULT_PRESSURESENSOR_FAILURE;

		/* RGB matrix initialization */
		if (!RGBMatrix::init())
			return INITRESULT_RGBMATRIX_FAILURE;

		/* RTC initialization */
		if (!RealTimeClock::init())
			return INITRESULT_RTC_FAILURE;

		/* 6-Axis initialization */
		if (!SixAxisSensor::init())
			return INITRESULT_SIXAXISSENSOR_FAILURE;

		return INITRESULT_SUCCESS;

	}

#endif
