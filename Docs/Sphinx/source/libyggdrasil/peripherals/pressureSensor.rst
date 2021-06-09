.. _PressureSensorPeripheral:

Pressure Sensor
===============
**STMicroelectronics LPS22HBTR Nano pressure sensor**

.. admonition:: Datasheets
    
    * `LPS22HBTR Datasheet </_static/datasheets/yggdrasil/LPS22HBTR.pdf>`_ 

Description
-----------

The LPS22HB is an ultra-compact piezoresistive
absolute pressure sensor which functions as a
digital output barometer.

* 260 to 1260 hPa absolute pressure range
* 24-bit pressure data output
* 16-bit temperature data output

Usage
-----

The sensor will be initialized through the BSP. The sensor data can be used as shown in the example. 

.. tabs::

    .. code-tab:: c

        // Get the pressure
        float pressure = yggdrasil_PressureSensor_GetPressure();
        printf("Pressure: %fhPa \n", pressure);

    .. code-tab:: cpp

        // Get the pressure
        auto pressure = bsp::ygg::prph::PressureSensor::getPressure();
        printf("Pressure: %fhPa \n", pressure);

.. tabs::

    .. code-tab:: c

        // Get the temperature
        auto temp = yggdrasil_PressureSensor_GetTemperature();
        printf("Temperature: %fC \n", temp);

    .. code-tab:: cpp

        // Get the temperature
        auto temp = bsp::ygg::prph::PressureSensor::getTemperature();
        printf("Temperature: %fC \n", temp);

.. note::

    When reading the pressure and the temperature, there must be a delay of at least 10ms between those read commands.

