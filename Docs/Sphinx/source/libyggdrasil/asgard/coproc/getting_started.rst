.. _asgard_m4_getting_started:

Asgard Coprocessor
==================

Setup
-----

To start developing on the Yggdrasil platform using Asgard's Coprocessor, the following things are needed:

.. seealso::
    * `STM32CubeIDE <https://www.st.com/en/development-tools/stm32cubeide.html>`_
    * `Midgard Template <https://gitlab.ti.bfh.ch/sagen1/midgard>`_

After starting the IDE for the first time, close the welcome screen and click on ``File -> Import...``.
Then import the Midgard Template using the ``Existing Project into Workspace`` option.

.. image:: assets/import.png
    :width: 100%
    :alt: Import


Getting Started
---------------

Using C
^^^^^^^

For starting with embedded C development, open ``Core/Src/main.c``, scroll down to the empty infinite loop inside the ``main`` function and start adding your code there.

Using C++
^^^^^^^^^

For starting with embedded C++ development, a few more things are needed.
First, create a new file called e.g ``cpp_main.cpp`` in the ``Core/Src`` folder. In there, include ``<yggdrasil.h>`` and create a new function like this:

.. code-block:: cpp

    #include <yggdrasil.h>

    C_LINKAGE void cpp_main() {

    }

Then in ``main.c`` again, add a function prototype to the top of the file:

.. code-block:: cpp

    void cpp_main(void);

Now call this function above the infinite loop in ``main`` and add all your C++ code to the ``cpp_main`` function.

Testing
-------

Engineering mode
^^^^^^^^^^^^^^^^

It's possible to test Coprocessor applications by switching the controller into Engineering boot mode using the boot mode switches.
After that, it can be programmed similar to Midgard using the STM32CubeIDE.

.. note::
    In contrast to Midgard, the coprocessor firmware resides exclusively in RAM. This means resetting the core through the IDE will erase the program
    and it needs to be reflashed before testing again. 

Linux
^^^^^

To load the coprocessor firmware while Linux is running, the firmware's .elf file can be placed in ``/lib/firmware`` on Asgard's rootfs.

Afterwards the firmware can be loaded through sysfs using the following commands:

.. code-block:: shell

    $ cd /sys/class/remoteproc/remoteproc0
    $ echo "stop" > state
    $ echo "firmware.elf" > firmware
    $ echo "start" > state

This is mainly useful when using Asynchronous Multiprocessing or when releasing a final version of the product.