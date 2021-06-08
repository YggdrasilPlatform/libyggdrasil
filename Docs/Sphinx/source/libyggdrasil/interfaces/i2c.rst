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

.. tabs::

    .. code-tab:: c

        const u8 deviceAddress = 0x42;

        // Read data directly
        u8 value = 0;
        yggdrasil_I2C_Read(I2CA, deviceAddress, &value, sizeof(u8));

        const u8 registerAddress = 0x11;

        // Read data from a register
        u8 registerValue = 0;
        yggdrasil_I2C_ReadRegister(I2CA, deviceAddress, registerAddress, &registerValue, sizeof(u8));

    .. code-tab:: cpp

        constexpr u8 DeviceAddress = 0x42;

        // Read data directly
        auto value = bsp::I2CA::read<u8>(DeviceAddress);

        constexpr u8 RegisterAddress = 0x11;

        // Read data from a register
        auto registerValue = bsp::I2CA::read<u8>(DeviceAddress, RegisterAddress);

And this code to write data:

.. tabs::

    .. code-tab:: c

        const u8 deviceAddress = 0x42;

        // Write 0xFF directly
        u8 value = 0xFF;
        yggdrasil_I2C_Write(I2CA, deviceAddress, &value, sizeof(u8));

        const u8 registerAddress = 0x22;

        // Write 0x55 to a register
        value = 0x55;
        yggdrasil_I2C_WriteRegister(I2CA, deviceAddress, registerAddress, &value, sizeof(u8));

    .. code-tab:: cpp

        constexpr u8 DeviceAddress = 0x42;

        // Write 0xFF directly
        bsp::I2CA::write<u8>(DeviceAddress, 0xFF);

        constexpr u8 RegisterAddress = 0x22;

        // Write 0x55 to a register
        bsp::I2CA::write<u8>(DeviceAddress, RegisterAddress, 0x55);


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


Custom I2C
----------

In order to control a I2C that has not been pre-defined by libyggdrasil, first it needs to be properly configured through the project's .ioc file. 
Once this is done, the new I2C can be defined like this:

.. tabs::

    .. code-tab:: c

        i2c_t MyI2C = { &hi2c1 };

    .. code-tab:: cpp

        using MyI2C = bsp::drv::I2C<&hi2c1, bsp::mid::drv::I2C>;

and then used like all the other I2C.