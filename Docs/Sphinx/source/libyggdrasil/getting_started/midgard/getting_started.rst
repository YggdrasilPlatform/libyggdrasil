.. _midgard_getting_started:

Midgard
=======

Midgard uses an easy to use STM32F7 Microcontroller, perfect for learning how to write embedded low-level software but still powerful enough
for the majority of projects. 

Setup
-----

To start developing on the Yggdrasil platform using Midgard, the following things are needed:

.. seealso::
    * `STM32CubeIDE <https://www.st.com/en/development-tools/stm32cubeide.html>`_
    * `Midgard Template <https://gitlab.ti.bfh.ch/yggdrasil/midgard/midgard_template>`_

After starting the IDE for the first time, close the welcome screen and click on ``File -> Import...``.
Then import the Midgard Template using the ``Existing Project into Workspace`` option.

.. image:: assets/import.png
    :width: 100%
    :alt: Import


Getting Started
---------------

.. tabs::

    .. group-tab:: C

        For starting with embedded C development, simply open ``Core/main.c``, scroll down to find the ``main`` function and in there scroll further down until you find a block
        of code that looks like this:

        .. code-block:: c

            /* Infinite loop */
            /* USER CODE BEGIN WHILE */
            while (1)
            {
            /* USER CODE END WHILE */
        
            /* USER CODE BEGIN 3 */
            }
            /* USER CODE END 3 */

        All code goes between one of the ``/* USER CODE BEGIN XXX*/`` and ``/*USER CODE END XXX*/`` blocks. This is important since everything outside of these blocks
        will be deleted when the project is regenerated with the .ioc file.

    .. group-tab:: C++

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