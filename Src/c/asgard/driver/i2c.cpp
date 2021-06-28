 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Asgard -                              *
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
  *  @file c/asgard/driver/i2c.cpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief I2C abstraction implementation for Asgard
  */

#include <yggdrasil.h>

#if BOARD == ASGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/asgard/driver/i2c.h>

	#include <math.h>
	#include <vector>
	#include <string>

	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <sys/stat.h>
	#include <linux/i2c-dev.h>

	C_LINKAGE bool yggdrasil_I2C_Init(i2c_t i2c) {
		i2c.fileHandle = open(("/dev/i2c-" + std::to_string(i2c.interfaceNumber)).c_str(), O_RDWR);
		return i2c.fileHandle != -1;
	}

	C_LINKAGE bool yggdrasil_I2C_Deinit(i2c_t i2c) {
		close(i2c.fileHandle);
		return true;
	}

	C_LINKAGE void yggdrasil_I2C_Write(i2c_t i2c, u8 address, void *data, size_t size) {
		::ioctl(i2c.fileHandle, I2C_SLAVE, address >> 1);
		::write(i2c.fileHandle, static_cast<u8*>(data), size);
	}

	C_LINKAGE void yggdrasil_I2C_WriteRegister(i2c_t i2c, u8 address, u8 reg, void *data, size_t size) {
		std::vector<u8> buffer(size + 1, 0x00);
		buffer[0] = reg;
		std::memcpy(&buffer[1], data, size);
		yggdrasil_I2C_Write(i2c, address, buffer.data(), buffer.size());

	}

	C_LINKAGE void yggdrasil_I2C_Read(i2c_t i2c, u8 address, void *data, size_t size) {
		::ioctl(i2c.fileHandle, I2C_SLAVE, address >> 1);
		::read(i2c.fileHandle, static_cast<u8*>(data), size);
	}

	C_LINKAGE void yggdrasil_I2C_ReadRegister(i2c_t i2c, u8 address, u8 reg, void *data, size_t size) {
		yggdrasil_I2C_Write(i2c, address, &reg, sizeof(u8));
		yggdrasil_I2C_Read(i2c, address, data, size);
	}


#endif
