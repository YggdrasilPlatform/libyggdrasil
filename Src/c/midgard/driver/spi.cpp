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
  *  @file midgard/driver/spi.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief SPI abstraction implementation for Midgard
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS) && BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/spi.h>

	#include <yggdrasil.h>

	#include <math.h>


	/**
	 * @brief SPI initialization
	 */
	C_LINKAGE bool yggdrasil_SPI_Init(spi_t spi) {
		return true;
	}

	/**
	 * @brief SPI write
	 *
	 * @param spi SPI handle
	 * @param data Data to transmit
	 * @param size Size of the data to transmit
	 */
	C_LINKAGE void yggdrasil_SPI_Write(spi_t spi, void *data, size_t size) {
		HAL_SPI_Transmit(spi.interface, (u8 *)data, size, HAL_MAX_DELAY);
	}

	/**
	 * @brief SPI read
	 *
	 * @param spi SPI handle
	 * @param[out] data Received data
	 * @param size Size of the data to receive
	 */
	C_LINKAGE void yggdrasil_SPI_Read(spi_t spi, void *data, size_t size) {
		HAL_SPI_Receive(spi.interface, (u8 *)data, size, HAL_MAX_DELAY);
	}

	/**
	 * @brief Set the spi mode (CPOL and CPHA)
	 *
	 * @param mode SPI mode
	 * @note This function wait until the SPI is not busy anymore and then the mode change will take place
	 */
	C_LINKAGE void yggdrasil_SPI_SetMode(spi_t spi, SPIMode mode) {
		while (HAL_SPI_GetState(spi.interface) == HAL_SPI_STATE_BUSY);
		spi.interface->Instance->CR1 = (spi.interface->Instance->CR1 & ~0b11) | mode;
	}


#endif
