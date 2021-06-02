.. _DacInterface:

DAC Interface
=============

.. note::
    The Digital-Analog converter allows applying of a specific voltage to a Pin to, for example generate an analog audio signal.


Simple Usage
------------

DACs in libyggdrasil can be used as if they were normal variables.
Writing a floating point value between 0 and 1 to it will cause a voltage between 0V and the reference voltage to be applied to the DAC pin.
Reading will read back the current value stored in the DAC.

The following code will apply 2V to the DAC A header.

.. tabs::

    .. code-tab:: c

        const double ReferenceVoltage = 3.3;

        yggdrasil_DAC_Write(DACA, 2.0 / ReferenceVoltage);

    .. code-tab:: cpp

        constexpr auto ReferenceVoltage = 3.3;

        bsp::DACA = 2.0 / ReferenceVoltage;

Available Pins
--------------

+-------+-----------------------------+
| Name  | Description                 |
+=======+=============================+
| DACA  | Analog Header DAC A         |
+-------+-----------------------------+
| DACB  | Analog Header DAC B         |
+-------+-----------------------------+

Custom DAC
----------

In order to apply a voltage to a DAC pin that has not been pre-defined by libyggdrasil, first it needs to be properly configured through the project's .ioc file. 
Once this is done, the new DAC can be defined like this:

.. tabs::

    .. code-tab:: c

        dac_t MyDAC = { &hdac, 1 };

    .. code-tab:: cpp

        using DAConverter2 = bsp::drv::DAConverter<&hdac2, bsp::mid::drv::DACChannel>;

        static constexpr auto &MyDAC = DAConverter2::Channel<1>;

and then used like all other DACs.

.. tabs::

    .. code-tab:: cpp

        yggdrasil_DAC_Write(MyDAC, 0.5 / ReferenceVoltage);

    .. code-tab:: cpp

        MyDAC = 0.5 / ReferenceVoltage;
