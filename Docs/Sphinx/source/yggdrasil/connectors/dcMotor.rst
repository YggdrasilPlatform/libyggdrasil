.. _DcMotorConnector:

DC Motor Connector
==================

The DC Motor Connector exposes a dual H-Bridge used for driving DC motors.

.. seealso::
    * :ref:`DC Motor Peripheral Driver <MotorDriverPeripheral>`

Connector
---------

.. rst-class:: only-light

    .. image:: assets/dcMotor_light.png
        :width: 40%
        :alt: Dual DC Motor connector
        :align: center

.. rst-class:: only-dark

    .. image:: assets/dcMotor_dark.png
        :width: 40%
        :alt: Dual DC Motor connector
        :align: center


.. important::
    The voltage of the Motor channels can be configured between 3.3V and 5V by closing either solder bridge SB3 or SB4 located next to the DC Motor header.
    Changing this solder bridge also affects the voltage applied on the Push Push Driver Header.

    ========== =============
    CH Voltage Solder bridge
    ========== =============
    3.3V       SB3
    5V         SB4
    ========== =============