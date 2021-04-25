/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Yggdrasil -                          *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/humidity_sensor.hpp                *
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief API to use the SHT40-AD1B-R2 humidity sensor  	        *
  *  			                                                    *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#pragma once

#include <common/attributes.hpp>
#include <common/types.hpp>
#include <common/utils.hpp>

namespace bsp::ygg::prph {

	struct SensorDataRaw {
		u8 th;
		u8 tl;
		u8 tcrc8;
		u8 rhh;
		u8 rhl;
		u8 rhcrc8;
	};

	struct SensorData{
		float humidity;
		float sensorTemperature;
	};


	class HumiditySensor {
	public:
		HumiditySensor() = delete;

		/**
		 * @brief Heater commands for the SHT40-AD1B-R2 sensor
		 */
		enum class HeaterCommand : u8{
			Heat200mWFor1s	 = 0x39,		///< activate Highest heater power & High precis. meas. (typ. 200mW @ 3.3V) for 1s
			Heat200mWFor0p1s = 0x32,		///< activate Highest heater power & High precis. meas. (typ. 200mW @ 3.3V) for 0.1s
			Heat110mWFor1s	 = 0x2F,		///< activate Highest heater power & High precis. meas. (typ. 110mW @ 3.3V) for 1s
			Heat110mWFor0p1s = 0x24,		///< activate Highest heater power & High precis. meas. (typ. 110mW @ 3.3V) for 0.1s
			Heat20mWFor1s	 = 0x1E,		///< activate Highest heater power & High precis. meas. (typ. 20mW @ 3.3V) for 1s
			Heat20mWFor0p1s	 = 0x15,		///< activate Highest heater power & High precis. meas. (typ. 20mW @ 3.3V) for 0.1s
		};

		enum class Precision : u8{
			High 	 	= 0xFD,		///< measure T & RH with High precision (High repeatability)
			Medium  	= 0xF6,		///< measure T & RH with medium precision (medium repeatability)
			Low 		= 0xE0,		///< measure T & RH with lowest precision (low repeatability)
		};

		/**
		 * @brief Initialization of the SHT40-AD1B-R2 relative humidity and temperature sensor
		 *
		 * @return Void
		 * @note The sensor does not need a special initialization, this function just does a soft reset
		 */
		static void init() {
			bsp::I2CA::write<u8>(DeviceAddress, static_cast<u8>(Command::SoftReset), {});


		}

		/**
		 * @brief Get a measurement without using the heater
		 *
		 * @return SensorData struct containing the humidity value in % and the sensor temperature
		 */
		static SensorData getSensorData(Precision precision = Precision::High) {
			SensorDataRaw rawData = {0};
			SensorData sensorData = {0};
			rawData = bsp::I2CA::read<SensorDataRaw>(DeviceAddress, static_cast<u8>(precision));

			/* According to the datasheed the code should be like this
			bsp::I2CA::write<u8>(DeviceAddress, static_cast<u8>(Command::High), {});
			// delay(10) //TODO
			bsp::I2CA::read<SensorDataRaw>(DeviceAddress, {});	// Try to read directly without the delay
			*/

			sensorData.sensorTemperature = -45 + (float(175 * ((rawData.th << 8) + rawData.tl)) / 0xFFFF);
			sensorData.humidity = -6 + (float(125 * ((rawData.rhh << 8) + rawData.rhl)) / 0xFFFF);
			if(sensorData.humidity > 100) sensorData.humidity = 100;
			else if(sensorData.humidity < 0) sensorData.humidity = 0;

			return sensorData;

		}

		/**
		 * @brief Enable the heater module on the sensor
		 *
		 * @param Power and duration command
		 * @return Void
		 * @note  The heater is designed for a maximal duty cycle of less than 5% when it is periodically heated
		 */
		static inline void enableHeater(HeaterCommand command) {
			bsp::I2CA::write<u8>(DeviceAddress, static_cast<u8>(command), {});
		}

	private:

		/**
		 * @brief Commands for the SHT40-AD1B-R2 sensor
		 */
		enum class Command : u8{
			ReadSerial	 	 = 0x89,		///< every single sensor has a unique serial number
			SoftReset		 = 0x94,		///< Soft reset
		};




		constexpr static inline u8 DeviceAddress 		= 0x88;		///< I2C device address




	};

}
