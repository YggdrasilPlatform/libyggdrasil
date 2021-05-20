Timer Hardware
==============

.. note::
    Timers allow very accurate timing of events, generation of PWM signals and interfacing with incremental encoders such as the one found on Yggdrasil.
    Note that not every timer can be used for PWM generation or in incremental encoder mode. 

Simple Usage
------------

Every timer got some basic functions and depending on the selected timer some additional functions such as a PWM generator or a incremental encoder decoder. 

Here is an example how to use a timer.

.. code-block:: cpp

    // Enable timer A
    bsp::TimerA::enable();

    // Do something

    // Disable timer A
    bsp::TimerA::disable();

    // Read the counter value
    auto cnt = bsp::TimerA::getCount();

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

.. code-block:: cpp

    ProfileCounter.start();
	// The code to measure
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

.. code-block:: cpp

    // The time to an overflow in nano seconds 
    auto timeToOverflow = ProfileCounter.getTimeToOverflow();

    // The time to an overflow formatted in a string
    auto timeToOverflowString = ProfileCounter.getFormattedTimeToOverflow();
    // The string may be printed like this
    printf("Time to an overflow: %s \n", timeToOverflowString.c_str());


Encoder
-------

The encoder can be used in two different modes. These modes determine how many steps per turn are counted.
Default setting is, that the encoder module counts 96 steps each turn. This can be change to 48 if needed.
The encoder also has a button

.. code-block:: cpp

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

    // Disable the encoder
    bsp::Encoder.disable();


Custom Encoder
^^^^^^^^^^^^^^

If you want to use an additional encoder, it needs to be properly configured through the project's .ioc file. 
Once this is done, the new encoder, in this case using timer 1, can be defined like this:

.. code-block:: cpp

    using MyEncoderTimer = bsp::drv::Timer<&htim1, bsp::mid::drv::Timer, u16>;
    static constexpr auto& MyEncoder = MyEncoderTimer::Encoder;	



PWM Generation
--------------

Some timer have an integrated multichannel PWM generation module. These channels can be used as shown in the example below.

.. code-block:: cpp

    // Enable a pwm generation on timer A channel A
    if (!bsp::TimerDCHA.startPwm()) {
        // Timer could not be started
        // Error handling
    }

    // Set the duty cycle to an float between 0 an 100
    bsp::TimerDCHA.setDutyCycle(25.2F);

    // Disable the pwm
    bsp::TimerDCHA.stopPwm();

For the multichannel PWM modules, the frequency for each channel is the same. To adjust the frequency the best way is to change this in the .ioc file.
There is also a function provided to change the PWM frequency, but there is no guarantee that the function is able to change the frequency. 
In order to change the frequency of timer A channel A, the frequency of the timer A must be changed.

.. code-block:: cpp

    // Change the pwm frequency of timer A 
    if (!bsp::TimerA::setPwmFrequency(50,1000)) {
        // Frequency could not be changed
        // Error handling
    }

    // To be sure that the frequency 

In the example above, the frequency will be set 50Hz with a resolution of 1000 steps. 
The function might not be able to adjust the frequency when:

* The desired frequency is equal or higher as the timer frequency
* The resolution is to high

There are more possibilities that the adjustment can fail, for example the the 