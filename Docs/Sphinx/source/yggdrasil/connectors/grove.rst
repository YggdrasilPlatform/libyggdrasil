.. _GroveConnector:

Grove Connectors
================

Grove is a standardized connector for all sort of sensor extension boards developed by Seeed and others. 

.. seealso::
    * :ref:`I2C Hardware Driver <I2cInterface>`

Grove Power
-----------

Different types of Grove extension boards need different supply voltages. Therefor it's possible to choose between 3.3V and 5V to be applied to all ``Vgrove`` Pins by changing the position of Jumper ``JP3`` located next to the Grove A connector.

.. warning::
    Make absolutely sure that the Grove Power Jumper is set to the correct setting **before** pluging in a board. A wrong setting
    may fry the extension board. 

Connector
---------

Grove A
^^^^^^^

.. rst-class:: only-light

    .. image:: assets/grovea_light.png
        :width: 40%
        :alt: Grove A
        :align: center

.. rst-class:: only-dark

    .. image:: assets/grovea_dark.png
        :width: 40%
        :alt: Grove A
        :align: center


Grove B
^^^^^^^

.. rst-class:: only-light

    .. image:: assets/groveb_light.png
        :width: 40%
        :alt: Grove B
        :align: center

.. rst-class:: only-dark

    .. image:: assets/groveb_dark.png
        :width: 40%
        :alt: Grove B
        :align: center