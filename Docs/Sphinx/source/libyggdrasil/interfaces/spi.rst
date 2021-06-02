.. _SpiInterface:

SPI Interface
=============

.. note::
    SPI is a fast serial interface made for talking to sensors, ICs and other peripherals. The Seeed and Pmod connectors allow for
    additional SPI modules to be connected. 


Simple Usage
------------

Reading from and writing to a SPI device is as simple as calling the ``read`` and ``write`` functions of the relevant 
SPI interface. For example, for a device connected to the PMOD A connector, the following code can be used to read data:

.. code-block:: cpp

    auto word = bsp::SPIC::read<u32>();

    auto tenBytes = bsp::SPIC::read<std::array<u8, 10>>();

And this code to write data:

.. code-block:: cpp
    
    bsp::SPIC::write<u32>(0x1234'5678);

    bsp::SPIC::write<std::array<u8, 5>>({ 1, 2, 3, 4, 5 });

.. important::
    All SPI interfaces are configured in Full-Duplex Master, MSB First, Mode 3 with a data rate of 6.75 MBits/s.
    If other settings are needed, they can be changed in the project's .ioc file.

Available peripherals
---------------------

+-----------------+-------------------+--------------+
| Peripheral      | Bus               | Chip Enable  |
+=================+===================+==============+
| RGB LED Matrix  | SPIA              | ``RGB_EN``   |
+-----------------+-------------------+--------------+
| Pressure Sensor | SPIA              | Hardware NSS |
+-----------------+-------------------+--------------+
| PMOD A          | SPIC              | Hardware NSS |
+-----------------+-------------------+--------------+
| Raspberry Port  | SPIB              | ``SPIACE``   |
+-----------------+-------------------+--------------+
| Raspberry Port  | SPIC              | Hardware NSS |
+-----------------+-------------------+--------------+
