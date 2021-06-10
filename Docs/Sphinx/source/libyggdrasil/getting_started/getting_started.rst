.. _getting_started:

Getting Started
===============

.. seealso::
    | **Midgard**
    | Developing applications running directly on Midgard's STM32F7 with or without a RTOS. 
    | :ref:`>>> <midgard_getting_started>`

.. seealso::
    | **Asgard**
    | Developing applications running on Asgard's STM32MP1 A7 Core under Linux or bare metal on its M4 Core
    | :ref:`>>> <asgard_getting_started>`


Compiling
"""""""""

libyggdrasil is a C++20 library and requires at least GCC v9.3 to build.
Additionally, there are a few setup requirements for the project:

Pre-Processor defines
---------------------

.. important::
    Make sure to apply the settings to both the gcc and g++ section!

================================ ============================================================================
Defines                          Description
================================ ============================================================================
``BOARD=<BOARD_NAME>``           ``BOARD_NAME`` represents the Board in use. Can be ``MIDGARD`` or ``ASGARD``
``YGGDRASIL_PERIPHERAL_DEFS``    Adds default peripheral definitions. Not supported when using a custom ioc
================================ ============================================================================

C++ Compile Flags
-----------------

===================== ============================================================================
Flag                  Description
===================== ============================================================================
``-std=gnu++2a``      Enables C++20 mode with GNU extensions
``-fconcepts``        Enables use of Concepts
``-u _printf_float``  Enables printf float support in newlib 
===================== ============================================================================

Include Paths
-------------

===================================== ============================================================================
Path                                  Description
===================================== ============================================================================
``../libyggdrasil/Inc``               Main include path for libyggdrasil
``../libyggdrasil/Inc/c/cmsis/dsp``   ARM DSP functions
===================================== ============================================================================

Source Paths
------------

===================================== ============================================================================
Path                                  Description
===================================== ============================================================================
``../libyggdrasil/Src``               Main source path for libyggdrasil
===================================== ============================================================================

.. toctree::
    :maxdepth: 1
    :caption: Contents:
    :hidden:
 
    asgard/asgard
    midgard/getting_started