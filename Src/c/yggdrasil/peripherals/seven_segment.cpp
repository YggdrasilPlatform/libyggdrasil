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
  *  @file yggdrasil/peripherals/pressure_sensor.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the RV-3028-C7 RTC
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/seven_segment.h>
	#include <yggdrasil.h>


	using SevenSegment = bsp::ygg::prph::SevenSegment;

	C_LINKAGE void yggdrasil_SevenSegment_SetUnsigned(u16 value) {
		SevenSegment::setUnsigned(value);
	}

	C_LINKAGE void yggdrasil_SevenSegment_SetSigned(i16 value) {
		SevenSegment::setSigned(value);
	}

	C_LINKAGE void yggdrasil_SevenSegment_SetHexadecimal(u16 value) {
		SevenSegment::setHexadecimal(value);
	}

	C_LINKAGE void yggdrasil_SevenSegment_SetFloatingPoint(float value) {
		SevenSegment::setFloatingPoint(value);
	}

	C_LINKAGE void yggdrasil_SevenSegment_SetDigit(char value) {
		SevenSegment::setDigit(value);
	}

	C_LINKAGE void yggdrasil_SevenSegment_EnableDigit(u8 number) {
		SevenSegment::enableDigit(number);
	}

	C_LINKAGE void yggdrasil_SevenSegment_Disable() {
		SevenSegment::disable();
	}

#endif
