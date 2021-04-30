/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Yggdrasil -                          *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/pressure_sensor.hpp                *
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief API to use the LPS22HBTR pressure sensor	  	        *
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



	class PressureSensor {
	public:
		PressureSensor() = delete;

		struct SensorData{
			float pressure;
			float sensorTemperature;
		};


		static void init(){
			u8 id = 0;
			do{
				bsp::SPIACE = false;
				bsp::SPIA::write<u8>(enumValue(Register::WHO_AM_I) | RequestResponse);
				id = bsp::SPIA::read<u8>();
				bsp::SPIACE = true;
				core::delay(1);
			} while(id != DeviceID);

		}

		static SensorData getSensorData(){
			SensorData senorData = {0};
			ControlRegister2 ctrlReg2 = { .ONE_SHOT = 1, .I2C_DIS = 0, .IF_ADD_INC = 0 };

			bsp::SPIACE = false;
			bsp::SPIA::write<std::array<u8,2>>({enumValue(Register::CTRL_REG2), bit_cast<u8>(ctrlReg2)});
			bsp::SPIACE = true;
			do{
				bsp::SPIACE = true;
				core::delay(10);
				bsp::SPIACE = false;
				bsp::SPIA::write<u8>(enumValue(Register::CTRL_REG2) | RequestResponse);
			} while((bsp::SPIA::read<u8>() & ConversionDone) == 0);

			{
				auto xl = readRegister(Register::PRESS_OUT_XL);
				auto l  = readRegister(Register::PRESS_OUT_L);
				auto h  = readRegister(Register::PRESS_OUT_H);

				senorData.pressure = static_cast<float>(xl | (l << 8) | (h << 16)) / 4096.0;
			}

			{
				auto l  = readRegister(Register::TEMP_OUT_L);
				auto h  = readRegister(Register::TEMP_OUT_H);

				senorData.sensorTemperature = static_cast<float>(l | (h << 8)) / 100;
			}


			return senorData;

		}

	private:

		enum class Register : u8{
			INTERRUPT_CFG 	= 0x0B, 	///< Interrupt register
			THS_P_L			= 0x0C,		///< Pressure threshold registers low
			THS_P_H			= 0x0D,		///< Pressure threshold registers high
			WHO_AM_I		= 0x0F, 	///< Who am I
			CTRL_REG1		= 0x10,		///< Control registers 1
			CTRL_REG2		= 0x11,		///< Control registers 2
			CTRL_REG3		= 0x12,		///< Control registers 3
			FIFO_CTRL		= 0x14,		///< FIFO configuration register
			REF_P_XL		= 0x15,		///< Reference pressure registers bit [0 7]
			REF_P_L			= 0x16,		///< Reference pressure registers bit [8 15]
			REF_P_H			= 0x17,		///< Reference pressure registers bit [16 23]
			RPDS_L			= 0x18,		///< Pressure offset registers low
			RPDS_H			= 0x19,		///< Pressure offset registers high
			RES_CONF		= 0x1A,		///< Resolution register
			INT_SOURCE 		= 0x25, 	///< Interrupt register
			FIFO_STATUS 	= 0x26,		///< FIFO status register
			STATUS			= 0x27,		///< Status register
			PRESS_OUT_XL 	= 0x28,		///< Pressure output registers bit [0 7]
			PRESS_OUT_L 	= 0x29,		///< Pressure output registers bit [8 15]
			PRESS_OUT_H 	= 0x2A,		///< Pressure output registers bit [16 23]
			TEMP_OUT_L 		= 0x2B,		///< Temperature output registers low
			TEMP_OUT_H 		= 0x2C,		///< Temperature output registers high
			LPFP_RES 		= 0x33,		///< Filter reset register
		};

		/**
		 * @brief Enable register
		 */
		struct ControlRegister2 {
			u8 ONE_SHOT 	: 1; 	///< One-shot enable
			u8 Reserved0 	: 1; 	///< Write as 0
			u8 SWRESET		: 1; 	///< Software reset
			u8 I2C_DIS		: 1; 	///< Disable I2C interface
			u8 IF_ADD_INC   : 1; 	///< Register address automatically incremented during a multiple byte access
			u8 STOP_ON_FTH  : 1; 	///< Stop on FIFO watermark
			u8 FIFO_EN		: 1;	///< FIFO enable
			u8 BOOT			: 1;	///< Reboot memory content
		};
		static_assert (sizeof(ControlRegister2) == sizeof(u8), "Control register 2 definition wrong");

		constexpr static inline u8 RequestResponse = 0x80;		///> Requests a write from the sensor on the following clocks
		constexpr static inline u8 DeviceID = 0xb1;			///> Value of the who am i register
		constexpr static inline u8 ConversionDone = 0x01;	///> Conversion done flag

		static u8 readRegister(Register reg) {
			bsp::SPIACE = false;
			bsp::SPIA::write<u8>(enumValue(reg) | RequestResponse);
			auto value = bsp::SPIA::read<u8>();
			bsp::SPIACE = true;

			return value;
		}

	};

}
