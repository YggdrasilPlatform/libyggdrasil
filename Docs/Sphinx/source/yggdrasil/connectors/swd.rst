.. _SwdConnector:

SWD Debug Port
==============

The SWD Debug Port allows flashing and debugging of external PCBs over the integrated STLINK-V3.

.. warning::

    When debugging an external PCB, make sure no World Board is plugged into the World Connector. Otherwise the two SoCs will interfere with each other.

.. note::
    
    Depending on the voltage the target board uses, it's possible to switch the ``Target V+`` between 3.3V and 5V.
    For the World Boards, 3.3V should be used, however the JTAG pins are 5V tollerant.

Connector
---------

.. rst-class:: only-light

    .. image:: assets/swd_light.png
        :width: 80%
        :alt: SWD connector
        :align: center

.. rst-class:: only-dark

    .. image:: assets/swd_dark.png
        :width: 80%
        :alt: SWD connector
        :align: center