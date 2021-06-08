.. _TimerInterface:

Timer Hardware
==============

.. note::
    Timers allow very accurate timing of events, generation of PWM signals and interfacing with incremental encoders such as the one found on Yggdrasil.
    Note that not every timer can be used for PWM generation or in incremental encoder mode. 

Simple Usage
------------

Every timer got some basic functions and depending on the selected timer some additional functions such as a PWM generator or a incremental encoder decoder. 

Here is an example how to use a timer.

.. tabs::

    .. code-tab:: c

        // Enable timer A
        yggdrasil_TIM_Enable(TimerA);

        // Read the counter value
        u32 cnt = yggdrasil_TIM_GetCount(TimerA);

        // Disable timer A
        yggdrasil_TIM_Disable(TimerA);

        // Reset the value 
        yggdrasil_TIM_ResetCount(TimerA);

        // Or preset the counter value
        yggdrasil_TIM_SetCount(TimerA, 200);


    .. code-tab:: cpp

        // Enable timer A
        bsp::TimerA::enable();

        // Read the counter value
        auto cnt = bsp::TimerA::getCount();

        // Disable timer A
        bsp::TimerA::disable();

        // Reset the value 
        bsp::TimerA::resetCount();

        // Or preset the counter value
        bsp::TimerA::setCount(200);

For runtime measurement it is suggested to use the implemented profile counter.  

Available peripherals
---------------------

+---------------+-----------+----------------+-----------------------------------------------------------------+
| Timer         | Usage     | Subtype        | Peripherals                                                     |
+===============+===========+================+=================================================================+
| TimerA        | PWM       | TimerACHA      | Raspberry Shield Connector Pin 33, PMod A Pin 2                 |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerB        | PWM       | TimerBCHB      | Raspberry Shield Connector Pin 28, Motor driver                 |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerB        | PWM       | TimerBCHC      | Raspberry Shield Connector Pin 22, PMod B Pin 2, Motor driver   |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerC        | PWM       | TimerCCHA      | Raspberry Shield Connector Pin 27, PMod A Pin 4                 |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerD        | PWM       | TimerDCHA      | Push pull driver A                                              |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerD        | PWM       | TimerDCHB      | Push pull driver B                                              |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerD        | PWM       | TimerDCHC      | Push pull driver C                                              |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerD        | PWM       | TimerDCHD      | Push pull driver D                                              |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerE        | PWM       | TimerECHA      | Push pull driver A                                              |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerF        | Encoder   | Encoder        | Encoder on Yggdrasil                                            |
+---------------+-----------+----------------+-----------------------------------------------------------------+
| TimerG        | Counter   | ProfileCounter |                                                                 |
+---------------+-----------+----------------+-----------------------------------------------------------------+

Profile Counter
---------------

Using a 32 Bit timer, the profile counter is able to get you high resolution long time measurement of the code execution time.

.. tabs::

    .. code-tab:: c

        yggdrasil_ProfileCounter_Start(ProfileCounter);
        // The code to measure
        function_to_measure();
        yggdrasil_ProfileCounter_Stop(ProfileCounter);

        // Get the passed time in nano seconds  
        u64 passedTime = yggdrasil_ProfileCounter_GetPassedTime(ProfileCounter);

        // Or get the passed time formatted in a string
        char buffer[30];
        yggdrasil_ProfileCounter_GetFormattedPassedTime(ProfileCounter, buffer, sizeof(buffer));

        // The string may be printed like this
        printf("Measured time: %s \n", buffer);

        // Reset the counter value 
        yggdrasil_ProfileCounter_Reset(ProfileCounter);

    .. code-tab:: cpp

        ProfileCounter.start();
        // The code to measure
        function_to_measure();
        ProfileCounter.stop();

        // Get the passed time in nano seconds  
        auto passedTime = ProfileCounter.getPassedTime();

        // Or get the passed time formatted in a string
        auto passedTimeString = ProfileCounter.getFormattedPassedTime();

        // The string may be printed like this
        printf("Measured time: %s \n", passedTimeString.c_str());

        // Reset the counter value 
        ProfileCounter.reset();

There is also a function to get the time to an overflow regarding the configured timer clock frequency. 

.. tabs::

    .. code-tab:: c

        // The time to an overflow in nano seconds 
        u64 timeToOverflow = yggdrasil_ProfileCounter_GetTimeToOverflow(ProfileCounter);

        // The time to an overflow formatted in a string
        char buffer[30];
        yggdrasil_ProfileCounter_GetFormattedTimeToOverflow(ProfileCounter, buffer, sizeof(buffer));

        // The string may be printed like this
        printf("Time to an overflow: %s \n",buffer);

    .. code-tab:: cpp

        // The time to an overflow in nano seconds 
        auto timeToOverflow = ProfileCounter.getTimeToOverflow();

        // The time to an overflow formatted in a string
        auto timeToOverflowString = ProfileCounter.getFormattedTimeToOverflow();

        // The string may be printed like this
        printf("Time to an overflow: %s \n", timeToOverflowString.c_str());


Custom Profile Counter
^^^^^^^^^^^^^^^^^^^^^^ 

If you want to use an additional profile counter, it needs to be properly configured through the project's .ioc file. 
Once this is done, the profile counter, in this case timer 10, can be defined like this:

