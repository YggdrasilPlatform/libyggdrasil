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
  *  @file cpp/yggdrasil/peripherals/humidity_sensor.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the SHT40-AD1B-R2 humidity sensor
  */

#pragma once

#include <cpp/common/attributes.hpp>
#include <cpp/common/types.hpp>
#include <cpp/common/utils.hpp>

namespace bsp::ygg::prph {

	/**
	 * @brief Humidity sensor SHT40-AD1B-R2 driver
	 */
	class HumiditySensor {
	public:
		HumiditySensor() = delete;

		/**
		 * @brief Heater commands for the SHT40-AD1B-R2 sensor
		 * @warning Do not use heater for extended periods of time. The heater is designed for a maximal duty cycle of less than 5% when it is periodically heated
		 */
		enum class Heat : u8 {
			_200mWFor1s	 	= 0x39,		///< 200mW @ 3.3V for 1s
			_200mWFor0p1s 	= 0x32,		///< 200mW @ 3.3V for 0.1s
			_110mWFor1s	 	= 0x2F,		///< 110mW @ 3.3V for 1s
			_110mWFor0p1s 	= 0x24,		///< 110mW @ 3.3V for 0.1s
			_20mWFor1s	 	= 0x1E,		///< 20mW @ 3.3V for 1s
			_20mWFor0p1s	= 0x15,		///< 20mW @ 3.3V for 0.1s
		};

		enum class Precision : u8 {
			High 	 	= 0xFD,		///< measure T & RH with High precision (High repeatability)
			Medium  	= 0xF6,		///< measure T & RH with medium precision (medium repeatability)
			Low 		= 0xE0,		///< measure T & RH with lowest precision (low repeatability)
		};

		/**
		 * @brief Initialization of the SHT40-AD1B-R2 relative humidity and temperature sensor
		 * @note The sensor does not need a special initialization, this function just does a soft reset
		 *
		 * @return Success
		 */
		static bool init() {
			bsp::I2CA::write(DeviceAddress, enumValue(Command::SoftReset));
			core::delay(2);
			return true;
		}

		/**
		 * @brief Get the temperature without using the heater
		 * @note The measurement takes about 10ms
		 *
		 * @param precision Precision for the conversion
		 * @return Temperature sensor temperature
		 */
		static float getTemperature(Precision precision = Precision::High){
			return getSensorData(precision).sensorTemperature;
		}

		/**
		 * @brief Get the temperature without using the heater
		 * @note The measurement takes about 10ms
		 *
		 * @param precision Precision for the conversion
		 * @return Temperature sensor temperature
		 */
		static float getHumidity(Precision precision = Precision::High){
			return getSensorData(precision).humidity;
		}

		/**
		 * @brief Enable the heater module on the sensor
		 * @warning The heater is designed for a maximal duty cycle of less than 5% when it is periodically heated
		 *
		 * @param level Power and duration command
		 */
		static void enableHeater(Heat level) {
			bsp::I2CA::write(DeviceAddress, enumValue(level));
		}

	private:

		/**
		 * @brief Sensor data
		 */
		struct SensorData{
			float humidity;				///< Humidity sensor value
			float sensorTemperature;	///< Temperature of the sensor
		};

		/**
		 * @brief Get a measurement without using the heater
		 * @note The measurement takes about 10ms
		 *
		 * @param precision Precision for the conversion
		 * @return SensorData struct containing the humidity value in % and the sensor temperature
		 */
		static SensorData getSensorData(Precision precision = Precision::High) {
			bsp::I2CA::write(DeviceAddress, enumValue(precision));
			core::delay(10);										// Delay until the measurement is done, there is no other option

			auto rawData = bsp::I2CA::read<SensorDataRaw>(DeviceAddress);

			SensorData data;
			data.sensorTemperature = -45 + 175 * float((u16(rawData.th) << 8) | rawData.tl) / 0xFFFF;
			data.humidity = -6 + 125 * float((u16(rawData.rhh) << 8) | rawData.rhl) / 0xFFFF;

			if (data.humidity > 100) data.humidity = 100;
			else if(data.humidity < 0) data.humidity = 0;

			return data;

		}

		/**
		 * @brief Raw sensor data
		 */
		struct SensorDataRaw {
			u8 th;			///< Temperature high byte
			u8 tl;			///< Temperature low byte
			u8 tcrc8;		///< Temperature crc8 checksum
			u8 rhh;			///< Relative humidity high byte
			u8 rhl;			///< Relative humidity low byte
			u8 rhcrc8;		///< Relative humidity crc8 checksum
		};

		/**
		 * @brief Commands for the SHT40-AD1B-R2 sensor
		 */
		enum class Command : u8 {
			ReadSerial = 0x89,		///< every single sensor has a unique serial number
			SoftReset  = 0x94,		///< Soft reset
		};

		constexpr static inline u8 DeviceAddress = 0x88;		///< I2C device address

	};

}
