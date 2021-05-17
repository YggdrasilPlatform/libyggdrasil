DAC Interface
=============

.. note::
    The Digital-Analog converter allows applying of a specific voltage to a Pin to, for example generate an analog audio signal.


Simple Usage
------------

DACs in libyggdrasil can be used as if they were write-only variables.
Writing a floating point value between 0 and 1 to it will cause a voltage between 0V and the reference voltage to be applied to the DAC pin.
Reading  is not possible.

The following code will apply 2V to the DAC A header.

.. code-block:: cpp

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

.. code-block:: cpp

    using DAConverter2 = bsp::drv::DAConverter<&hdac2, bsp::mid::drv::DACChannel>;

    static constexpr auto &MyDAC = DAConverter2::Channel<1>;

and then used like all other DACs.

.. code-block:: cpp

    MyDAC = 0.5;
