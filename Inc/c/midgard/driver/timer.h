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
  *  @file c/midgard/driver/timer.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Timer abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

typedef struct {
	TIM_HandleTypeDef *interface;
	size_t size;
	u8 channel;
} tim_t;


/* Basic tim functions */

C_LINKAGE bool yggdrasil_TIM_Init(tim_t tim);
C_LINKAGE void yggdrasil_TIM_Enable(tim_t tim);
C_LINKAGE void yggdrasil_TIM_Disable(tim_t tim);
C_LINKAGE u32  yggdrasil_TIM_GetCount(tim_t tim);
C_LINKAGE void yggdrasil_TIM_SetCount(tim_t tim, u32 cnt);
C_LINKAGE void yggdrasil_TIM_ResetCount(tim_t tim);
C_LINKAGE u32  yggdrasil_TIM_GetPwmFrequency(tim_t tim);
C_LINKAGE bool yggdrasil_TIM_SetPwmFrequency(tim_t tim, u32 f_hz, u32 resolution);


/* Channel functions */
C_LINKAGE bool yggdrasil_TIM_Channel_StartPwm(tim_t tim);
C_LINKAGE bool yggdrasil_TIM_Channel_StopPwm(tim_t tim);
C_LINKAGE bool yggdrasil_TIM_Channel_SetPolarityHigh(tim_t tim, bool highActive);
C_LINKAGE bool yggdrasil_TIM_Channel_SetDutyCycle(tim_t tim, float dutyCycle);


/* Profile counter functions */
C_LINKAGE void yggdrasil_Profilecounter_Start(tim_t tim);
C_LINKAGE void yggdrasil_Profilecounter_Stop(tim_t tim);
C_LINKAGE void yggdrasil_Profilecounter_Reset(tim_t tim);
C_LINKAGE u64  yggdrasil_Profilecounter_GetTimeToOverflow(tim_t tim);
C_LINKAGE void yggdrasil_Profilecounter_GetFormattedTimeToOverflow(tim_t tim, char *buffer, size_t size);
C_LINKAGE u64  yggdrasil_Profilecounter_GetPassedTime(tim_t tim);
C_LINKAGE void yggdrasil_Profilecounter_GetFormattedPassedTime(tim_t tim, char *buffer, size_t size);
C_LINKAGE void yggdrasil_Profilecounter_FormatToString(u64 passedTime, char *buffer, size_t size);

/* Encoder functions */
/**
 * @brief Last known turning direction of the encoder
 */
enum EncoderDirection {
	EncoderDirectionClockwise,
	EncoderDirectionCounterClockwise,
};

/**
 * @brief Modes for the encoder, 48 odr 96 steps per turn are possible
 */
enum EncoderMode {
	EncoderMode_48StepsPerTurn,
	EncoderMode_96StepsPerTurn
};

C_LINKAGE bool yggdrasil_Encoder_Init(tim_t tim);
C_LINKAGE bool yggdrasil_Encoder_Enable(tim_t tim);
C_LINKAGE bool yggdrasil_Encoder_Disable(tim_t tim);
C_LINKAGE u32  yggdrasil_Encoder_GetCount(tim_t tim);
C_LINKAGE void yggdrasil_Encoder_SetCount(tim_t tim, u32 cnt);
C_LINKAGE enum EncoderDirection yggdrasil_Encoder_GetDirection(tim_t tim);
C_LINKAGE void yggdrasil_Encoder_SetMoce(tim_t tim, enum EncoderMode mode);
