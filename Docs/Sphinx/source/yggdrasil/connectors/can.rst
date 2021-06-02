.. _CanConnector:

CAN Connectors
==============

The CAN connectors give access to two, optionally terminated CAN interfaces. 

.. seealso::
    * :ref:`CAN Hardware Driver <CanInterface>`

.. important::
    Both CAN connectors are Galvantically isolated from the rest of Yggdrasil. They need therefor be supplied externally using the screw terminals.

Connector
---------

CAN A
^^^^^

.. image:: assets/cana.png
    :width: 30%
    :alt: CAN A
    :align: center

CAN B
^^^^^

.. image:: assets/canb.png
    :width: 30%
    :alt: CAN B
    :align: center

Termination
-----------

The last device on the CAN bus is required to terminate the bus with a :math:`120\Omega` resistor. This can be done by bridging the termination jumpers JP4 or JP5 