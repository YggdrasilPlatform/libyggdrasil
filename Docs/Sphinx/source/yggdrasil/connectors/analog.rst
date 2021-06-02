.. _AnalogConnector:

Analog Header
=============

The analog header gives easy access to the two DAC channels ``DACA`` and ``DACB`` as well as the four ADC channels ``ADCA`` to ``ADCD``.

.. seealso::
    * :ref:`ADC Hardware Driver <AdcInterface>`
    * :ref:`DAC Hardware Driver <DacInterface>`

Connector
---------

.. image:: assets/analog.png
    :width: 80%
    :alt: Analog connector
    :align: center

|

.. important::
    The reference voltage of all analog pins is 3.3V. To prevent damaging the hardware, avoid applying a voltage higher than the reference voltage or lower than 0V to it.
