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
  *  @file c/yggdrasil/peripherals/six_axis_sensor.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the ICM-42605 Six Axis Sensor
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Coordinates
 */
struct Coordinate {
	float x, y, z;
};

/**
 * @brief Absolute board orientation
 */
struct Orientation {
	float roll;		///< Rotation around x-axis
	float pitch;	///< Rotation around y-axis
};

/**
 * @brief Accelerometer range
 */
enum SixAxisSensorAccelFullScaleRange {
	SixAxisSensorAccelFullScaleRange_2G = 0x03,		///< Range from -2G to 2G with highest precision
	SixAxisSensorAccelFullScaleRange_4G = 0x02,		///< Range from -4G to 4G
	SixAxisSensorAccelFullScaleRange_8G = 0x01,		///< Range from -8G to 8G
	SixAxisSensorAccelFullScaleRange_16G = 0x00		///< Range from -16G to 16G with lowest precision
};

/**
 * @brief Gyroscope range
 * @note DPS = degree per second
 */
enum SixAxisSensorGyroFullScaleRange {
	SixAxisSensorGyroFullScaleRange_2000DPS   = 0x00,	///< Range from -2000DPS to 2000DPS with lowest precision
	SixAxisSensorGyroFullScaleRange_1000DPS   = 0x01,	///< Range from -1000DPS to 1000DPS
	SixAxisSensorGyroFullScaleRange_500DPS    = 0x02,	///< Range from -500DPS to 500DPS
	SixAxisSensorGyroFullScaleRange_250DPS    = 0x03,	///< Range from -250DPS to 250DPS
	SixAxisSensorGyroFullScaleRange_125DPS    = 0x04,	///< Range from -125DPS to 125DPS
	SixAxisSensorGyroFullScaleRange_62_5DPS   = 0x05,	///< Range from -62.5DPS to 65.5DPS
	SixAxisSensorGyroFullScaleRange_31_25DPS  = 0x06,	///< Range from -31.25DPS to 31.25DPS
	SixAxisSensorGyroFullScaleRange_15_125DPS = 0x07	///< Range from -15.125DPS to 15.125DPS with highest precision
};

/**
 * @brief Accelerometer data rate
 */
enum SixAxisSensorAccelOutputDataRange {
	SixAxisSensorAccelOutputDataRange_8000Hz   = 0x03,	///< 8000 measurements per second
	SixAxisSensorAccelOutputDataRange_4000Hz   = 0x04,	///< 4000 measurements per second
	SixAxisSensorAccelOutputDataRange_2000Hz   = 0x05,	///< 2000 measurements per second
	SixAxisSensorAccelOutputDataRange_1000Hz   = 0x06,	///< 1000 measurements per second
	SixAxisSensorAccelOutputDataRange_500Hz    = 0x0F,	///< 500 measurements per second
	SixAxisSensorAccelOutputDataRange_200Hz    = 0x07,	///< 200 measurements per second
	SixAxisSensorAccelOutputDataRange_100Hz    = 0x08,	///< 100 measurements per second
	SixAxisSensorAccelOutputDataRange_50Hz     = 0x09,	///< 50 measurements per second
	SixAxisSensorAccelOutputDataRange_25Hz     = 0x0A,	///< 25 measurements per second
	SixAxisSensorAccelOutputDataRange_12_5Hz   = 0x0B,	///< 12.5 measurements per second
	SixAxisSensorAccelOutputDataRange_6_25Hz   = 0x0C,	///< 6.25 measurements per second
	SixAxisSensorAccelOutputDataRange_3_125Hz  = 0x0D,	///< 3.125 measurements per second
	SixAxisSensorAccelOutputDataRange_1_5625Hz = 0x0E	///< 1.5625 measurements per second
};

/**
 * @brief Gyroscope data rate
 */
enum SixAxisSensorGyroOutputDataRange {
	SixAxisSensorGyroOutputDataRange_8000Hz   = 0x03,	///< 8000 measurements per second
	SixAxisSensorGyroOutputDataRange_4000Hz   = 0x04,	///< 4000 measurements per second
	SixAxisSensorGyroOutputDataRange_2000Hz   = 0x05,	///< 2000 measurements per second
	SixAxisSensorGyroOutputDataRange_1000Hz   = 0x06,	///< 1000 measurements per second
	SixAxisSensorGyroOutputDataRange_500Hz    = 0x0F,	///< 500 measurements per second
	SixAxisSensorGyroOutputDataRange_200Hz    = 0x07,	///< 200 measurements per second
	SixAxisSensorGyroOutputDataRange_100Hz    = 0x08,	///< 100 measurements per second
	SixAxisSensorGyroOutputDataRange_50Hz     = 0x09,	///< 50 measurements per second
	SixAxisSensorGyroOutputDataRange_25Hz     = 0x0A,	///< 25 measurements per second
	SixAxisSensorGyroOutputDataRange_12_5Hz   = 0x0B,	///< 12.5 measurements per second
};

C_LINKAGE bool yggdrasil_SixAxisSensor_Init(enum SixAxisSensorAccelFullScaleRange accelScale, enum SixAxisSensorGyroFullScaleRange gyroScale, enum SixAxisSensorAccelOutputDataRange accelOdr, enum SixAxisSensorGyroOutputDataRange gyroOdr);
C_LINKAGE struct Coordinate yggdrasil_SixAxisSensor_GetRotation();
C_LINKAGE struct Coordinate yggdrasil_SixAxisSensor_GetAcceleration();
C_LINKAGE float yggdrasil_SixAxisSensor_GetTemperature();
C_LINKAGE struct Orientation yggdrasil_SixAxisSensor_GetBoardOrientation();


