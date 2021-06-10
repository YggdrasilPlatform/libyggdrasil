.. _SinkDriverPeripheral:

Sink Driver
===========
**Sink driver**

.. admonition:: Datasheets
    
    * `DMN2020LSN-7 Datasheet </_static/datasheets/yggdrasil/DMN2020LSN-7.pdf>`_ 

Description
-----------

Each sink driver is capable of sinking 5A of peak current,
and has a maximum voltage rating of 20V. 

All driver can be use as:

* Servo driver
* PWM output with high sink capability 
* Output with high sink capability 

There is a pull up resistor to provide a high signal, which is needed to controll a servo.

.. note::

    The PWM frequency will be the same for all channels. 


Usage as output
---------------

The example below will use button A to control the state of the driver output.

.. tabs::

    .. code-tab:: c

        // Set channel D to the state of button A
        yggdrasil_PushPullDriver_Out_Set(PushPullDriverChannel_D, yggdrasil_GPIO_Read(ButtonA));

    .. code-tab:: cpp

        // Set channel D to the state of button A
        bsp::ygg::prph::PushPullDriver::Out::set(bsp::ygg::prph::PushPullDriver::Channel::D, bsp::ButtonA);

Usage as servo driver
---------------------

.. warning::

    When using at least one output to control a servo, the PWM frequency will be automatically set to 50Hz.


The servo driver uses default value which can be modified. The idle PWM high time is 1.5ms. This equals the 0 position. 
The rotation is changed with the high time of the PWM signal. Typically a high time of 0.9ms equals the maximal rotation in cw direction and 2.1ms high time the maximal rotation in ccw direction.
To set a new rotation, the function takes values from -100 to 100, where 100 equals the percentage value of the maximal rotation. Since the single step resolution of the pwm module is 500ns, float values can place the servo accurate to the position.

The example below shows a sweep in ccw direction.

.. tabs::

    .. code-tab:: c

        float sweep = 0;

        while(1) {

            // Set the position value for channel D
            yggdrasil_PushPullDriver_Servo_Set(PushPullDriverChannel_D, sweep);

            core_Delay(10);

            // Increment the sweep variable
            sweep += 0.1F;

            // Reset the variable when the maximum is reached
            if (sweep == 100) sweep = -100;
        }

    .. code-tab:: cpp

        float sweep = 0;

        while(true) {

            // Set the position value for channel D
            bsp::ygg::prph::PushPullDriver::Servo::set(bsp::ygg::prph::PushPullDriver::Channel::D, sweep);

            bsp::core::delay(10);

            // Increment the sweep variable
            sweep += 0.1F;

            // Reset the variable when the maximum is reached
            if (sweep == 100) sweep = -100;
        }


If the used servos need other high time differences form the 1.5ms idle high time, this can be adjusted as shown in the following example.

.. tabs::

    .. code-tab:: c

        // Change the high time difference to 750 ms
        yggdrasil_PushPullDriver_Servo_SetDeltaHighTime(PushPullDriverChannel_D, 750);

    .. code-tab:: cpp

        // Change the high time difference to 750 ms
        bsp::ygg::prph::PushPullDriver::Servo::setDeltaHighTime(bsp::ygg::prph::PushPullDriver::Channel::D, 750);

After this code line, -100% equals 0.75ms and 100% equals 2.25ms for channel D. The other channels will not be affected from this change.


Usage as PWM output
-------------------

.. warning::

    * If one channel is already used as servo driver, the pwm frequency must no be changed. 
    * When changing the frequency, even when the function succeeds, the set frequency might be just the closest possible  


The following example will set the pwm frequency to 1kHz with a resolution of 1000 steps which equals 1us. 

.. tabs::

    .. code-tab:: c

        // Set the pwm frequency to 1kHz with a resolution of 1000 steps
        if (yggdrasil_PushPullDriver_PWM_SetFrequency(1000, 1000)) {
            printf("Frequency and resolution successfully changed!\n");
        }
        else {
            printf("Frequency and resolution could not be changed!\n");
            /*
            * Error handling
            */
        }

        // Get the set frequency 
        f = yggdrasil_PushPullDriver_PWM_GetFrequency();
        printf("F = %luHz\n", f);

        // Set the duty to 25.5% (equals 255us high time with the settings above)
        yggdrasil_PushPullDriver_PWM_SetDuty(PushPullDriverChannel_D, 25.5F);

    .. code-tab:: cpp

        // Set the pwm frequency to 1kHz with a resolution of 1000 steps
        if (bsp::ygg::prph::PushPullDriver::PWM::setFrequency(1E3, 1000)) {
            printf("Frequency and resolution successfully changed!\n");
        }
        else {
            printf("Frequency and resolution could not be changed!\n");
            /*
            * Error handling
            */
        }

        // Get the set frequency 
        f = bsp::ygg::prph::PushPullDriver::PWM::getFrequency();
        printf("F = %luHz\n", f);

        // Set the duty to 25.5% (equals 255us high time with the settings above)
        bsp::ygg::prph::PushPullDriver::PWM::setDuty(bsp::ygg::prph::PushPullDriver::Channel::D, 25.5F);

What if the pwm can not be set
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If the frequency can not be set, there are two possible errors:
    #. The desired PWM frequency :math:`f_p` multiplied with the resolution :math:`r` is higher than the timer frequency :math:`f_t`. As an equation: :math:`f_p * r > f_t` 
    #. The resulting prescaler would be grater than 65'535

To avoid error 1. the frequency or the resolution should be lowered. For specially slow pwm, which might lead to error 2, the resolution should be set as high as possible.

It is also possible to change the project's .ioc file, but be aware that the default template already runs on maximal frequency.


What if the pwm frequency is not accurate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The function to set the pwm frequency will set the nearest frequency possible. This comes from the prescaler, which is a simple integer value. 

.. note::
    Higher frequencies and resolutions lead to smaller prescaler values which are inaccurate due to rounding

There are different solutions for this problem:
    * Lower the resolution. 
    * Set the optimal parameter, such as system frequency, prescaler and resolution, in the project's ioc file.
