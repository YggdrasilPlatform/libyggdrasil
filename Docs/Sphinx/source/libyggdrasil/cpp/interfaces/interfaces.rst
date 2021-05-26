Hardware Drivers
================

Hardware drivers are simple abstractions to talk to Hardware inside the Microcontroller itself. 

libyggdrasil gives access to all standard interfaces as long as the ``YGGDRASIL_PERIPHERAL_DEFS`` define flag is set.
This should only be used with the unmodified template as things may stop working correctly when changes were made to the .ioc file.

.. note::
    The C++ interface heavily depends on ``constexpr`` execution and template meta programming to optain ideal code generation.
    This might be confusing for C++ beginners so here's a breakdown of the structure:
    
    All interfaces consist of a "frontend" and a "implementation". The frontend takes a context (e.g the interface base address, a HAL handle or a interface number) and the
    implementation class of the current board as template parameters. The frontend is the common interface that gets accessed by the user. It then calls into the implementation
    to interact with the hardware.

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