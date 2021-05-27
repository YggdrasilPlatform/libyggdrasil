.. _UartInterfaceCpp:

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

.. code-block:: cpp

    // Read string from console
    std::string string = bsp::UARTB::readString();

    // Read 10 bytes from the console
    std::array<u8, 10> = bsp::UARTB::read<10>();

.. code-block:: cpp

    // Send string to console
    bsp::UARTB::write("Hello World!");

    // Send 10 bytes to the console
    std::array<u8, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    bsp::UARTB::write(data);

Available ports
---------------

+-------------+------------------------+
| Port        | Bus                    |
+=============+========================+
| ST-Link COM | UARTST                 |
+-------------+------------------------+
| PMOD B      | USARTA                 |
+-------------+------------------------+
| Raspberry   | USARTA & UARTB         |
+-------------+------------------------+
