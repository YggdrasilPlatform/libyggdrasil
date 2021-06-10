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

.. tabs::

    .. code-tab:: c

        u32 rxdata = 0;

        // Read an u32
        yggdrasil_SPI_Read(SPIC, &rxdata, sizeof(u32));
        

        u8 rxarray[10] = { 0 };

        // Read an array of 10 u8 
        yggdrasil_SPI_Read(SPIC, rxarray, sizeof(rxarray));


    .. code-tab:: cpp

        // Read an u32
        auto word = bsp::SPIC::read<u32>();

        // Read an array of 10 u8 
        auto tenBytes = bsp::SPIC::read<std::array<u8, 10>>();


And this code to write data:

.. tabs::

    .. code-tab:: c

        u32 txdata = 0x12345678;

        // Write an u32
        yggdrasil_SPI_Write(SPIC, &txdata, sizeof(u32));

        u8 txarray[5] = { 1, 2, 3, 4, 5 };

        // Write an array of 5 u8
        yggdrasil_SPI_Read(SPIC, txarray, sizeof(txarray));

    .. code-tab:: cpp
        
        // Write an u32
        bsp::SPIC::write<u32>(0x1234'5678);

        // Write an array of 5 u8
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
| Raspberry Port  | SPIB              | ``SPIBCE``   |
+-----------------+-------------------+--------------+
| Raspberry Port  | SPIC              | Hardware NSS |
+-----------------+-------------------+--------------+

Custom SPI
----------

In order to control a SPI that has not been pre-defined by libyggdrasil, first it needs to be properly configured through the project's .ioc file. 
Once this is done, the new SPI can be defined like this:

.. tabs::

    .. code-tab:: c

        spi_t MySPI = { &hspi1 };

    .. code-tab:: cpp

        using MySPI = bsp::drv::SPI<&hspi1, bsp::mid::drv::SPI>;

and then used like all the other SPI.