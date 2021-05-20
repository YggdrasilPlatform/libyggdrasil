C++ On-Board Peripherals
========================

In a .cpp file, libyggdrasil will automatically be put into C++ mode. It's encouraged to use the C++ interface in this case since it's a lot more readable and easier to use.

.. note::
    If for any reason the C interface is preferred over the C++ one while still writing C++ code,
    it may be used by adding the following define before including the libyggdrasil header.

    .. code-block:: cpp
    
        #define YGGDRASIL_USE_C_INTERFACE

.. toctree::
    :maxdepth: 1
    :caption: Contents:
    :hidden:
     
    colorSensor
    humiditySensor
    pressureSensor
    sixAxisSensor
    rtc
    joystick
    sevenSegment
    motorDriver
    rgbMatrix
    pushPullDriver