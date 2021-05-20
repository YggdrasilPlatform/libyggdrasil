 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file asgard/interfaces.hpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Interface definitions for Asgard
  */

#pragma once

#include <asgard/driver/gpio.hpp>
#include <asgard/driver/i2c.hpp>

#include <asgard/core/cortex.hpp>

//#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	namespace bsp {

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using GPIOPortA = bsp::drv::GPIOPort<0x5000'2000, bsp::asg::drv::GPIOPort>;
		using GPIOPortB = bsp::drv::GPIOPort<0x5000'3000, bsp::asg::drv::GPIOPort>;
		using GPIOPortC = bsp::drv::GPIOPort<0x5000'4000, bsp::asg::drv::GPIOPort>;
		using GPIOPortD = bsp::drv::GPIOPort<0x5000'5000, bsp::asg::drv::GPIOPort>;
		using GPIOPortE = bsp::drv::GPIOPort<0x5000'6000, bsp::asg::drv::GPIOPort>;
		using GPIOPortF = bsp::drv::GPIOPort<0x5000'7000, bsp::asg::drv::GPIOPort>;
		using GPIOPortG = bsp::drv::GPIOPort<0x5000'8000, bsp::asg::drv::GPIOPort>;
		using GPIOPortH = bsp::drv::GPIOPort<0x5000'9000, bsp::asg::drv::GPIOPort>;
		using GPIOPortI = bsp::drv::GPIOPort<0x5000'A000, bsp::asg::drv::GPIOPort>;
		using GPIOPortJ = bsp::drv::GPIOPort<0x5000'B000, bsp::asg::drv::GPIOPort>;
		using GPIOPortK = bsp::drv::GPIOPort<0x5000'C000, bsp::asg::drv::GPIOPort>;
		using GPIOPortZ = bsp::drv::GPIOPort<0x5400'4000, bsp::asg::drv::GPIOPort>;
		/** @} */

		using I2CA = bsp::drv::I2C<1, bsp::asg::drv::I2C>;	// I2C1
	}

//#endif
