.. _I2cInterface:

I2C Interface
=============

.. note::
    I2C a serial interface mainly used to talk to sensors, peripherals and ICs located on the same circuit board as the microcontroller.
    On Yggdrasil, almost all sensors are connected to it with the ability to connect extra peripherals through the Seeed or PMod connectors.


Simple Usage
------------

Reading from and writing to a I2C device is as simple as calling the ``read`` and ``write`` functions of the relevant 
I2C interface. For example, for a sensor connected to the Grove A connector, the following code can be used to read data:

.. code-block:: cpp

    constexpr u8 DeviceAddress = 0x42;

    // Read data directly
    auto value = bsp::I2CA::read<u8>(DeviceAddress);

    constexpr u8 RegisterAddress = 0x11;

    // Read data from a register
    auto registerValue = bsp::I2CA::read<u8>(DeviceAddress, RegisterAddress);

And this code to write data:

.. code-block:: cpp

    constexpr u8 DeviceAddress = 0x42;

    // Write 0xFF directly
    bsp::I2CA::write<u8>(DeviceAddress, 0xFF);

    constexpr u8 RegisterAddress = 0x22;

    // Write 0x55 to a register
    bsp::I2CA::read<u8>(DeviceAddress, RegisterAddress, 0x55);


.. important::
    All I2C interfaces are configured to 100kHz Standard mode. This is the default and works for all on-board peripherals as well as most external peripherals.
    If a connected peripheral requires a different speed or faster communication is desired, the speed may be changed in the projects .ioc file. However, this can cause
    the onboard peripherals to no longer be usable.

Available peripherals
---------------------

+---------------+-------------------+---------+
| Peripheral    | Bus               | Address |
+===============+===================+=========+
| PMOD A        | I2CA              | None    |
+---------------+-------------------+---------+
| PMOD B        | I2CB              | None    |
+---------------+-------------------+---------+
| Grove A       | I2CA              | None    |
+---------------+-------------------+---------+
| Grove B       | I2CB              | None    |
+---------------+-------------------+---------+
| Raspberry     | I2CA & I2CB       | None    |
+---------------+-------------------+---------+
| 6 Axis        | I2CA              | 0xD2    |
+---------------+-------------------+---------+
| Color         | I2CA              | 0x52    |
+---------------+-------------------+---------+
| Humidity      | I2CA              | 0x88    |
+---------------+-------------------+---------+
| RTC           | I2CA              | 0xA4    |
+---------------+-------------------+---------+
| Joystick ADC  | I2CA              | 0x90    |
+---------------+-------------------+---------+
| Codec         | I2CD              | 0x40    |
+---------------+-------------------+---------+
| Touch Screen  | I2CC              | 0x54    |
+---------------+-------------------+---------+
| DCMI          | I2CD              | None    |
+---------------+-------------------+---------+
| USB Hub       | I2CD              | 0x58    |
+---------------+-------------------+---------+
| USB C         | I2CD              | 0x50    |
+---------------+-------------------+---------+
