.. _midgard_getting_started:

Midgard
=======

Getting Started
---------------

To start using libyggdrasil on Midgard, first include it and specify what board is being used. 

.. code-block:: cpp

    #define BOARD MIDGARD
    #define YGGDRASIL_PERIPHERAL_DEFS
    #include <yggdrasil.h>

| The :code:`#define BOARD MIDGARD` directive tells libyggdrasil that Midgard is being used.
| The :code:`#define YGGDRASIL_PERIPHERAL_DEFS` directive tells libyggdrasil to define all peripheral definitions and also enable the Yggdrasil peripheral drivers. 

.. warning::
    :code:`YGGDRASIL_PERIPHERAL_DEFS` may only be used with the default Midgard template. If any existing peripherals are disabled,
    or configurations are changed, this may no longer work or even compile!
    Instead you need to define your own peripheral definitions as seen in :code:`libyggdrasil/midgard/interfaces.hpp`