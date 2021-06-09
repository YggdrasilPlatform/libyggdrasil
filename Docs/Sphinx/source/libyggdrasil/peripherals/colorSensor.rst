.. _ColorSensorPeripheral:

Color Sensor
============
**ams TCS3472 Color Sensor**

.. admonition:: Datasheets
    
    * `TCS3472 Datasheet </_static/datasheets/yggdrasil/TCS3472.pdf>`_ 


Description
-----------

The TCS3472 device provides a digital return of red, green, blue
(RGB), and clear light sensing values. An IR blocking filter,
integrated on-chip and localized to the color sensing
photodiodes, minimizes the IR spectral component of the
incoming light and allows color measurements to be made
accurately (16 Bit each color).

Usage
-----

The sensor will be initialized through the BSP. These default values will be set:

* Integration time to 2.4ms
* Gain to 1x


The initialization starts the first conversion with the given parameters. If those are suitable, the sensor data can be used as shown in the example. 

.. tabs::

    .. code-tab:: c

        // Read the 16 bit converted color values and start a new conversion
        RGBA16 color = yggdrasil_ColorSensor_GetColor16(true);
        printf("Color RGBA16: %d, %d, %d, %d \n", color.r, color.g, color.b, color.a);

    .. code-tab:: cpp

        // Read the 16 bit converted color values and start a new conversion
        auto color = bsp::ygg::prph::ColorSensor::getColor16(true);
        printf("Color RGBA16: %d, %d, %d, %d \n", color.r, color.g, color.b, color.a);

When the Integration time and the gain must be changed, a new conversion must be started.

.. tabs::

    .. code-tab:: c

        // Wait until the sensor is not working
        while (!yggdrasil_ColorSensor_IsDone());

        // Set a new integration time
        yggdrasil_ColorSensor_SetIntegrationTime(ColorSensorIntegrationTime_10ms);

        // Set a new gain
        yggdrasil_ColorSensor_SetGain(ColorSensorGain_4x);

        // Start a new conversion
        yggdrasil_ColorSensor_StartConversion();

    .. code-tab:: cpp

        // Wait until the sensor is not working
        while (!bsp::ygg::prph::ColorSensor::isDone());

        // Set a new integration time
        bsp::ygg::prph::ColorSensor::setIntergrationTime(bsp::ygg::prph::ColorSensor::IntegrationTime::_10ms);

        // Set a new gain
        bsp::ygg::prph::ColorSensor::setGain(bsp::ygg::prph::ColorSensor::Gain::_4x);

        // Start a new conversion
        bsp::ygg::prph::ColorSensor::startConversion();


