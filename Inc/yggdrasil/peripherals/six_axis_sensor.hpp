/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Peripherals -                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/six_axis_sensor.hpp   	            *
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Driver to use the ICM-42605 Six Axis Sensor				*
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

namespace bsp::ygg::prph {

	class SixAxisSensor {
	public:
		struct Coordinate {
			float x, y, z;
		};

		enum class AccelFullScaleRange : u8 {
			_2G = 0x03,
			_4G = 0x02,
			_8G = 0x01,
			_16G = 0x00
		};

		enum class GyroFullScaleRange : u8 {
			_2000DPS   = 0x00,
			_1000DPS   = 0x01,
			_500DPS    = 0x02,
			_250DPS    = 0x03,
			_125DPS    = 0x04,
			_62_5DPS   = 0x05,
			_31_25DPS  = 0x06,
			_15_125DPS = 0x07
		};

		enum class AccelOutputDataRange : u8 {
			_8000Hz   = 0x03,
			_4000Hz   = 0x04,
			_2000Hz   = 0x05,
			_1000Hz   = 0x06,
			_200Hz    = 0x07,
			_100Hz    = 0x08,
			_50Hz     = 0x09,
			_25Hz     = 0x0A,
			_12_5Hz   = 0x0B,
			_6_25Hz   = 0x0C,
			_3_125Hz  = 0x0D,
			_1_5625Hz = 0x0E,
			_500Hz    = 0x0F
		};

		enum class GyroOutputDataRange : u8 {
			_8000Hz = 0x03,
			_4000Hz = 0x04,
			_2000Hz = 0x05,
			_1000Hz = 0x06,
			_200Hz  = 0x07,
			_100Hz  = 0x08,
			_50Hz   = 0x09,
			_25Hz   = 0x0A,
			_12_5Hz = 0x0B,
			_500Hz  = 0x0F
		};

		SixAxisSensor() = delete;

		/**
		 * @brief Initializes the ICM-42605 Six Axis Sensor
		 *
		 * @param accelScale Scaling factor of the Accelerometer
		 * @param gyroScale Scaling factor of the Gyroscope
		 * @param accelOdr Output data rate of the Accelerometer
		 * @param gyroOdr Output data rate of the Gyroscope
		 */
		static void init(AccelFullScaleRange accelScale, GyroFullScaleRange gyroScale, AccelOutputDataRange accelOdr, GyroOutputDataRange gyroOdr) {
			SixAxisSensor::s_accelScale = accelScale;
			SixAxisSensor::s_gyroScale = gyroScale;

			selectBank(0);

			{
				u8 id;
				do {
					id = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::WHO_AM_I));
				} while (id != DeviceID);
			}

