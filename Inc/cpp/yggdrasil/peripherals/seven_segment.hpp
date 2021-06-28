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
  *  @file cpp/yggdrasil/peripherals/seven_segment.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the Seven segment display
  */

#pragma once

#include <cpp/common/attributes.hpp>
#include <cpp/common/types.hpp>
#include <cpp/common/utils.hpp>

#include <cstdlib>

namespace bsp::ygg::prph {

	/**
	 * @brief Sevensegment driver
	 */
	class SevenSegment {
	public:
		SevenSegment() = delete;

		/**
		 * @brief Initialization function
		 *
		 * @return Success
		 */
		static bool init() {
			return true;
		}

		/**
		 * @brief Display a unsigned value from 0 to 9999 on the 7 segments
		 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
		 *
		 * @param value Value to display
		 */
		static void setUnsigned(u16 value) {
			static u8 currSegment = 0;

			enableDigit(currSegment);	// Enable the current segment

			switch(currSegment){
				case 0:
					SevenSegment::setDigit((value / 1000) % 10);	// Display thousands
				break;
				case 1:
					SevenSegment::setDigit((value / 100) % 10);		// Display hundreds
				break;
				case 2:
					SevenSegment::setDigit((value / 10) % 10);		// Display tens
				break;
				case 3:
					SevenSegment::setDigit((value / 1) % 10);		// Display ones
				break;
			}
			currSegment = (currSegment + 1) % 4;	// Increment current segment
		}

		/**
		 * @brief Display a signed value from -999 to 999 on the 7 segments
		 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
		 *
		 * @param value Value to display
		 */
		static void setSigned(i16 value) {
			static u8 currSegment = 0;

			enableDigit(currSegment);	// Enable the current segment

			switch(currSegment) {
				case 0:
					if(value < 0) SevenSegment::setDigit('-');				// Display the minus
					else SevenSegment::setDigit(' ');
				break;
				case 1:
					SevenSegment::setDigit((std::abs(value) / 100) % 10);	// Display hundreds
				break;
				case 2:
					SevenSegment::setDigit((std::abs(value) / 10) % 10);	// Display tens
				break;
				case 3:
					SevenSegment::setDigit((std::abs(value) / 1) % 10);		// Display ones
				break;
			}
			currSegment = (currSegment + 1) % 4;	// Increment current segment
		}

		/**
		 * @brief Display a unsigned value from 0 to 0xFFFF in hexadecimal on the 7 segments
		 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
		 *
		 * @param value Value to display in hexadecimal
		 */
		static void setHexadecimal(u16 value) {
			static u8 currSegment = 0;

			enableDigit(currSegment); // Enable the current segment

			switch(currSegment){
				case 0:
					SevenSegment::setDigit((value / 0x1000) % 0x10);
				break;
				case 1:
					SevenSegment::setDigit((value / 0x100) % 0x10);
				break;
				case 2:
					SevenSegment::setDigit((value / 0x10) % 0x10);
				break;
				case 3:
					SevenSegment::setDigit((value / 0x1) % 0x10);
				break;
			}
			currSegment = (currSegment + 1) % 4;	// Increment current segment
		}

		/**
		 * @brief Display a floating point value from -99.9 to 99.9 on the 7 segments, the function will show as many decimal places as possible
		 * @note The function takes care of the multiplexing, but must be called frequently (>= 200Hz recommended)
		 *
		 * @param value Value to display
		 */
		static void setFloatingPoint(float value) {
			static u8 currSegment = 0;

			enableDigit(currSegment);
			switch(currSegment){
				case 0:
					if(value < 0) SevenSegment::setDigit('-');														// Display the minus
					else SevenSegment::setDigit(' ');
				break;
				case 1:
					if(std::abs(value) >= 10) SevenSegment::setDigit(static_cast<u8>(std::abs(value) / 10) % 10);	// Display tens
					else {
						SevenSegment::setDigit(static_cast<u8>(std::abs(value) / 1) % 10);							// Display ones
						seven_segment::DP = true;
					}
				break;
				case 2:
					if(std::abs(value) >= 10) {
						SevenSegment::setDigit(static_cast<u8>(std::abs(value) / 1) % 10);							// Display ones
						seven_segment::DP = true;
					}
					else SevenSegment::setDigit(static_cast<u8>(std::abs(value) * 10) % 10);						// Display tenth

				break;
				case 3:
					if(std::abs(value) >= 10) SevenSegment::setDigit(static_cast<u8>(std::abs(value) * 10) % 10);	// Display tenth
					else SevenSegment::setDigit(static_cast<u8>(std::abs(value) * 100) % 10);						// Display hundredth
				break;
			}

			currSegment = (currSegment + 1) % 4;	// Increment current segment
		}

		/**
		 * @brief Set the segments to the given value, supports hexadecimal, '-' for minus and ' ' for an empty segment
		 * @note The function does not enable any segment
		 *
		 * @param value Digit to set
		 */
		static void setDigit(char value){
			switch(value){
				case 0:		seven_segment::All = 0x3F; break;
				case 1:		seven_segment::All = 0x06; break;
				case 2:		seven_segment::All = 0x5B; break;
				case 3:		seven_segment::All = 0x4F; break;
				case 4:		seven_segment::All = 0x66; break;
				case 5:		seven_segment::All = 0x6D; break;
				case 6:		seven_segment::All = 0x7D; break;
				case 7:		seven_segment::All = 0x07; break;
				case 8:		seven_segment::All = 0x7F; break;
				case 9:		seven_segment::All = 0x6F; break;
				case 0x0A:	seven_segment::All = 0x77; break;
				case 0x0B:	seven_segment::All = 0x7C; break;
				case 0x0C:	seven_segment::All = 0x39; break;
				case 0x0D:	seven_segment::All = 0x5E; break;
				case 0x0E:	seven_segment::All = 0x79; break;
				case 0x0F:	seven_segment::All = 0x71; break;
				case '-':   seven_segment::All = 0x40; break;
				case ' ':   seven_segment::All = 0x00; break;
			}
		}

		/**
		 * @brief Enable one single segment
		 *
		 * @param number Digit to enable
		 */
		static void enableDigit(u8 number){
			switch(number){
				case 0:		seven_segment::SelectAll = 0x01; break;
				case 1:		seven_segment::SelectAll = 0x02; break;
				case 2:		seven_segment::SelectAll = 0x04; break;
				case 3:		seven_segment::SelectAll = 0x08; break;
				default:	seven_segment::SelectAll = 0x00; break;
			}
		}

		/**
		 * @brief Disable all segments
		 */
		static void disable(){
			setDigit(' ');
			enableDigit(0xFF);		// Some value higher than 3 will shut down all
		}

	};

}
