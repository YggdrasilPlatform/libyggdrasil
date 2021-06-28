 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
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
  *  @file c/midgard/driver/spi.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief SPI abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

/**
 * @brief SPI handle type
 */
typedef struct {
	SPI_HandleTypeDef *interface;
} spi_t;


/**
 * @brief SPI modes
 */
enum SPIMode {
	SPIMode_0 = 0b00,  	///< CPOL = 0  |  CPHA = 0
	SPIMode_1 = 0b01,	///< CPOL = 0  |  CPHA = 1
	SPIMode_2 = 0b10,	///< CPOL = 1  |  CPHA = 0
	SPIMode_3 = 0b11,	///< CPOL = 1  |  CPHA = 1
};

/**
 * @brief SPI initialization
 * 
 * @param spi SPI handel
 * @return Success
 */
C_LINKAGE bool yggdrasil_SPI_Init(spi_t spi);

/**
 * @brief SPI deinitialization
 * 
 * @param spi SPI handel
 * @return Success
 */
C_LINKAGE bool yggdrasil_SPI_Deinit(spi_t spi);

/**
 * @brief SPI write
 *
 * @param spi SPI handle
 * @param data Data to transmit
 * @param size Size of the data to transmit
 */
C_LINKAGE void yggdrasil_SPI_Write(spi_t spi, void *data, size_t size);

/**
 * @brief SPI read
 *
 * @param spi SPI handle
 * @param[out] data Received data
 * @param size Size of the data to receive
 */
C_LINKAGE void yggdrasil_SPI_Read(spi_t spi,  void *data, size_t size);

/**
 * @brief Set the spi mode (CPOL and CPHA)
 *
 * @param spi SPI handle
 * @param mode SPI mode
 * @note This function wait until the SPI is not busy anymore and then the mode change will take place
 */
C_LINKAGE void yggdrasil_SPI_SetMode(spi_t spi, enum SPIMode mode);
