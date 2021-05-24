6 Axis Sensor ICM-42605
=======================

.. seealso::
    * `ICM-42605 Datasheet <_static/datasheets/yggdrasil/ICM-42605.pdf>`_ 

Description
-----------

The ICM-42605 is a 6-axis MEMS MotionTracking device that combines a 3-axis gyroscope and a 3-axis accelerometer.

* User selectable Gyro Full-scale range (dps / degrees per second): ± 15.2/31.2/62.5/125/250/500/1000/2000
* User selectable Accelerometer Full-scale range (g): ± 2/4/8/16
* User-programmable digital filters for gyro, accel, and temp sensor

Usage
-----

The sensor will be initialized through the BSP. These default values will be set:

* Scaling factor of the Accelerometer       2G
* Scaling factor of the Gyroscope           250dps
* Output data rate of the Accelerometer     1000Hz
* Output data rate of the Gyroscope         1000Hz

If those are suitable, the sensor data can be used as shown in the following examples. 


.. code-block:: cpp

    // Get the acceleration
    auto [x, y, z] =  bsp::ygg::prph::SixAxisSensor::getAcceleration();
    printf("Acceleration [x, y, z]: %f %f %f \n", x, y, z);


.. code-block:: cpp

    // Get the rotation
    auto [x, y, z] = bsp::ygg::prph::SixAxisSensor::getRotation();
    printf("Rotation [x, y, z]: %f %f %f \n", x, y, z);

.. code-block:: cpp

    auto temp = bsp::ygg::prph::SixAxisSensor::getTemperature();
    printf("Temperature: %fC \n", temp);

There is also a function providing the absolute board roll an pitch. 
This is calculated using the accelerometer's data.

.. code-block:: cpp

    // Get the board orientation
    auto [roll, pitch] = bsp::ygg::prph::SixAxisSensor::getBoardOrientation();
    printf("Roll: %f, Pitch  %f \n", roll, pitch);