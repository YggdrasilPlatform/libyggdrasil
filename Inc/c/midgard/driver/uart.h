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
  *  @file c/midgard/driver/uart.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief UART abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

typedef struct {
	UART_HandleTypeDef *interface;
} uart_t;

/**
 * @brief UART initialization
 *
 * @param uart UART handle
 */
C_LINKAGE bool yggdrasil_UART_Init(uart_t uart);

/**
 * @brief UART transmit
 *
 * @param uart UART handle
 * @param data Data to transmit
 * @param size Size of the data to transmit
 */
C_LINKAGE void yggdrasil_UART_Transmit(uart_t uart, void *data, size_t size);

/**
 * @brief UART receive
 *
 * @param uart UART handle
 * @param data Data to transmit
 * @param size Size of the data to transmit
 */
C_LINKAGE void yggdrasil_UART_Receive(uart_t uart, void *data, size_t size);
