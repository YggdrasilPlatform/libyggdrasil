.. _SixAxisSensorPeripheral:

6-Axis Sensor
=============
**TDK ICM-42605 Accelerometer & Gyroscope**

.. admonition:: Datasheets
    
    * `ICM-42605 Datasheet </_static/datasheets/yggdrasil/ICM-42605.pdf>`_ 

Description
-----------

The ICM-42605 is a 6-axis MEMS MotionTracking device that combines a 3-axis gyroscope and a 3-axis accelerometer.

* User selectable Gyro Full-scale range (dps / degrees per second): ± 15.2/31.2/62.5/125/250/500/1000/2000
* User selectable Accelerometer Full-scale range (g): ± 2/4/8/16
* User-programmable digital filters for gyro, accel, and temp sensor

Usage
-----

.. note::
    A coordinate system with roll and pitch indicators can be found on Yggdrasil's silk screen. It's very useful to make sense of the values returned by the following functions.

The sensor will be initialized through the BSP. These default values will be set:

* Scaling factor of the Accelerometer       2G
* Scaling factor of the Gyroscope           250dps
* Output data rate of the Accelerometer     1000Hz
* Output data rate of the Gyroscope         1000Hz

If those are suitable, the sensor data can be used as shown in the following examples. 

.. tabs::

    .. code-tab:: c

        // Get the acceleration
        struct Coordinate coords = yggdrasil_SixAxisSensor_GetAcceleration();
        printf("Acceleration [x, y, z]: %f %f %f \n", coords.x, coords.y, coords.z);

    .. code-tab:: cpp

        // Get the acceleration
        auto [x, y, z] =  bsp::ygg::prph::SixAxisSensor::getAcceleration();
        printf("Acceleration [x, y, z]: %f %f %f \n", x, y, z);


.. tabs::

    .. code-tab:: c

        // Get the acceleration
        struct Coordinate coords = yggdrasil_SixAxisSensor_GetRotation();
        printf("Rotation [x, y, z]: %f %f %f \n", coords.x, coords.y, coords.z);

    .. code-tab:: cpp

        // Get the acceleration
        auto [x, y, z] =  bsp::ygg::prph::SixAxisSensor::getRotation();
        printf("Rotation [x, y, z]: %f %f %f \n", x, y, z);

.. tabs::

    .. code-tab:: c

        // Get the temperature
        float temp = yggdrasil_SixAxisSensor_GetTemperature();
        printf("Temperature: %fC \n", temp);

    .. code-tab:: cpp

        // Get the temperature
        auto temp = bsp::ygg::prph::SixAxisSensor::getTemperature();
        printf("Temperature: %fC \n", temp);

There is also a function providing the absolute board roll an pitch. 
This is calculated using the accelerometer's data.

.. tabs::

    .. code-tab:: c

        // Get the board orientation
        struct Orientation orientation = yggdrasil_SixAxisSensor_GetBoardOrientation();
        printf("Roll: %f, Pitch  %f \n", orientation.roll, orientation.pitch);

    .. code-tab:: cpp

        // Get the board orientation
        auto [roll, pitch] = bsp::ygg::prph::SixAxisSensor::getBoardOrientation();
        printf("Roll: %f, Pitch  %f \n", roll, pitch);