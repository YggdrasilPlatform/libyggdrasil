 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file c/asgard/driver/i2c.h
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief I2C abstraction implementation for Asgard
  */

#include <c/common/types.h>

/**
 * @brief I2C handle type
 */
typedef struct {
	u8 interfaceNumber;
	int fileHandle;
} i2c_t;

/**
 * @brief I2C initialization
 * @return Success
 */
C_LINKAGE bool yggdrasil_I2C_Init(i2c_t i2c);

/**
 * @brief I2C deinitialization
 * @return Success
 */
C_LINKAGE bool yggdrasil_I2C_Deinit(i2c_t i2c);

/**
 * @brief I2C write
 *
 * @param i2c I2C handle
 * @param address I2C device address
 * @param data Data to transmit
 * @param size Size of the data to transmit
 */
C_LINKAGE void yggdrasil_I2C_Write(i2c_t i2c, u8 address, void *data, size_t size);

/**
 * @brief I2C write register
 *
 * @param i2c I2C handle
 * @param address I2C device address
 * @param reg I2C device register address
 * @param data Data to transmit
 * @param size Size of the data to transmit
 */
C_LINKAGE void yggdrasil_I2C_WriteRegister(i2c_t i2c, u8 address, u8 reg, void *data, size_t size);
/**
 * @brief I2C read
 *
 * @param i2c I2C handle
 * @param address I2C device address
 * @param[out] data Received data
 * @param size Size of the data to receive
 */
C_LINKAGE void yggdrasil_I2C_Read(i2c_t i2c,  u8 address, void *data, size_t size);

/**
 * @brief I2C read register
 *
 * @param i2c I2C handle
 * @param address I2C device address
 * @param reg I2C device register address
 * @param[out] data Received data
 * @param size Size of the data to receive
 */
C_LINKAGE void yggdrasil_I2C_ReadRegister(i2c_t i2c, u8 address, u8 reg, void *data, size_t size);



