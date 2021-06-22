 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Asgard  -                             *
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
  *  @file asgard/driver/gpio.cpp
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief GPIO Pin abstraction implementation for Asgard
  */

#include <yggdrasil.h>

#if BOARD == ASGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/asgard/driver/gpio.h>



  #include <unistd.h>
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/mman.h>
  #include <string>

	extern "C" bool yggdrasil_GPIO_Init(gpio_t gpio) {
			int fd = open("/sys/class/gpio/export", O_WRONLY);
			if (fd == -1) return false;

			auto value = std::to_string(gpio.pinNumber);
			write(fd, value.c_str(), value.length());
			close(fd);

			return true;
	}

  C_LINKAGE bool yggdrasil_GPIO_Deinit(gpio_t gpio) {
			int fd = open("/sys/class/gpio/unexport", O_WRONLY);
			if (fd == -1) return false;

			auto value = std::to_string(gpio.pinNumber);
			write(fd, value.c_str(), value.length());
			close(fd);

			return true;
  }

  C_LINKAGE bool yggdrasil_GPIO_MakeOutput(gpio_t gpio) {
			int fd = open(("/sys/class/gpio/gpio" + std::to_string(gpio.pinNumber) + "/direction").c_str(), O_WRONLY);
			if (fd == -1) return false;

			write(fd, "out", 3);
			close(fd);

      return true;
  }

  C_LINKAGE bool yggdrasil_GPIO_MakeInput(gpio_t gpio) {
			int fd = open(("/sys/class/gpio/gpio" + std::to_string(gpio.pinNumber) + "/direction").c_str(), O_WRONLY);
			if (fd == -1) return false;

			write(fd, "in", 2);
			close(fd);

      return true;
  }

	C_LINKAGE bool yggdrasil_GPIO_Get(gpio_t gpio) {
			int fd = open(("/sys/class/gpio/gpio" + std::to_string(gpio.pinNumber) + "/value").c_str(), O_RDONLY);
			if (fd == -1) return false;

			char buffer[2] = { 0 };
			read(fd, buffer, sizeof(buffer));
			close(fd);

			bool result = buffer[0] == '1';

      return gpio.lowActive ? !result : result;
	}

	C_LINKAGE void yggdrasil_GPIO_Set(gpio_t gpio, bool state) {
			state = gpio.lowActive ? !state : state;

			int fd = open(("/sys/class/gpio/gpio" + std::to_string(gpio.pinNumber) + "/value").c_str(), O_WRONLY);
			if (fd == -1) return;

			write(fd, state ? "1" : "0", 1);
			close(fd);
	}

	C_LINKAGE void yggdrasil_GPIO_Toggle(gpio_t gpio) {
		yggdrasil_GPIO_Set(gpio, !yggdrasil_GPIO_Get(gpio));
	}

#endif
