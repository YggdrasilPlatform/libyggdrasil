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
  *  @file c/yggdrasil/peripherals/color_sensor.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the TCS3472 color sensor
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Integration time = (256 - IntegrationTime) * 2.4ms
 */
enum ColorSensorIntegrationTime {
	_2_4ms 	= 0xFF, ///<  2.4ms - 1 cycle
	_10ms	= 0xFB, ///<  10ms	- 4 cycles
	_24ms 	= 0xF6, ///<  24ms  - 10 cycles
	_50ms 	= 0xEB, ///<  50ms  - 20 cycles
	_101ms	= 0xD5,	///<  101ms - 42 cycles
	_154ms 	= 0xC0, ///<  154ms - 64 cycles
	_700ms 	= 0x00 	///<  700ms - 256 cycles
};

/**
 * @brief Gain settings
 */
enum ColorSensorGain {
	_1x 	= 0x00, ///<  No gain
	_4x 	= 0x01, ///<  4x gain
	_16x 	= 0x02, ///<  16x gain
	_60x 	= 0x03  ///<  60x gain
};

C_LINKAGE bool yggdrasil_ColorSensor_init(void);
C_LINKAGE void yggdrasil_ColorSensor_setIntegrationTime(ColorSensorIntegrationTime integrationTime);
C_LINKAGE void yggdrasil_ColorSensor_setGain(ColorSensorGain gain);
C_LINKAGE void yggdrasil_ColorSensor_enable(void);
C_LINKAGE void yggdrasil_ColorSensor_disable(void);
C_LINKAGE u16  yggdrasil_ColorSensor_startConversion(void);
C_LINKAGE bool yggdrasil_ColorSensor_isDone(void);
C_LINKAGE RGBA8  yggdrasil_ColorSensor_getColor8(bool restartConversion);
C_LINKAGE RGBA16 yggdrasil_ColorSensor_getColor16(bool restartConversion);
