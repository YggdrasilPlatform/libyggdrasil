/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Yggdrasil - 	                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/rtc.hpp                			*
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief API to use the Joysticks using the external 	        *
  *  TLA2024IRUGT ADC.
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

	struct Position {
	  i8 x;
	  i8 y;
	};

	struct JoyStickData {
	  Position pos;
	  bool pressed;
	};


	class Joystick {
	public:
		Joystick() = delete;


		/**
		 * @brief Get the joystick data for the left joystick
		 *
		 * @return JoyStickData struct
		 * @note This function is polling
		 */
		static JoyStickData getLeftJoyStick() {
			JoyStickData tempData = {0};
			tempData.pressed = LeftJoyStickButton;								// Read the button state
			tempData.pos.x = transformInputData(getADCValue(MUX::SingleEnded_AIN1));	// Get ADC Value
			tempData.pos.y = transformInputData(getADCValue(MUX::SingleEnded_AIN0));	// Get ADC Value
			if(tempData.pos.x * tempData.pos.x + tempData.pos.y * tempData.pos.y < s_deadzone * s_deadzone){
				tempData.pos = {0,0};
			}
			return tempData;
		}

		/**
		 * @brief Get the joystick data for the right joystick
		 *
		 * @return JoyStickData struct
		 * @note This function is polling
		 */
		static JoyStickData getRightJoyStick(){
			JoyStickData tempData = {0};
			tempData.pressed = RightJoyStickButton;								// Read the button state
			tempData.pos.x = transformInputData(getADCValue(MUX::SingleEnded_AIN3));	// Get ADC Value
			tempData.pos.y = transformInputData(getADCValue(MUX::SingleEnded_AIN2));	// Get ADC Value
			if(tempData.pos.x * tempData.pos.x + tempData.pos.y * tempData.pos.y < s_deadzone * s_deadzone){
				tempData.pos = {0,0};
			}
			return tempData;
		}

		/**
		 * @brief Set both joystick's deadzone
		 *
		 * @param deadzone Deadzone value
		 */
		static void setDeadzone(u8 deadzone){
			if (deadzone < PositionMax)
				Joystick::s_deadzone = deadzone;
		}

		/**
		 * @brief Get the current Joystick deadzone
		 *
		 * @return Current deadzone value
		 */
		static u8 getDeadzone(){
			return Joystick::s_deadzone;
		}




	private:

		/**
		 * @brief Register map of the TLA2024 ADC
		 */
		enum class RegisterID : u8 {
			ConversionRegister 		= 0x00,		///< The 16-bit conversion data register contains the result of the last conversion in binary two's-complement format
			ConfigurationRegister 	= 0x01,		///< The 16-bit configuration register controls the operating mode, input selection, data rate, and full-scale range.
		};

		/**
		 * @brief Input Multiplexer Configuration (TLA2024 only)
		 */
		enum class MUX : u8 {
			Differential_AIN0_AIN1 	= 0x00,		///< AINP = AIN0 and AINN = AIN1 (default)
			Differential_AIN0_AIN3 	= 0x01,		///< AINP = AIN0 and AINN = AIN3
			Differential_AIN1_AIN3 	= 0x02,		///< AINP = AIN1 and AINN = AIN3
			Differential_AIN2_AIN3 	= 0x03,		///< AINP = AIN2 and AINN = AIN3
			SingleEnded_AIN0		= 0x04,		///< AINP = AIN0 and AINN = GND
			SingleEnded_AIN1		= 0x05,		///< AINP = AIN1 and AINN = GND
			SingleEnded_AIN2		= 0x06,		///< AINP = AIN2 and AINN = GND
			SingleEnded_AIN3		= 0x07,		///< AINP = AIN3 and AINN = GND
		};

		/**
		 * @brief Programmable Gain Amplifier Configuration (TLA2022 and TLA2024 Only)
		 */
		enum class PGA : u8 {
			FSR_6p144 = 0x00, 	///< FSR = ±6.144 V
			FSR_4p096 = 0x01, 	///< FSR = ±4.096 V
			FSR_2p048 = 0x02,	///< FSR = ±2.048 V (default)
			FSR_1p024 = 0x03,	///< FSR = ±1.024 V
			FSR_0p512 = 0x04,	///< FSR = ±0.512 V
			FSR_0p256 = 0x05,	///< FSR = ±0.256 V
		};

		/**
		 * @brief Operating Mode
		 */
		enum class MODE : u8 {
			Continious = 0x00, 	///< Continuous-conversion mode
			SingleShot = 0x01, 	///< Single-shot conversion mode or power-down state (default)
		};

		/**
		 * @brief Data Rate
		 */
		enum class DR : u8 {
			SPS128  = 0x00, 	///< 128 SPS
			SPS250  = 0x01, 	///< 250 SPS
			SPS490  = 0x02,		///< 490 SPS
			SPS920  = 0x03,		///< 920 SPS
			SPS1600 = 0x04,		///< 1600 SPS (default)
			SPS2400 = 0x05,		///< 2400 SPS
			SPS3300 = 0x06,		///< 3300 SPS
		};

		/**
		 * @brief Configuration register
		 */
		struct ConfigurationRegister {
			u16 Reserved 	: 5;		///< Always write as 0x03
			u16 DR 			: 3;		///< Data Rate
			u16 MODE 		: 1;		///< Operating Mode
			u16 PGA 		: 3;		///< Programmable Gain Amplifier Configuration (TLA2022 and TLA2024 Only)
			u16 MUX 		: 3;		///< Input Multiplexer Configuration (TLA2024 only)
			u16 OS 			: 1;		///< Operational Status or Single-Shot Conversion Start
		};

		static_assert(sizeof(ConfigurationRegister) == sizeof(u16), "Configuration register definition wrong");


		constexpr static inline u8 DeviceAddress 		= 0x90;		///< I2C device address
		constexpr static inline u8 ReservedBits			= 0x03;		///< Reserved bits must be write as 0x03
		constexpr static inline u16 ConversionDone		= 0x8000;	///< Configuration done flag (OS bit in configuration register)

		constexpr static inline i8 CenterPosition		= 0x7F;		///< Configuration done flag (OS bit in configuration register)
		constexpr static inline u16 AdcMaxValue			= 0x7FF;	///< Single ended maximal value (lost 1 bit due to single ended measurement)
		constexpr static inline i8 PositionRange		= 200;
		constexpr static inline i8 PositionMin			= -100;
		constexpr static inline i8 PositionMax			= 100;

		static inline i8 s_deadzone = 5;


		/**
		 * @brief Start a single shot measurement
		 *
		 * @param MUX channel to determine the input to convert
		 * @return u16 12 bit adc data left aligned
		 * @note Start a conversion and poll until the conversion is finished
		 */
		static u16 getADCValue(MUX channel) {
			ConfigurationRegister configRegister = {0};
			configRegister.OS = 1;
			configRegister.MUX = static_cast<u8>(channel);
			configRegister.PGA = static_cast<u8>(PGA::FSR_4p096);
			configRegister.MODE = static_cast<u8>(MODE::SingleShot);
			configRegister.DR = static_cast<u8>(DR::SPS1600);
			configRegister.Reserved = ReservedBits;

			bsp::I2CA::write<u16>(DeviceAddress, static_cast<u8>(RegisterID::ConfigurationRegister), byteSwap(bit_cast<u16>(configRegister)));		// Start Conversion

			while(byteSwap(bsp::I2CA::read<u16>(DeviceAddress, static_cast<u8>(RegisterID::ConfigurationRegister))) & ConversionDone){
				core::delay(1);
			}


			volatile auto adcdata = byteSwap(bsp::I2CA::read<u16>(DeviceAddress, static_cast<u8>(RegisterID::ConversionRegister)));
			return adcdata;

		}

		/**
		 * @brief Conversion from 12 Bit ADC Value to a
		 *
		 * @param u16 12 bit ADC data left aligned
		 * @return i8 converted data to an range from -100 to 100 where 0 equals center position
		 */
		static inline i8 transformInputData(u16 adcData) {
			return (i8)((static_cast<float>(PositionRange) / static_cast<float>(AdcMaxValue)) * static_cast<float>(adcData) + static_cast<float>(PositionMin));	// Convert the 11 bit tow's complement value to a i8 ranged [-100,100]
		}

	};

}
