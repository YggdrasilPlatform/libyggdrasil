#pragma once

#include <common/attributes.hpp>
#include <common/types.hpp>

namespace bsp::drv {
	struct Cooridnate {
		i16 x, y, z;
	};


	class SixAxisSensor {
	public:
		SixAxisSensor() = delete;

		static void init ();
		static Cooridnate getAcceleration () {


		};
		static Cooridnate getRotation ();
		static Cooridnate getTemperature ();

	private:
		static void writeRegister(u8 address, u8 data){};
		static i16 readRegister(u8 address){return 0;};

	};

}
