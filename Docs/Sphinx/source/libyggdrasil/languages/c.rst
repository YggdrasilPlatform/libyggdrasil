.. _libyggdrasil_c:

C Project
===========

Templates
"""""""""

To get started with C development, it's easiest to clone the example or a template for the board and environment you're using from GitLab.

.. important::
    If there are build errors about the compiler not finding certain includes from libyggdrasil, make sure you cloned the template repository recusively with ``--recurse-submodules``. Without this flag, the ``libyggdrasil`` folder will be empty.


Midgard
-------
.. code-block:: sh
    
    git clone https://gitlab.ti.bfh.ch/yggdrasil/midgard/midgard_template --recurse-submodules

Asgard
------

Coprozessor
^^^^^^^^^^^
.. code-block:: sh
    
    git clone https://gitlab.ti.bfh.ch/yggdrasil/asgard/asgard_coprocessor_template --recurse-submodules

Linux
^^^^^
.. code-block:: sh
    
    git clone https://gitlab.ti.bfh.ch/yggdrasil/asgard/asgard_linux_template --recurse-submodules


Examples
"""""""""

Examples are a nice way to demonstrate the power of Yggdrasil and to learn how to use different aspects of the support library.

Midgard
-------

.. code-block:: sh
    
    git clone https://gitlab.ti.bfh.ch/yggdrasil/midgard/midgard_examples --recurse-submodules


Following examples are available:

* TotalGB Gameboy / Gameboy Color Emulator with Super Mario Land 2 loaded by default. Available ROMs are Tetris, Super Mario Land 2 and The Legend of Zelda: Link's Awakening
* Mandelbrot / Julia Set generator with Joystick support
* Azure RTOS example