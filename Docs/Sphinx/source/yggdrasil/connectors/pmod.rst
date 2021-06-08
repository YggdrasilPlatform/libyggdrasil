.. _PmodConnector:

Pmod Connectors
===============

Pmod is an interface used mainly in extension boards for development platforms and has multiple different types. 

.. seealso::
    * :ref:`UART Hardware Driver <UartInterface>`
    * :ref:`I2C Hardware Driver <I2cInterface>`
    * :ref:`SPI Hardware Driver <SpiInterface>`
    * :ref:`Timer Hardware Driver <TimerInterface>`

PMod Power
----------

Different types of PMod extension boards need different supply voltages. Therefor it's possible to choose between 3.3V and 5V to be applied to all ``PMod Power`` Pins by changing the position of Jumper ``JP2`` located between the PMod connectors.

.. warning::
    Make absolutely sure that the PMod Power Jumper is set to the correct setting **before** pluging in a board. A wrong setting
    may fry the extension board. 

Connector
---------

PMod A
^^^^^^

.. note::
    This connector is compatible with Type 2 and 6.

.. rst-class:: only-light

    .. image:: assets/pmoda_light.png
        :width: 80%
        :alt: PMod A Type 2 / 6
        :align: center

.. rst-class:: only-dark

    .. image:: assets/pmoda_dark.png
        :width: 80%
        :alt: PMod A Type 2 / 6
        :align: center


PMod B
^^^^^^

.. note::
    This connector is compatible with Type 3 and 6.

.. rst-class:: only-light

    .. image:: assets/pmodb_light.png
        :width: 80%
        :alt: PMod B Type 3 / 6
        :align: center

.. rst-class:: only-dark

    .. image:: assets/pmodb_dark.png
        :width: 80%
        :alt: PMod B Type 3 / 6
        :align: center
