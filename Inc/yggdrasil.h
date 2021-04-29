/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                            - Top -                              *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil.hpp                                            *
  *  @ingroup top                                                   *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Top-Level include file for libyggdralis 			    *
  *  			                                                    *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#pragma once

#define YGGDRASIL	0
#define ASGARD 		1
#define MIDGARD 	2

// C++ headers
#if defined(__cplusplus)

	#include <common/attributes.hpp>
	#include <common/registers.hpp>
	#include <common/types.hpp>
	#include <common/utils.hpp>
	#include <common/math.hpp>

	#if BOARD == ASGARD
		#include <asgard/asgard.hpp>
	#elif BOARD == MIDGARD
		#include <midgard/midgard.hpp>
	#else
		#error "No board selected. Choose one with '#define BOARD <BOARD_NAME>' before '#include <yggdrasil.h>'!"
	#endif

	#include <yggdrasil/yggdrasil.hpp>

// C headers
#else

	#if BOARD == ASGARD
		#include <asgard/asgard.h>
	#elif BOARD == MIDGARD
		#include <midgard/midgard.h>
	#else
		#error "No board selected. Choose one with '#define BOARD <BOARD_NAME>' before '#include <yggdrasil.h>'!"
	#endif

	#include <yggdrasil/yggdrasil.h>

#endif

// CMSIS DSP Library headers
#if defined(YGGDRASIL_USE_CMSIS_DSP)

	#include <common/cmsis/dsp/arm_common_tables.h>
	#include <common/cmsis/dsp/arm_const_structs.h>
	#include <common/cmsis/dsp/arm_helium_utils.h>
	#include <common/cmsis/dsp/arm_math.h>
	#include <common/cmsis/dsp/arm_mve_tables.h>
	#include <common/cmsis/dsp/arm_sorting.h>
	#include <common/cmsis/dsp/arm_vec_fft.h>
	#include <common/cmsis/dsp/arm_vec_filtering.h>
	#include <common/cmsis/dsp/arm_vec_math.h>

#endif

#if !defined(YGGDRASIL_PERIPHERAL_DEFS)
	#warning "Standard peripheral definitions won't be added. Add them with '#define YGGDRASIL_PERIPHERAL_DEFS'!"
#endif
