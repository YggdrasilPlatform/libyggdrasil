.. _libyggdrasil_cpp:

C++ Project
===========

Getting Started Guides
----------------------

.. seealso::
    | **Midgard Bare metal**
    | Developing applications running directly on Midgard's STM32F7 with or without a RTOS. 
    | :ref:`>>> <midgard_getting_started_cpp>`

.. seealso::
    | **Asgard Linux Userland**
    | Developing applications running on Asgard's STM32MP1 A7 Core under Linux
    | :ref:`>>> <asgard_a7_getting_started_cpp>`

.. seealso::
    | **Asgard Coprocessor Bare metal**
    | Developing applications running directly on Asgards's STM32MP1 M4 Core with or without a RTOS. 
    | :ref:`>>> <asgard_m4_getting_started_cpp>`

C interface in C++
------------------

In a .cpp file, libyggdrasil will automatically be put into C++ mode. It's encouraged to use the C++ interface in this case since it's a lot more readable and easier to use.

.. note::
    If for any reason the C interface is preferred over the C++ one while still writing C++ code,
    it can be used by adding the following define before including the libyggdrasil header.

    .. code-block:: cpp
    
        #define YGGDRASIL_USE_C_INTERFACE

.. toctree::
    :maxdepth: 1
    :caption: Contents:
    :hidden:
     
    midgard/getting_started
    asgard/linux/getting_started
    asgard/coproc/getting_started
    interfaces/interfaces
    peripherals/peripherals