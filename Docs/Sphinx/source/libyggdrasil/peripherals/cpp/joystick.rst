Joystick
========

.. note::
    The joysticks are connected to an external ADC converter, which can be accessed using I2C

.. seealso::
    * `TLA2024IRUGT Datasheet <_static/datasheets/yggdrasil/TLA2024IRUGT.pdf>`_ 

Description
-----------

Both joysticks are connected to the TLA2024IRUGT ADC, which can be accessed using I2C. The buttons on the joysticks
can also be read as every other gpio. 
Theoretically each axis give a value from -100 to 100, but due to product tolerances, this values are not reached with every joystick.
To guarantee that 0|0 is read even the hands are on the joysticks, there is a default deadzone from 5.  


Usage
-----

This example shows how to read the deadzone, set a new one and access the joystick data.

.. code-block:: cpp

    // Get the deadzone 
    auto deadZone = bsp::ygg::prph::Joystick::getDeadzone();

    // Double the deadzone
    bsp::ygg::prph::Joystick::setDeadzone(2*deadZone);

    // Get the left joystick data
    auto data = bsp::ygg::prph::Joystick::getLeft();
    printf("Left joystick X: %d, Y: %d, radius from center: %d, button: %d\n", data.pos.x, data.pos.y, data.mag, data.pressed);


