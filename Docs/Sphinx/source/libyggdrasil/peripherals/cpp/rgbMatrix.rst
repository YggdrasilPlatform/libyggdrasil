RGB Matrix SK9822 RGB Led
=========================

.. seealso::
    * `SK9822 Datasheet <_static/datasheets/yggdrasil/SK9822.pdf>`_ 

Description
-----------

The 3 x 3 LED matrix uses SK9822 leds. These are also known as a clone from the APA102C RGB leds.
These leds have 4 built in pwm generators. For the red, green and blue channel three times a 8 bit pwm and for the global brightness a 5 bit pwm.

.. warning::
    Each led consumes up to 200mW. It is not recommended to watch directly in the leds.


Usage
-----

. .note::

    When enabling the leds, the SPIA mode will be set to mode 3

.. code-block:: cpp 
    
