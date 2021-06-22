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
  *  @file init.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Initialization file for yggdrasil
  */

enum {
	INITRESULT_SUCCESS,
	INITRESULT_ADC_FAILURE,
	INITRESULT_CAN_FAILURE,
	INITRESULT_DAC_FAILURE,
	INITRESULT_DISPLAY_FAILURE,
	INITRESULT_GPIO_FAILURE,
	INITRESULT_HASH_FAILURE,
	INITRESULT_I2C_FAILURE,
	INITRESULT_RNG_FAILURE,
	INITRESULT_SPI_FAILURE,
	INITRESULT_TIMER_FAILURE,
	INITRESULT_UART_FAILURE,
	INITRESULT_COLORSENSOR_FAILURE,
	INITRESULT_HUMIDITYSENSOR_FAILURE,
	INITRESULT_JOYSTICK_FAILURE,
	INITRESULT_MOTORDRIVER_FAILURE,
	INITRESULT_PRESSURESENSOR_FAILURE,
	INITRESULT_RGBMATRIX_FAILURE,
	INITRESULT_RTC_FAILURE,
	INITRESULT_SEVENSEGMENT_FAILURE,
	INITRESULT_SINKDRIVER_FAILURE,
	INITRESULT_SIXAXISSENSOR_FAILURE,

};

C_LINKAGE i8 bsp_init();



