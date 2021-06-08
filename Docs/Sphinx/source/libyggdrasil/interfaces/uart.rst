.. _UartInterface:

UART Interface
==============

.. note::
    UART is a Asynchronous serial interface often used as debug console or interfacing with some sensors. It is connected to the ST-Link debugger to
    allow printf-output to be displayed within the STM32CubeIDE but is also available on the Pmod connectors.


Simple Usage
------------

Reading from and writing to a UART port is as simple as calling the ``read`` and ``write`` functions of the relevant 
UART interface.

There's two versions available: Binary and ASCII transmissions.

If binary data is read or written, the interface reads as many bytes as requested or writes as many bytes as given. It doesn't stop until everything is done.
If ASCII data is read or written, the interface reads until it hits a ``Line Feed [ \n, 0x0A ]`` or a ``Carriage Return [ \r, 0x0D ]``. It sends data until it hits a string ``Null Terminator [ \0, 0x00 ]``.

.. tabs::

    .. code-tab:: c

        u8 buffer[10] = { 0 };

        // Read 10 bytes from the console
        yggdrasil_UART_Receive(UARTB, buffer, 10);

        
    .. code-tab:: cpp

        // Read string from console
        std::string string = bsp::UARTB::readString();

.. tabs::

    .. code-tab:: c

        char * txbuffer = "Hello World!\n";

        // Send string to console
        yggdrasil_UART_Transmit(UARTB, txbuffer, strlen(txbuffer));

        u8 buffer[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        // Send 10 bytes to the console
        yggdrasil_UART_Transmit(UARTB, buffer, sizeof(buffer));

    .. code-tab:: cpp

        // Send string to console
        bsp::UARTB::write("Hello World!");

        std::array<u8, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        // Send 10 bytes to the console
        bsp::UARTB::write(data);

Available ports
---------------

+-------------+------------------------+
| Port        | Bus                    |
+=============+========================+
| ST-Link COM | UARTST / UARTC         |
+-------------+------------------------+
| PMOD B      | USARTA                 |
+-------------+------------------------+
| Raspberry   | USARTA & UARTB         |
+-------------+------------------------+

Custom UART
-----------

In order to control a UART that has not been pre-defined by libyggdrasil, first it needs to be properly configured through the project's .ioc file. 
Once this is done, the new UART can be defined like this:

.. tabs::

    .. code-tab:: c

        uart_t MyUART = { &huart2 };				

    .. code-tab:: cpp

        using MyUART = bsp::drv::UART<0x4000'4400, bsp::mid::drv::UART>;    // Base address

and then used like all the other UART.