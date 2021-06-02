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

/**
 * @brief Timer initialization
 *
 * @param tim Timer handel
 */
C_LINKAGE bool yggdrasil_TIM_Init(tim_t tim);

/**
 * @brief Timer enable
 *
 * @param tim Timer handel
 */
C_LINKAGE void yggdrasil_TIM_Enable(tim_t tim);

/**
 * @brief Timer disable
 *
 * @param tim Timer handel
 */
C_LINKAGE void yggdrasil_TIM_Disable(tim_t tim);

/**
 * @brief Get the counter value
 *
 * @param tim Timer handel
 * @return Actual timer count
 */
C_LINKAGE u32  yggdrasil_TIM_GetCount(tim_t tim);

/**
 * @brief Set the counter value
 *
 * @param tim Timer handel
 * @param cnt New timer value
 */
C_LINKAGE void yggdrasil_TIM_SetCount(tim_t tim, u32 cnt);

/**
 * @brief Reset the counter value
 *
 * @param tim Timer handel
 */
C_LINKAGE void yggdrasil_TIM_ResetCount(tim_t tim);

/**
 * @brief Get the pwm frequency
 * @note The frequency is for all channels the same
 *
 * @param tim Timer handel
 * @return Frequency in Hz
 */
C_LINKAGE u32  yggdrasil_TIM_GetPwmFrequency(tim_t tim);

/**
 * @brief Set the pwm frequency and (optional) the maximal ticks within on cycle for all channels
 * @note The actual duty cycle for all channels will be restored after the changes
 * @note Implement a proper error handling, the function does not guarantee to be successful
 *
 * @param tim Timer handel
 * @param f_hz new frequency in hz
 * @param resolution of the pwm, for 0 the actual value will be used
 *
 * @return True when the adjustment was possible, false when the parameter did not match
 */
C_LINKAGE bool yggdrasil_TIM_SetPwmFrequency(tim_t tim, u32 f_hz, u32 resolution);


/**
 * @brief Start PWM generation for the channel
 * @Note A duty cycle should be set with setDuty()
 *
 * @param tim Timer handel
 * @return True when successfully started, false when not
 */
C_LINKAGE bool yggdrasil_TIM_Channel_StartPwm(tim_t tim);

/**
 * @brief Stop PWM generation for the channel
 * @note This function disables the counter when no PWM channel is active
 *
 * @param tim Timer handel
 * @return True when successfully stopped, false when not
 */
C_LINKAGE bool yggdrasil_TIM_Channel_StopPwm(tim_t tim);

/**
 * @brief Start set pwm polarity
 *
 * @param tim Timer handel
 * @param highActive Set channel to high active when true
 * @return True when successfully switched, false when not
 */
C_LINKAGE bool yggdrasil_TIM_Channel_SetPolarityHigh(tim_t tim, bool highActive);

/**
 * @brief Set the duty cycle as a float value
 *
 * @param tim Timer handel
 * @param dutyCycle Duty cycle in % [0 100]
 */
C_LINKAGE bool yggdrasil_TIM_Channel_SetDutyCycle(tim_t tim, float dutyCycle);


/* Profile counter functions */

/**
 * @brief Start the counter
 *
 * @param tim Timer handel
 */
C_LINKAGE void yggdrasil_Profilecounter_Start(tim_t tim);

/**
 * @brief Stop the counter
 *
 * @param tim Timer handel
 */
C_LINKAGE void yggdrasil_Profilecounter_Stop(tim_t tim);

/**
 * @brief Reset the counter to 0
 *
 * @param tim Timer handel
 */
C_LINKAGE void yggdrasil_Profilecounter_Reset(tim_t tim);

/**
 * @brief Get the time to an overflow
 *
 * @param tim Timer handel
 * @return Time to an overflow in a u64
 */
C_LINKAGE u64  yggdrasil_Profilecounter_GetTimeToOverflow(tim_t tim);

/**
 * @brief Get the time to an overflow formatted as a string
 *
 * @return Time to an overflow formatted as a string
 */
C_LINKAGE void yggdrasil_Profilecounter_GetFormattedTimeToOverflow(tim_t tim, char *buffer, size_t size);

/**
 * @brief Get the time passed time since the start
 *
 * @param tim Timer handel
 * @return Passed time in a u64
 */
C_LINKAGE u64  yggdrasil_Profilecounter_GetPassedTime(tim_t tim);

/**
 * @brief Get the time passed time since the start
 *
 * @param tim Timer handel
 * @return Passed time formatted as a string
 */
C_LINKAGE void yggdrasil_Profilecounter_GetFormattedPassedTime(tim_t tim, char *buffer, size_t size);


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

/**
 * @brief Initialization function for the encoder
 * @note Default encoder mode is 96 steps per turn
 *
 * @param tim Timer handel
 * @return True when successfully enabled, false when not
 */
C_LINKAGE bool yggdrasil_Encoder_Init(tim_t tim);

/**
 * @brief Enable the encoder mode
 * @note This does only work for timer with a encoder modul
 *
 * @param tim Timer handel
 * @return True when successfully enabled, false when not
 */
C_LINKAGE bool yggdrasil_Encoder_Enable(tim_t tim);

/**
 * @brief Disable the encoder mode
 * @note This does only work for timer with a encoder modul
 *
 * @param tim Timer handel
 * @return True when successfully disabled, false when not
 */
C_LINKAGE bool yggdrasil_Encoder_Disable(tim_t tim);

/**
 * @brief Get the counter value
 * @note This does only work for timer with a encoder modul
 *
 * @param tim Timer handel
 * @return Actual timer count
 */
C_LINKAGE u32  yggdrasil_Encoder_GetCount(tim_t tim);

/**
 * @brief Set the encoder counter value
 *
 * @param tim Timer handel
 * @param cnt New counter value
 */
C_LINKAGE void yggdrasil_Encoder_SetCount(tim_t tim, u32 cnt);

/**
 * @brief Get the direction of the last rotation
 * @note This bit might not be accurate while turning the encoder
 *
 * @param tim Timer handel
 * @return Direction
 */
C_LINKAGE enum EncoderDirection yggdrasil_Encoder_GetDirection(tim_t tim);

/**
 * @brief Set the mode of the encoder (48 or 96 counts per turn)
 *
 * @param tim Timer handel
 * @param mode Mode selection
 */
C_LINKAGE void yggdrasil_Encoder_SetMoce(tim_t tim, enum EncoderMode mode);


