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
  *  @file common/midgard/override_funcs.c
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Function overriding for Midgard
  */

#include <yggdrasil.h>

#if BOARD == MIDGARD

	#include <stm32f7xx_hal.h>

	extern DSI_HandleTypeDef hdsi;

	/**
	  * @brief  DCS or Generic short/long write command
	  * @param  NbrParams: Number of parameters. It indicates the write command mode:
	  *                 If inferior to 2, a long write command is performed else short.
	  * @param  pParams: Pointer to parameter values table.
	  * @retval HAL status
	  */
	void DSI_IO_WriteCmd(uint32_t NbrParams, uint8_t *pParams)
	{
	  if(NbrParams <= 1)
	  {
	   HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, pParams[0], pParams[1]);
	  }
	  else
	  {
	   HAL_DSI_LongWrite(&hdsi,  0, DSI_DCS_LONG_PKT_WRITE, NbrParams, pParams[NbrParams], pParams);
	  }
	}

	int __io_putchar(int ch){
		ITM_SendChar(ch);

		return ch;
	}

#endif