			{
				// Enable hyroscope and accelerometer in low noise mode
				auto pwrMgmt0 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::PWR_MGMT0));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::PWR_MGMT0), pwrMgmt0 | 0x0F);

				// Set gyro scale and data rate
				auto gyroConfig0 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::GYRO_CONFIG0));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::GYRO_CONFIG0), gyroConfig0 | enumValue(gyroOdr) | (enumValue(gyroScale) << 5));

				// Set accel scale and data rate
				auto accelConfig0 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::ACCEL_CONFIG0));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::ACCEL_CONFIG0), accelConfig0 | enumValue(accelOdr) | (enumValue(accelScale) << 5));

				// Set temperature low pass filter to a minimum and use first order filter for gyro
				auto gyroConfig1 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::GYRO_CONFIG1));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::GYRO_CONFIG1), gyroConfig1 | 0xD0);

				// Setup interrupt pins
				auto intConfig0 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::INT_CONFIG));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::INT_CONFIG), intConfig0 | 0x18 | 0x03);

				// Enable async interrupt reset
				auto intConfig1 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::INT_CONFIG1));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::INT_CONFIG1), intConfig1 & ~0x10);

				// Route data ready interrupt to INT1
				auto intSource0 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::INT_SOURCE0));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::INT_SOURCE0), intSource0 | 0x08);

				// Route AGC interrupt to INT2
				auto intSource3 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::INT_SOURCE3));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::INT_SOURCE3), intSource3 | 0x01);

				selectBank(4);

				// Set inversion matrix to X and Y inverted, Z not inverted
				auto apexConfig5 = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank4::APEX_CONFIG5));
				bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank4::APEX_CONFIG5), (apexConfig5 & ~(0b111)) | 0x011);

				selectBank(0);
			}
		}

		/**
		 * @brief Get yggdrasil's current orientation from the gyroscope
		 *
		 * @return X, Y and Z rotation axis values
		 */
		static Coordinate getRotation() {
			struct GyroData {
				ByteSwapped<i16> x, y, z;
			};

			auto [x, y, z] = bsp::I2CA::read<GyroData>(DeviceAddress, enumValue(RegisterBank0::GYRO_DATA_X1));

			return { transformGyroAxisData(x), transformGyroAxisData(y), transformGyroAxisData(z) };
		}

		/**
		 * @brief Get yggdrasil's current acceleration from the accelerometer
		 *
		 * @return X, Y and Z acceleration axis values
		 */
		static Coordinate getAcceleration() {
			struct AccelData {
				ByteSwapped<i16> x, y, z;
			};

			auto [x, y, z] = bsp::I2CA::read<AccelData>(DeviceAddress, enumValue(RegisterBank0::ACCEL_DATA_X1));

			return { transformAccelAxisData(x), transformAccelAxisData(y), transformAccelAxisData(z) };
		}

		/**
		 * @brief Get the internal temperature of the ICM-42605 sensor
		 */
		static float getTemperature() {
			auto data = bsp::I2CA::read<ByteSwapped<u16>>(DeviceAddress, enumValue(RegisterBank0::TEMP_DATA1));

			return (float(data) / 132.48F) + 25;
		}


	private:
		enum class RegisterBank0 : u8 {
			DEVICE_CONFIG      = 0x11,
			DRIVE_CONFIG       = 0x13,
			INT_CONFIG         = 0x14,
			FIFO_CONFIG        = 0x16,
			TEMP_DATA1         = 0x1D,
			TEMP_DATA0         = 0x1E,
			ACCEL_DATA_X1      = 0x1F,
			ACCEL_DATA_X0      = 0x20,
			ACCEL_DATA_Y1      = 0x21,
			ACCEL_DATA_Y0      = 0x22,
			ACCEL_DATA_Z1      = 0x23,
			ACCEL_DATA_Z0      = 0x24,
			GYRO_DATA_X1       = 0x25,
			GYRO_DATA_X0       = 0x26,
			GYRO_DATA_Y1       = 0x27,
			GYRO_DATA_Y0       = 0x28,
			GYRO_DATA_Z1       = 0x29,
			GYRO_DATA_Z0       = 0x2A,
			TMST_FSYNCH        = 0x2B,
			TMST_FSYNCL        = 0x2C,
			INT_STATUS         = 0x2D,
			FIFO_COUNTH        = 0x2E,
			FIFO_COUNTL        = 0x2F,
			FIFO_DATA          = 0x30,
			APEX_DATA0         = 0x31,
			APEX_DATA1         = 0x32,
			APEX_DATA2         = 0x33,
			APEX_DATA3         = 0x34,
			APEX_DATA4         = 0x35,
			APEX_DATA5         = 0x36,
			INT_STATUS2        = 0x37,
			INT_STATUS3        = 0x38,
			SIGNAL_PATH_RESET  = 0x4B,
			INTF_CONFIG0       = 0x4C,
			INTF_CONFIG1       = 0x4D,
			PWR_MGMT0          = 0x4E,
			GYRO_CONFIG0       = 0x4F,
			ACCEL_CONFIG0      = 0x50,
			GYRO_CONFIG1       = 0x51,
			GYRO_ACCEL_CONFIG0 = 0x52,
			ACCEL_CONFIG1      = 0x53,
			TMST_CONFIG        = 0x54,
			APEX_CONFIG0       = 0x56,
			SMD_CONFIG         = 0x57,
			FIFO_CONFIG1       = 0x5F,
			FIFO_CONFIG2       = 0x60,
			FIFO_CONFIG3       = 0x61,
			FSYNC_CONFIG       = 0x62,
			INT_CONFIG0        = 0x63,
			INT_CONFIG1        = 0x64,
			INT_SOURCE0        = 0x65,
			INT_SOURCE1        = 0x66,
			INT_SOURCE3        = 0x68,
			INT_SOURCE4        = 0x69,
			FIFO_LOST_PKT0     = 0x6C,
			FIFO_LOST_PKT1     = 0x6D,
			SELF_TEST_CONFIG   = 0x70,
			WHO_AM_I           = 0x75,
			REG_BANK_SEL       = 0x76
		};

		enum class RegisterBank1 : u8 {
			SENSOR_CONFIG0       = 0x03,
			GYRO_CONFIG_STATIC2  = 0x0B,
			GYRO_CONFIG_STATIC3  = 0x0C,
			GYRO_CONFIG_STATIC4  = 0x0D,
			GYRO_CONFIG_STATIC5  = 0x0E,
			GYRO_CONFIG_STATIC6  = 0x0F,
			GYRO_CONFIG_STATIC7  = 0x10,
			GYRO_CONFIG_STATIC8  = 0x11,
			GYRO_CONFIG_STATIC9  = 0x12,
			GYRO_CONFIG_STATIC10 = 0x13,
			XG_ST_DATA           = 0x5F,
			YG_ST_DATA           = 0x60,
			ZG_ST_DATA           = 0x61,
			TMSTVAL0             = 0x62,
			TMSTVAL1             = 0x63,
			TMSTVAL2             = 0x64,
			INTF_CONFIG4         = 0x7A,
			INTF_CONFIG5         = 0x7B,
			INTF_CONFIG6         = 0x7C
		};

		enum class RegisterBank2 : u8 {
			ACCEL_CONFIG_STATIC2 = 0x03,
			ACCEL_CONFIG_STATIC3 = 0x04,
			ACCEL_CONFIG_STATIC4 = 0x05,
			XA_ST_DATA           = 0x3B,
			YA_ST_DATA           = 0x3C,
			ZA_ST_DATA           = 0x3D
		};

		enum class RegisterBank4 : u8 {
			GYRO_ON_OFF_CONFIG = 0x0E,
			APEX_CONFIG1       = 0x40,
			APEX_CONFIG2       = 0x41,
			APEX_CONFIG3       = 0x42,
			APEX_CONFIG4       = 0x43,
			APEX_CONFIG5       = 0x44,
			APEX_CONFIG6       = 0x45,
			APEX_CONFIG7       = 0x46,
			APEX_CONFIG8       = 0x47,
			APEX_CONFIG9       = 0x48,
			ACCEL_WOM_X_THR    = 0x4A,
			ACCEL_WOM_Y_THR    = 0x4B,
			ACCEL_WOM_Z_THR    = 0x4C,
			INT_SOURCE6        = 0x4D,
			INT_SOURCE7        = 0x4E,
			INT_SOURCE8        = 0x4F,
			INT_SOURCE9        = 0x50,
			INT_SOURCE10       = 0x51,
			OFFSET_USER0       = 0x77,
			OFFSET_USER1       = 0x78,
			OFFSET_USER2       = 0x79,
			OFFSET_USER3       = 0x7A,
			OFFSET_USER4       = 0x7B,
			OFFSET_USER5       = 0x7C,
			OFFSET_USER6       = 0x7D,
			OFFSET_USER7       = 0x7E,
			OFFSET_USER8       = 0x7F
		};

		constexpr static inline auto DeviceAddress = 0xD2;
		constexpr static inline auto DeviceID = 0x42;

		static inline AccelFullScaleRange s_accelScale;
		static inline GyroFullScaleRange s_gyroScale;

		/**
		 * @brief Select the current register bank
		 *
		 * @oaram bank Bank to select
		 */
		static void selectBank(u8 bank) {
			auto bankSelect = bsp::I2CA::read<u8>(DeviceAddress, enumValue(RegisterBank0::REG_BANK_SEL));
			bsp::I2CA::write<u8>(DeviceAddress, enumValue(RegisterBank0::REG_BANK_SEL), (bankSelect & 0xF8) | bank);
		}

		/**
		 * @brief Transforms the raw gyroscope output data to degrees per second
		 *
		 * @brief data Raw data from gyroscope
		 */
		static inline float transformGyroAxisData(i16 data) {
			return (float(data) / 0xFFFF) * (2000 / (enumValue(SixAxisSensor::s_gyroScale) + 1));
		}

		/**
		 * @brief Transforms the raw accelerometer output data to g => 9.81m/s^2
		 *
		 * @brief data Raw data from accelerometer
		 */
		static inline float transformAccelAxisData(i16 data) {
			return (float(data) / 0xFFFF) * (16 / (enumValue(SixAxisSensor::s_accelScale) + 1));
		}
	};

}
