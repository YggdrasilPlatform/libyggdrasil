/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Peripherals -                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/color_sensor.hpp   	            *
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief API to use the TCS3472 color sensor  	        		*
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

	struct Color {
		u16 r;
		u16 g;
		u16 b;
		u16 brightness;
	};


	class ColorSensor {
	public:
		ColorSensor() = delete;

		/**
		 * @brief Integration time = (256 - IntegrationTime) * 2.4ms
		 */
		enum class IntegrationTime {
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
		enum class Gain {
		  _1x 	= 0x00, ///<  No gain
		  _4x 	= 0x01, ///<  4x gain
		  _16x 	= 0x02, ///<  16x gain
		  _60x 	= 0x03  ///<  60x gain
		};

		/**
		 * @brief Initialization of the TCS3472 color sensor
		 *
		 * @return True when the connected device matched the device id, false when not
		 * @note This function does not start a conversion. Values for integration time (50ms) and gain (1x) are set
		 */

		static bool init() {
			if (bsp::I2CA::read<u8>(DeviceAddress, CommandBit | static_cast<u8>(RegisterID::ID)) != DeviceID) {		// Check device id
					return false;
			}
			setIntergrationTime(IntegrationTime::_50ms);			// Set integration time
			setGain(Gain::_1x);										// Set gain
			enable();												// Enable sensor, this does not start a conversion

			return true;

		}


		/**
		 * @brief Set the integration time
		 *
		 * @param Integration time value
		 * @note Integration time = (256 - IntegrationTime) * 2.4ms
		 */
		static inline void setIntergrationTime(IntegrationTime integrationTime) {
			bsp::I2CA::write<u8>(DeviceAddress, static_cast<u8>(RegisterID::ATIME),  static_cast<u8>(integrationTime));	// Write integration time in the ATIME register
		}

		/**
		 * @brief Set the gain
		 *
		 * @param Gain value
		 * @note value can be 1x, 4x, 16x and 60x
		 */
		static inline void setGain(Gain gain) {
			bsp::I2CA::write<u8>(DeviceAddress, CommandBit | static_cast<u8>(RegisterID::CTRL), static_cast<u8>(gain));				// Set gain value in the CTRL register
		}

		/**
		 * @brief Enable the sensor
		 *
		 * @note This function does not start a conversion
		 */
		static void enable() {
			EnableRegister enRegister = {0};
			enRegister.PON = 1;
			bsp::I2CA::write<u8>(DeviceAddress, CommandBit | static_cast<u8>(RegisterID::EN), bit_cast<u8>(enRegister));				// Enable sensor
			//delay(3);																									// Wait for power up
		}

		/**
		 * @brief Disables the sensor
		 */
		static void disable() {
			EnableRegister enRegister = {0};
			bsp::I2CA::write<u8>(DeviceAddress, CommandBit | static_cast<u8>(RegisterID::EN), bit_cast<u8>(enRegister));				// Disable sensor

		}

		/**
		 * @brief Start a new measurement and read the color values
		 *
		 * @return Color RGB and brightness value (all 16 Bit)
		 * @note This function is polling the result and blocks the code for the duration of the integration time
		 */
		static Color getColor() {
			EnableRegister enRegister = {0};
			enRegister.PON = 1;																								// Enable
			enRegister.AEN = 1;																								// Enable RGBC
			bsp::I2CA::write<u8>(DeviceAddress, CommandBit | static_cast<u8>(RegisterID::EN), bit_cast<u8>(enRegister));	// Write enable register
			while(bsp::I2CA::read<u8>(DeviceAddress, CommandBit | static_cast<u8>(RegisterID::STATUS)) && ConversionDone) {			// Wait for cnoversion to complete
				//delay(1);																								// TODO	// Wait to not avoid continuous i2c communication
			}

			return bsp::I2CA::read<Color>(10, 10);
		}

	private:




		/**
		 * @brief Register map of the TCS3472 color sensor.
		 */
		enum class RegisterID : u8{
			EN			= 0x00,		///< Enable Register
			ATIME  		= 0x01,		///< RGBC Timing Register
			WTIME		= 0x02,		///< Wait Time Register
			AILTL		= 0x04,		///< RGBC clear channel low threshold lower byte
			AILTH		= 0x05,		///< RGBC clear channel low threshold upper byte
			AIHTL		= 0x06,		///< RGBC clear channel high threshold lower byte
			AIHTH		= 0x07,		///< RGBC clear channel high threshold upper byte
			PERS		= 0x0C, 	///< Persistence Register
			CNFG		= 0x0D, 	///< Configuration Register
			CTRL		= 0x0F, 	///< Control Register
			ID			= 0x12,		///< ID Register
			STATUS		= 0x13,		///< Status Register
			CDATA 		= 0x14,		///< Clear data low byte
			CDATAH 		= 0x15,		///< Clear data high byte
			RDATA 		= 0x16, 	///< Red data low byte
			RDATAH 		= 0x17,		///< Red data high byte
			GDATA 		= 0x18,		///< Green data low byte
			GDATAH		= 0x19,		///< Green data high byte
			BDATA 		= 0x1A,		///< Blue data low byte
			BDATAH 		= 0x1B, 	///< Blue data high byte

		};

		/**
		 * @brief Enable register
		 */
		struct EnableRegister {
			u8 PON : 1;			///< Power on
			u8 AEN : 1;			///< RGBC enable, activates the two channel ADC
			u8 Reserved : 1;	///< Write as 0
			u8 WEN : 1;			///< Wait enable
			u8 AIEN : 1;		///< RGBC interrupt enable
			u8 Reserved2 :3;	///< Write as 0
		};
		static_assert (sizeof(EnableRegister) == sizeof(u8), "Enable register definition wrong");

		/**
		 * @brief Status register
		 */
		struct StatusRegister {
			u8 AVALID : 1;		///< RGBC Valid. Indicates that the RGBC channels have completed an integration cycle.
			u8 Reserved1 : 3;	///< Reserved
			u8 AINT : 1;		///< RGBC clear channel interrupt
			u8 Reserved2: 3;	///< Reserved
		};
		static_assert (sizeof(StatusRegister) == sizeof(u8), "Status register definition wrong");

		constexpr static inline u8 DeviceAddress 		= 0x29;		///< I2C device address
		constexpr static inline u8 DeviceID				= 0x44;		///< ID for TCS34725
		constexpr static inline u8 CommandBit			= 0x80;		///< Set to write a command
		constexpr static inline u8 ConversionDone		= 0x01;		///< Conversion done flag



	};

}
