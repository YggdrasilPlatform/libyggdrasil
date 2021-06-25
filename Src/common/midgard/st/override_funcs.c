
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
