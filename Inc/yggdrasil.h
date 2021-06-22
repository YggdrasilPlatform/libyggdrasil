 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Yggdrasil -                           *
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
  *  @file yggdrasil.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Main include file for libyggdrasil. This is the only header you'll ever need to include!
  */

#pragma once

#define ASGARD 		1
#define MIDGARD 	2

// C++ headers
#if defined(__cplusplus) && !defined(YGGDRASIL_USE_C_INTERFACE)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/registers.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>
	#include <cpp/common/math.hpp>

	#if BOARD == ASGARD
		#include <cpp/asgard/asgard.hpp>
	#elif BOARD == MIDGARD
		#include <cpp/midgard/midgard.hpp>
	#else
		#error "No board selected. Choose one with '#define BOARD <BOARD_NAME>' before '#include <yggdrasil.h>'!"
	#endif

	#include <cpp/yggdrasil/yggdrasil.hpp>

	#include <cpp/common/frontend/interrupts.hpp>

// C headers
#else

	#if BOARD == ASGARD
		#include <c/asgard/asgard.h>
	#elif BOARD == MIDGARD
		#include <c/midgard/midgard.h>
	#else
		#error "No board selected. Choose one with '#define BOARD <BOARD_NAME>' before '#include <yggdrasil.h>'!"
	#endif

	#include <c/yggdrasil/yggdrasil.h>

#endif

// CMSIS DSP Library headers
#if defined(YGGDRASIL_USE_CMSIS_DSP)

	#include <c/cmsis/dsp/arm_common_tables.h>
	#include <c/cmsis/dsp/arm_const_structs.h>
	#include <c/cmsis/dsp/arm_helium_utils.h>
	#include <c/cmsis/dsp/arm_math.h>
	#include <c/cmsis/dsp/arm_mve_tables.h>
	#include <c/cmsis/dsp/arm_sorting.h>
	#include <c/cmsis/dsp/arm_vec_fft.h>
	#include <c/cmsis/dsp/arm_vec_filtering.h>
	#include <c/cmsis/dsp/arm_vec_math.h>

#endif

#if !defined(YGGDRASIL_PERIPHERAL_DEFS)
	#warning "Standard peripheral definitions won't be added. Add them with '#define YGGDRASIL_PERIPHERAL_DEFS'!"
#endif

#include <init.h>
