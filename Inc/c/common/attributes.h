 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
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
  *  @file cpp/common/attributes.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Commonly used C++ and GNU attributes
  */

#pragma once

#define LIKELY 					__attribute__((likely))
#define UNLIKELY 				__attribute__((unlikely))
#define DEPRECTATED(reason) 	__attribute__((deprecated))
#define NO_RETURN 				__attribute__((noreturn))

#define WEAK 					__attribute__((weak))
#define ALWAYS_INLINE 			__attribute__((always_inline)) inline
#define PACKED 					__attribute__((packed))
#define NAKED 					__attribute__((naked))
#define SECTION(name) 			__attribute__((section(name)))
#define ALIGNED(alignment) 		__attribute__((aligned(alignment)))

#if defined(__cplusplus)
	#define C_LINKAGE extern "C"
#else
	#define C_LINKAGE
#endif
