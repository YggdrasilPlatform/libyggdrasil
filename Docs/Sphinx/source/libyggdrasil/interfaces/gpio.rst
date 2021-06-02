.. _GpioInterface:

GPIO Interface
==============

.. note::
    GPIOs can be used to drive a physical pin on the microcontroller to 3.3V or GND in order to control for example an LED.
    Alternatively they can also read if there's currently 3.3V or GND being applied to the pin, to detect for example the state of a button.

Simple Usage
------------

The following code will cause the blue User LED to light up, the yellow LED to turn off and the red LED to blink.

.. tabs::

    .. code-tab:: c

        yggdrasil_GPIO_Set(LedBlue, true);
        yggdrasil_GPIO_Set(LedYellow, false);
        yggdrasil_GPIO_Toggle(LedRed);

    .. code-tab:: cpp

        bsp::LedBlue = true;
        bsp::LedYellow = false;
        bsp::LedRed = !bsp::LedRed;

It's also possible to read and write multiple pins at once. For this use the following:

.. tabs::

    .. code-tab:: c

        yggdrasil_GPIO_SetMultiple(GPIOA, 0, 3, 0x0A);
        u8 bits = yggdrasil_GPIO_GetMultiple(GPIOA, 4, 7);

    .. code-tab:: cpp

        bsp::GPIOPortA::Out<0, 3> = 0b1010;
        u8 bits = bsp::GPIOPortA::In<4, 7>;

This code turns Pin 1 and 3 of Port A on and Pin 0 and 2 off. Then it reads the values of pin 4 to 7 and stores the value into a variable.


Available Pins
--------------

+---------------+----------------+-------------------------+
| Name          | Aliases        | Description             |
+===============+================+=========================+
| LD1           | LDA, LedBlue   | LED 1, Blue             |
+---------------+----------------+-------------------------+
| LD2           | LDB, LedRed    | LED 2, Red              |
+---------------+----------------+-------------------------+
| LD3           | LDC, LedYellow | LED 3, Yellow           |
+---------------+----------------+-------------------------+
| LD4           | LDD, LedGreen  | LED 4, Green            |
+---------------+----------------+-------------------------+
| EncoderButton |                | Encoder Push Button     |
+---------------+----------------+-------------------------+
| DriverA       | LD5, LDE       | Driver Pin A, Green LED |
+---------------+----------------+-------------------------+
| DriverB       | LD6, LDF       | Driver Pin B, Green LED |
+---------------+----------------+-------------------------+
| DriverC       | LD7, LDG       | Driver Pin C, Green LED |
+---------------+----------------+-------------------------+
| DriverD       | LD8, LDH       | Driver Pin D, Green LED |
+---------------+----------------+-------------------------+
| EnableRGB     |                | Enable RGB LED Matrix   |
+---------------+----------------+-------------------------+
| SPIACE        |                | SPIA Chip Enable        |
+---------------+----------------+-------------------------+
| TC78Mode      |                | Motor Driver Mode Select|
+---------------+----------------+-------------------------+
| TC78Err       |                | Motor Driver Error      |
+---------------+----------------+-------------------------+
| TC78Stby      |                | Motor Driver Standby    |
+---------------+----------------+-------------------------+
| PhaseA        |                | Motor CH A Direction    |
+---------------+----------------+-------------------------+
| PhaseB        |                | Motor CH B Direction    |
+---------------+----------------+-------------------------+

Custom Pin
----------

In order to control a pin that has not been pre-defined by libyggdrasil, first it needs to be properly configured through the project's .ioc file. 
Once this is done, the new pin, in this case the Port E Pin 7, can be defined like this:

.. tabs::

    .. code-tab:: c

        gpio_t MyPin = { GPIOE, 7 };

    .. code-tab:: cpp

        auto& MyPin = bsp::GPIOPortE::Pin<7>;

and then used like all other GPIO Pins.

.. tabs::

    .. code-tab:: c

        if (yggdrasil_GPIO_Get(MyPin))
            LedGreen = true;

    .. code-tab:: cpp

        if (MyPin == true)
            LedGreen = true;