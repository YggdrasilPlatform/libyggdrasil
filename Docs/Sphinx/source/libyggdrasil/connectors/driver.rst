.. _PpDriverConnector:

Push-Pull Driver Header
=======================

| The Push-Pull Driver Pins can be used as GPIOs with the ability to drive or sink up to 2A at 3.3V or 5V, to control Servo motors or to generate PWMs.
| Each Driver Channel also has an LED to show activity. 

.. seealso::
    * :ref:`Push Pull Driver Peripheral Driver <PpDriverPeripheral>`

Connector
---------

.. image:: assets/ppdriver.png
    :width: 60%
    :alt: Push Pull Driver
    :align: center

.. important::
    VP can be configured between 3.3V and 5V by closing either solder bridge SB3 or SB4 located next to the DC Motor header.
    Changing this solder bridge also affects the voltage applied on the DC motor header.

    ========== =============
    VP Voltage Solder bridge
    ========== =============
    3.3V       SB3
    5V         SB4
    ========== =============
