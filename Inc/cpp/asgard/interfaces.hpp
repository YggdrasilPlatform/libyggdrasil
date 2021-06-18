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

#include <cpp/asgard/driver/gpio.hpp>
#include <cpp/asgard/driver/i2c.hpp>

#include <cpp/asgard/core/cortex.hpp>

//#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	namespace bsp {

		/**
		 * @brief GPIO Port definitions
		 * @{
		 */
		using GPIOPortA = bsp::drv::GPIOPort<0, bsp::asg::drv::GPIOPort>;
		using GPIOPortB = bsp::drv::GPIOPort<16, bsp::asg::drv::GPIOPort>;
		using GPIOPortC = bsp::drv::GPIOPort<32, bsp::asg::drv::GPIOPort>;
		using GPIOPortD = bsp::drv::GPIOPort<48, bsp::asg::drv::GPIOPort>;
		using GPIOPortE = bsp::drv::GPIOPort<64, bsp::asg::drv::GPIOPort>;
		using GPIOPortF = bsp::drv::GPIOPort<80, bsp::asg::drv::GPIOPort>;
		using GPIOPortG = bsp::drv::GPIOPort<96, bsp::asg::drv::GPIOPort>;
		using GPIOPortH = bsp::drv::GPIOPort<112, bsp::asg::drv::GPIOPort>;
		using GPIOPortI = bsp::drv::GPIOPort<128, bsp::asg::drv::GPIOPort>;
		using GPIOPortJ = bsp::drv::GPIOPort<144, bsp::asg::drv::GPIOPort>;
		using GPIOPortK = bsp::drv::GPIOPort<160, bsp::asg::drv::GPIOPort>;
		/** @} */

		using I2CA = bsp::drv::I2C<1, bsp::asg::drv::I2C>;
		using I2CB = bsp::drv::I2C<3, bsp::asg::drv::I2C>;
		using I2CC = bsp::drv::I2C<4, bsp::asg::drv::I2C>;
		using I2CD = bsp::drv::I2C<0, bsp::asg::drv::I2C>;

    	static constexpr auto& LD1 = GPIOPortJ::Pin<0>;
		static constexpr auto& LDA = LD1;
		static constexpr auto& LedBlue = LD1;
		static constexpr auto& LD2 = GPIOPortJ::Pin<1>;
		static constexpr auto& LDB = LD2;
		static constexpr auto& LedRed = LD2;
		static constexpr auto& LD3 = GPIOPortJ::Pin<2>;
		static constexpr auto& LDC = LD3;
		static constexpr auto& LedYellow = LD3;
		static constexpr auto& LD4 = GPIOPortJ::Pin<3>;
		static constexpr auto& LDD = LD4;
		static constexpr auto& LedGreen = LD4;

		static constexpr auto& ButtonA = GPIOPortJ::Pin<4, drv::Active::Low>;
		static constexpr auto& ButtonB = GPIOPortJ::Pin<5, drv::Active::Low>;
		static constexpr auto& ButtonC = GPIOPortJ::Pin<6, drv::Active::Low>;
		static constexpr auto& ButtonD = GPIOPortJ::Pin<7, drv::Active::Low>;

		static constexpr auto& LeftJoyStickButton = GPIOPortE::Pin<9, drv::Active::Low>;
		static constexpr auto& RightJoyStickButton = GPIOPortE::Pin<7, drv::Active::Low>;
	}

//#endif