.. tabs::

    .. code-tab:: c

        tim_t myProfileCounter = { &htim2, sizeof(u32) };		


    .. code-tab:: cpp

        using MyProfileTimer = bsp::drv::Timer<&htim10, bsp::mid::drv::Timer, u16>;
        static constexpr auto& MyProfileCounter = MyProfileTimer::ProfileCounter;

After this declaration, the profile counter can be used as in the examples above.

.. note::

    Note that 16 bit timer, possibly on high frequency bus reaches an overflow faster than expected.



Encoder
-------

The encoder can be used in two different modes. These modes determine how many steps per turn are counted.
Default setting is, that the encoder module counts 96 steps each turn. This can be change to 48 steps if needed.
The encoder also has a button which can be used as a gpio.

.. tabs::

    .. code-tab:: c
    
        // Enable the encoder 
        if (!yggdrasil_Encoder_Enable(Encoder)) {
            // No encoder module on this timer
            // Error handling
        }

        // Get the direction of the ongoing or the last rotation
        u8 direction = yggdrasil_Encoder_GetDirection(Encoder);

        // Get the count 
        u32 count = yggdrasil_Encoder_GetCount(Encoder);

        // Set the count to a desired value
        yggdrasil_Encoder_SetCount(Encoder, 1000);

        u8 buttonState = yggdrasil_GPIO_Get(EncoderButton);

        // Disable the encoder
        yggdrasil_Encoder_Disable(Encoder);

    .. code-tab:: cpp

        // Enable the encoder 
        if (!bsp::Encoder.enable()) {
            // No encoder module on this timer
            // Error handling
        }

        // Get the direction of the ongoing or the last rotation
        auto direction = bsp::Encoder.getDirection();

        // Get the count 
        auto count = bsp::Encoder.getCount();

        // Set the count to a desired value
        bsp::Encoder.setCount(1000);

        auto buttonState = bsp::EncoderButton;

        // Disable the encoder
        bsp::Encoder.disable();


Custom Encoder
^^^^^^^^^^^^^^

If you want to use an additional encoder, it needs to be properly configured through the project's .ioc file. 
Once this is done, the new encoder, in this case timer 1, can be defined like this:

.. tabs::

    .. code-tab:: c

        tim_t myEncoder = { &htim1, sizeof(u16) };

    .. code-tab:: cpp

        using MyEncoderTimer = bsp::drv::Timer<&htim1, bsp::mid::drv::Timer, u16>;
        static constexpr auto& MyEncoder = MyEncoderTimer::Encoder;	

After this declaration, the added encoder can be used as in the examples above.

PWM Generation
--------------

Some timer have an integrated multichannel PWM generation module. These channels can be used as shown in the example below.

.. tabs::

    .. code-tab:: c

        // Enable a pwm generation on timer A channel A
        if (!yggdrasil_TIM_Channel_StartPwm(TimeACHA)) {
            // Timer could not be started
            // Error handling
        }

        // Set the duty cycle to an float between 0 an 100
        yggdrasil_TIM_Channel_SetDutyCycle(TimeACHA, 25.5F);

        // Disable the pwm
        yggdrasil_TIM_Channel_StopPwm(TimeACHA);

    .. code-tab:: cpp

        // Enable a pwm generation on timer A channel A
        if (!bsp::TimerDCHA.startPwm()) {
            // Timer could not be started
            // Error handling
        }

        // Set the duty cycle to an float between 0 an 100
        bsp::TimerDCHA.setDutyCycle(25.2F);

        // Disable the pwm
        bsp::TimerDCHA.stopPwm();

For the multichannel PWM modules, the frequency for each channel is the same. To adjust the frequency the best way is to change this in the project's .ioc file.
There is also a function provided to change the PWM frequency, but there is no guarantee that the function is able to change it. 
In order to change the frequency of timer A channel A, the frequency of the timer A must be changed. The frequency for all channels in one timer is the same.

.. tabs::

    .. code-tab:: c

        // Change the pwm frequency of timer A 
        if (!yggdrasil_TIM_SetPwmFrequency(TimerA, 50, 1000)) {
            // Frequency could not be changed
            // Error handling
        }

    .. code-tab:: cpp

        // Change the pwm frequency of timer A 
        if (!bsp::TimerA::setPwmFrequency(50, 1000)) {
            // Frequency could not be changed
            // Error handling
        }
 

In the example above, the frequency will be set 50Hz with a resolution of 1000 steps. 
The function might not be able to adjust the frequency when:

* The desired frequency is equal or higher as the timer frequency
* The resolution is to high
* The timer frequency is to high (only for very slow pwm signals)

Custom PWM Generation
^^^^^^^^^^^^^^^^^^^^^

To add an other timer with a pwm module, the timer as is must be declared.

.. tabs::

    .. code-tab:: c

        tim_t MyPwmTimer = { &htim10, sizeof(u16) };

    .. code-tab:: cpp

        using MyPwmTimer = bsp::drv::Timer<&htim10, bsp::mid::drv::Timer, u16>;

Then the actual channel can be declared.

.. tabs::

    .. code-tab:: c

        tim_channel_t MyPwmChannel = { MyPwmTimer, 1 };

    .. code-tab:: cpp

        static constexpr auto& MyPwmChannel = MyPwmTimer::Channel<1>;

After this declaration, the added pwm channel can be used as in the examples above.