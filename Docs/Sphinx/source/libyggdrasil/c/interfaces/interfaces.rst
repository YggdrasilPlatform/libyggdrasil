Hardware Drivers
================

Hardware drivers are simple abstractions to talk to Hardware inside the Microcontroller itself. 

libyggdrasil gives access to all standard interfaces as long as the ``YGGDRASIL_PERIPHERAL_DEFS`` define flag is set.
This should only be used with the unmodified template as things may stop working correctly when changes were made to the .ioc file.

.. toctree::
    :maxdepth: 1
    :caption: Contents:
    :hidden:
     
    gpio
    uart
    spi
    i2c
    adc
    dac
    hash
    rng
    timer
    display