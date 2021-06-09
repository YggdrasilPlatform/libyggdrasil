.. _HumiditySensorPeripheral:

Humidity Sensor
===============
**Sensirion SHT40-AD1B-R2 Humidity & Temperature sensor**

.. admonition:: Datasheets
    
    * `SHT40-AD1B-R2 Datasheet </_static/datasheets/yggdrasil/SHT40-AD1B-R2.pdf>`_ 

Description
-----------

SHT4x is a digital sensor platform for measuring relative humidity and temperature at different
accuracy classes. The power-trimmed internal heater can be used at three heating levels
thus enabling sensor operation in demanding environments.

* Relative humidity accuracy: up to ±1.5 %RH
* Temperature accuracy: up to ±0.1 °C

.. note::
    The temperature value is the one from the chip, not the environment. It can be used to monitor the sensor temperature when using the heater.

.. warning::
    The heater is designed for a maximal duty cycle of less than 5% when it is periodically heated. Otherwise the sensor might be destroyed.

Usage
-----

The sensor will be initialized through the BSP. These default settings are high precision measurements.
A measurement takes about 10ms. 

.. tabs::

    .. code-tab:: c

        // Read the humidity
        float humidity = yggdrasil_HumiditySensor_GetHumidity(HumiditySensorPrecision_High);
        printf("Humidity: %f%RH \n", humidity);

    .. code-tab:: cpp

        // Read the humidity
        auto humidity = bsp::ygg::prph::HumiditySensor::getHumidity();
        printf("Humidity: %f%RH \n", humidity);
        
.. tabs::

    .. code-tab:: c

        // Read the temperature of the sensor
        float temp = yggdrasil_HumiditySensor_GetTemperature(HumiditySensorPrecision_High);
        printf("Temperature: %fC \n", temp);

    .. code-tab:: cpp

        // Read the temperature of the sensor
        auto temp = bsp::ygg::prph::HumiditySensor::getTemperature();
        printf("Temperature: %fC \n", temp);