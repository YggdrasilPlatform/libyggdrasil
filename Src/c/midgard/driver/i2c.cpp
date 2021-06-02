 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Midgard -                             *
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
  *  @file midgard/driver/i2c.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief I2C abstraction implementation for Midgard
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS) && BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/i2c.h>

	#include <yggdrasil.h>

	#include <math.h>


	C_LINKAGE bool yggdrasil_I2C_Init(i2c_t i2c) {
		return true;
	}

	C_LINKAGE void yggdrasil_I2C_Write(i2c_t i2c, u8 address, void *data, size_t size) {
		HAL_I2C_Master_Transmit(i2c.interface, address, (u8 *)data, size, HAL_MAX_DELAY);
	}

	C_LINKAGE void yggdrasil_I2C_Read(i2c_t i2c, u8 address, void *data, size_t size) {
		HAL_I2C_Master_Receive(i2c.interface, address, (u8 *)data, size, HAL_MAX_DELAY);
	}

	C_LINKAGE void yggdrasil_I2C_ReadRegister(i2c_t i2c, u8 address, u8 reg, void *data, size_t size) {
		HAL_I2C_Master_Transmit(i2c.interface, address, &reg, sizeof(u8), HAL_MAX_DELAY);
		HAL_I2C_Master_Receive(i2c.interface, address, (u8 *)data, size, HAL_MAX_DELAY);
	}


#endif
