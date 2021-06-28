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
  *  @file c/yggdrasil/peripherals/pressure_sensor.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the LPS22HBTR pressure sensor
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/rgb_matrix.h>
	#include <yggdrasil.h>


	using RGBMatrix = bsp::ygg::prph::RGBMatrix;

	C_LINKAGE void yggdrasil_RGBMatrix_Init(void) {
		RGBMatrix::init();
	}

	C_LINKAGE void yggdrasil_RGBMatrix_Enable(void) {
		RGBMatrix::enable();
	}

	C_LINKAGE void yggdrasil_RGBMatrix_Disable(void) {
		RGBMatrix::disable();
	}

	C_LINKAGE void yggdrasil_RGBMatrix_Clear(void) {
		RGBMatrix::clear();
	}

	C_LINKAGE void yggdrasil_RGBMatrix_SetLed(u8 index, RGBA8 color) {
		RGBMatrix::setLed(index, bsp::bit_cast<bsp::ygg::RGBA8>(color));
	}

	C_LINKAGE void yggdrasil_RGBMatrix_SetLedMasked(u16 enableMask, RGBA8 color) {
		RGBMatrix::setLedMasked(enableMask, bsp::bit_cast<bsp::ygg::RGBA8>(color));

	}

	C_LINKAGE void yggdrasil_RGBMatrix_Dice(u8 number, RGBA8 color) {
		RGBMatrix::dice(number, bsp::bit_cast<bsp::ygg::RGBA8>(color));
	}

	C_LINKAGE void yggdrasil_RGBMatrix_Flush(void) {
		RGBMatrix::flush();
	}

#endif
