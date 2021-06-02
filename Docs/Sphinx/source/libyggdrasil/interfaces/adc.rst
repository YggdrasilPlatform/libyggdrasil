.. _AdcInterface:

ADC Interface
=============

.. note::
    The Analog-Digital converter is a way to read in analog values, for example the voltage after the Potentiometer, and turn it into
    a Digital value the Microcontroller can work with.


Simple Usage
------------

ADCs in libyggdrasil can be used as if they were read-only variables.
Reading will return a floating point value between 0 and 1 where 0 represents a voltage of 0V on the ADC Pin and 1 represents a voltage equivaluent to the Reference voltage of 3.3V.
Writing to an ADC pin is not possible.

The following code will read the current voltage after the Potentiometer.

.. tabs::

    .. code-tab:: c

        const double ReferenceVoltage = 3.3;

        float adcValue = yggdrasil_ADC_Read(ADCPotentiometer);
        float voltage = adcValue * ReferenceVoltage;

    .. code-tab:: cpp

        constexpr auto ReferenceVoltage = 3.3;

        float adcValue = bsp::ADCPotentiometer;
        float voltage = adcValue * ReferenceVoltage;

Available Pins
--------------

+------------------+-----------------------------+
| Name             | Description                 |
+==================+=============================+
| ADCA             | Analog Header ADC A         |
+------------------+-----------------------------+
| ADCB             | Analog Header ADC B         |
+------------------+-----------------------------+
| ADCC             | Analog Header ADC C         |
+------------------+-----------------------------+
| ADCD             | Analog Header ADC D         |
+------------------+-----------------------------+
| ADCPotentiometer | Potentiometer voltage       |
+------------------+-----------------------------+
| ADCTemperature   | Internal temperature sensor |
+------------------+-----------------------------+

Custom ADC
----------

In order to read the voltage of a ADC pin that has not been pre-defined by libyggdrasil, first it needs to be properly configured through the project's .ioc file. 
Once this is done, the new ADC can be defined like this:

.. tabs::

    .. code-tab:: c

        adc_t MyADCChannel = { &hadc7, 14 };

    .. code-tab:: cpp

        using ADConverter7 = bsp::drv::ADConverter<&hadc7, bsp::mid::drv::ADCChannel>;

        static constexpr auto& MyADCChannel = ADConverter7::Channel<14>;

and then used like all other ADCs.

.. tabs::

    .. code-tab:: c

        float myADCValue = yggdrasil_ADC_Read(MyADCChannel);

    .. code-tab:: cpp

        float myADCValue = MyADCChannel;
