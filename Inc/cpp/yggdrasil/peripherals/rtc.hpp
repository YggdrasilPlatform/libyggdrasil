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
  *  @file cpp/yggdrasil/peripherals/rtc.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the RV-3028-C7 RTC
  */

#pragma once

#include <cpp/common/attributes.hpp>
#include <cpp/common/types.hpp>
#include <cpp/common/utils.hpp>
#include <time.h>

namespace bsp::ygg::prph {

	/**
	 * @brief RTC driver RV-3028-C7
	 */
	class RealTimeClock {
	public:
		RealTimeClock() = delete;

		/**
		 * @brief Initialization function
		 *
		 * @return Success
		 */
		static bool init() {
			return true;
		}

		/**
		 * @brief Get the time saved in the RTC
		 *
		 * @return Time saved in the RTC
		 */
		static time_t getTime() {
			return bsp::I2CA::read<time_t>(DeviceAddress, enumValue(RegisterID::UnixTime0));
		}

		/**
		 * @brief Set the time in the RTC
		 *
		 * @param time Time to save in the RTC
		 */
		static void setTime(time_t time) {
			bsp::I2CA::write<time_t>(DeviceAddress, enumValue(RegisterID::UnixTime0), time);
		}

	private:

		/**
		 * @brief Register map of the RV-3028-C7 RTC
		 */
		enum class RegisterID : u8{
			// Clock registers
			Seconds      			= 0x00,		///< Count of seconds, coded in BCD format
			Minutes      			= 0x01,		///< Count of minutes, coded in BCD format
			Hours        			= 0x02,		///< Count of hours, coded in BCD format 24H Mode as default

			// Calendar registers
			Weekday					= 0x03,		///< Weekday counter value
			Date         			= 0x04,		///< Current date of the month, coded in BCD format
			Month       			= 0x05,		///< Current month, coded in BCD format
			Year        			= 0x06,		///< Current year, coded in BCD format

			// Alarm registers
			MinutesAlarm     		= 0x07,		///< Minutes alarm configuration
			HoursAlarm       		= 0x08,		///< Hours alarm configuration
			DateAlarm        		= 0x09,		///< Weekday / date alarm configuration

			// Periodic countdown timer registers
			TimerValue0				= 0x0A,		///< Lower 8 bits of the 12 bit Timer Value (preset value) for the Periodic Countdown Timer
			TimerValue1				= 0x0B,		///< Upper 4 bits of the 12 bit Timer Value (preset value) for the Periodic Countdown Timer
			TimerStatus0			= 0x0C,		///< Lower 8 bits of the current 12 bit value of the Periodic Countdown Timer
			TimerStatus1			= 0x0D,		///< Upper 4 bits of the current 12 bit value of the Periodic Countdown Timer

			// Configuration registers
			Status					= 0x0E,		///< Used to detect the occurrence of various interrupt events and reliability problems in internal data
			Control1				= 0x0F,		///< Used to specify the target for the Alarm Interrupt function and the Periodic Time Update Interrupt function and to select or set operations for the Periodic Countdown Timer
			Control2				= 0x10,		///< Used to control the interrupt event output for the INT?????????? pin, the stop/start status of clock and calendar operations, the interrupt controlled clock output on CLKOUT pin, the hour mode and the time stamp enable
			GPBits					= 0x11,		///< Holding the bits for general purpose use (7 bits)
			ClockIntMask			= 0x12,		///< Select a predefined interrupt for automatic clock output

			// Eventcontrol / timestamp registers
			EventControl			= 0x13,		///< Controls the event detection on the EVI pin
			Count_TS				= 0x14,		///< Contains the number of occurrences of the corresponding event in standard binary format
			Seconds_TS				= 0x15,		///< Holding a recorded Time Stamp of the Seconds register, in two binary coded decimal (BCD) digits
			Minutes_TS				= 0x16,		///< Holding a recorded Time Stamp of the Minutes register, in two binary coded decimal (BCD) digits
			Hours_TS				= 0x17,		///< Holding a recorded Time Stamp of the Hours register, in two binary coded decimal (BCD) digits
			Date_TS					= 0x18,		///< Holding a recorded Time Stamp of the Date register, in two binary coded decimal (BCD) digits
			Month_TS				= 0x19,		///< Holding a recorded Time Stamp of the Month register, in two binary coded decimal (BCD) digits
			Year_TS					= 0x1A,		///< Holding a recorded Time Stamp of the Year register, in two binary coded decimal (BCD) digits

			// Unix time registers
			UnixTime0				= 0x1B,		///< Bit 0 to 7 from 32-bit UNIX Time counter
			UnixTime1				= 0x1C,		///< Bit 8 to 15 from 32-bit UNIX Time counter
			UnixTime2				= 0x1D,		///< Bit 16 to 23 from 32-bit UNIX Time counter
			UnixTime3				= 0x1E,		///< Bit 24 to 31 from 32-bit UNIX Time counter

			// RAM registers
			UserRam1				= 0x1F,		///< Holding the bits for general purpose use
			UserRam2				= 0x20,		///< Holding the bits for general purpose use

			//Password registers
			Password0				= 0x21,		///< Bit 0 to 7 from 32-bit Password
			Password1				= 0x22,		///< Bit 8 to 15 from 32-bit Password
			Password2				= 0x23,		///< Bit 16 to 23 from 32-bit Password
			Password3				= 0x24,		///< Bit 24 to 31 from 32-bit Password

			//EEPROM memory control registers
			EEAddress				= 0x25,		///< Holding the Address used for read or write from/to a single EEPROM Memory byte
			EEData					= 0x26,		///< Holding the Data that are read from, or that are written to a single EEPROM Memory byte
			EECommand				= 0x27,		///< This register must be written with specific values, in order to Update or Refresh all (readable/writeable) Configuration EEPROM registers or to read or write from/to a single EEPROM Memory byte

			//ID register
			ID						= 0x28,		///< Holding the 4 bit Hardware Identification number (HID) and the 4 bit Version Identification number (VID)

		};

		constexpr static inline u8 DeviceAddress = 0xA4;		///< I2C device address

		/**
		 * @brief Raw RTC data
		 */
		struct RawData {
			u8 sec;		///< Seconds in BCD
			u8 min;		///< Minutes in BCD
			u8 hrs;		///< Hours in BCD
			u8 weekday; ///< Weekday
			u8 date;	///< Day of the month in BCD
			u8 month;	///< Month in BCD
			u8 year;	///< Year in BCD
		};

	};

}
