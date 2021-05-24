Encoder
=======

.. seealso::
    * :ref:`Timer interface <TimerInterface>`


Description
-----------

With the timer F (TIM8) in the encoder mode, the onboard encoder can be used. 

Usage
-----

The encoder mode will be enabled through the bsp. 


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

    auto buttonState = bsp::EncoderButton;

    // Disable the encoder
    bsp::Encoder.disable();