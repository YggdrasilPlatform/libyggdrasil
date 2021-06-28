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
	ColorSensorIntegrationTime_2_4ms 	= 0xFF, ///<  2.4ms - 1 cycle
	ColorSensorIntegrationTime_10ms		= 0xFB, ///<  10ms	- 4 cycles
	ColorSensorIntegrationTime_24ms 	= 0xF6, ///<  24ms  - 10 cycles
	ColorSensorIntegrationTime_50ms 	= 0xEB, ///<  50ms  - 20 cycles
	ColorSensorIntegrationTime_101ms	= 0xD5,	///<  101ms - 42 cycles
	ColorSensorIntegrationTime_154ms 	= 0xC0, ///<  154ms - 64 cycles
	ColorSensorIntegrationTime_700ms 	= 0x00 	///<  700ms - 256 cycles
};

/**
 * @brief Gain settings
 */
enum ColorSensorGain {
	ColorSensorGain_1x 		= 0x00, ///<  No gain
	ColorSensorGain_4x 		= 0x01, ///<  4x gain
	ColorSensorGain_16x 	= 0x02, ///<  16x gain
	ColorSensorGain_60x 	= 0x03  ///<  60x gain
};

/**
 * @brief Initialization of the TCS3472 color sensor
 * @note This function does start a conversion. Values for integration time (2.4ms) and gain (1x) are set
 *
 * @return True when the connected device matched the device id, false when not
 */
C_LINKAGE bool yggdrasil_ColorSensor_Init(void);

/**
 * @brief Set the integration time
 * @note Integration time = (256 - IntegrationTime) * 2.4ms
 *
 * @param integrationTime Integration time value
 */
C_LINKAGE void yggdrasil_ColorSensor_SetIntegrationTime(enum ColorSensorIntegrationTime integrationTime);

/**
 * @brief Set the gain
 * @note value can be 1x, 4x, 16x and 60x
 *
 * @param gain Gain value
 */
C_LINKAGE void yggdrasil_ColorSensor_SetGain(enum ColorSensorGain gain);

/**
 * @brief Enable the sensor
 * @note This function does not start a conversion
 */
C_LINKAGE void yggdrasil_ColorSensor_Enable(void);

/**
 * @brief Disables the sensor
 */
C_LINKAGE void yggdrasil_ColorSensor_Disable(void);

/**
 * @brief Start a conversion and returns the set integration time
 *
 * @return integration time in ms
 */
C_LINKAGE u16  yggdrasil_ColorSensor_StartConversion(void);

/**
 * @brief Used to poll a conversion
 *
 * @return True when the conversion is finished, false when not
 */
C_LINKAGE bool yggdrasil_ColorSensor_IsDone(void);

/**
 * @brief Get the color values and start a new measurement (optional)
 * @note The integration time must be passed since the last read
 *
 * @param restartConversion Restart a measurement after reading with the same setting
 * @return Color RGBA8 value
 */
C_LINKAGE RGBA8  yggdrasil_ColorSensor_GetColor8(bool restartConversion);

/**
 * @brief Get the color values and start a new measurement (optional)
 * @note The integration time must be passed since the last read
 *
 * @param restartConversion Restart a measurement after reading with the same setting
 * @return Color RGB and brightness value (all 16 Bit)
 */
C_LINKAGE RGBA16 yggdrasil_ColorSensor_GetColor16(bool restartConversion);
