/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Yggdrasil -	                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/seven_segment.hpp   	            *
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief API to use the 7 segment display 	 	        		*
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



	class SevenSegment {
	public:
		SevenSegment() = delete;

		enum class Mode {
			Unsigned,
			Signed,
			Hexdecimal,
			FloatingPoint,

			DigitA,
			DigitB,
			DigitC,
			DigitD,
		};

		/**
		 * @brief
		 *
		 * @return
		 * @note
		 */
		static void setUnsigned(u16 value) {
			static u8 currSegment = 0;

			enableDigit(currSegment);

			switch(currSegment){
				case 0:
					SevenSegment::setDigit((value / 1000) % 10);
				break;
				case 1:
					SevenSegment::setDigit((value / 100) % 10);
				break;
				case 2:
					SevenSegment::setDigit((value / 10) % 10);
				break;
				case 3:
					SevenSegment::setDigit((value / 1) % 10);
				break;
			}
			currSegment = (currSegment + 1) % 4;
		}

		static void setSigned(i16 value) {
			static u8 currSegment = 0;

			enableDigit(currSegment);

			switch(currSegment){
				case 0:
					if(value < 0) SevenSegment::setDigit('-');
				break;
				case 1:
					SevenSegment::setDigit((value / 100) % 10);
				break;
				case 2:
					SevenSegment::setDigit((value / 10) % 10);
				break;
				case 3:
					SevenSegment::setDigit((value / 1) % 10);
				break;
			}
			currSegment = (currSegment + 1) % 4;
		}

		static void setHexadecimal(u16 value) {
			static u8 currSegment = 0;

			enableDigit(currSegment);

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
			currSegment = (currSegment + 1) % 4;
		}

		static void setFloatingPoint(float value) {
			static u8 currSegment = 0;

			enableDigit(currSegment);
			switch(currSegment){
				case 0:
					if(value < 0) SevenSegment::setDigit('-');
				break;
				case 1:
					SevenSegment::setDigit(static_cast<u8>(value / 10) % 10);
				break;
				case 2:
					SevenSegment::setDigit(static_cast<u8>(value / 1) % 10);
					seven_segment::DP = false;
				break;
				case 3:
					SevenSegment::setDigit(static_cast<u8>(value * 10) % 10);
				break;
			}

			currSegment = (currSegment + 1) % 4;

		}

		static void setDigit(char value){
			switch(value){
				case 0:		seven_segment::All = 0xC0; break;
				case 1:		seven_segment::All = 0xF9; break;
				case 2:		seven_segment::All = 0xA4; break;
				case 3:		seven_segment::All = 0xB0; break;
				case 4:		seven_segment::All = 0x99; break;
				case 5:		seven_segment::All = 0x92; break;
				case 6:		seven_segment::All = 0x82; break;
				case 7:		seven_segment::All = 0xF8; break;
				case 8:		seven_segment::All = 0x80; break;
				case 9:		seven_segment::All = 0x90; break;
				case 0x0A:	seven_segment::All = 0x88; break;
				case 0x0B:	seven_segment::All = 0x83; break;
				case 0x0C:	seven_segment::All = 0xC6; break;
				case 0x0D:	seven_segment::All = 0xA1; break;
				case 0x0E:	seven_segment::All = 0x86; break;
				case 0x0F:	seven_segment::All = 0x8E; break;
				case '-':   seven_segment::All = 0x9F; break;
			}

		}

		static void enableDigit(u8 number){
			switch(number){
				case 0:		seven_segment::SelectAll = ~0x01; break;
				case 1:		seven_segment::SelectAll = ~0x02; break;
				case 2:		seven_segment::SelectAll = ~0x04; break;
				case 3:		seven_segment::SelectAll = ~0x08; break;
			}
		}


	private:


	};

}
