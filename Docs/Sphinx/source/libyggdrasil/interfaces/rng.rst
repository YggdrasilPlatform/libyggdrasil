.. _RngInterface:

RNG Hardware
============

.. note::
    The RNG harware is a true random number generator based on entropy. It allows reading of guaranteed true random data and numbers.


Simple Usage
------------

The interface allows reading of an arbitrary amount of random data into any default constructible type.

.. tabs::

    .. code-tab:: c

        // Get a random 32 bit value
        u32 random32BitValue = yggdrasil_RNG_GetU32();

    .. code-tab:: cpp

        // Get a random 32 bit value
        auto random32BitValue = bsp::RNG::get<u32>();

        // Get a random array of 512 u8
        auto random512Bytes = bsp::RNG::get<std::array<u8, 512>>();

.. important::
    The hardware generates 4 random bytes at once every 42 cycles of the RNG clock.
    If more than 4 bytes are requested, the core will wait until enough data has been generated.

.. note::
    The RNG hardware's noise source consists of three free-running ring oscillators XORed together.
    If more than 64 consecutive ``0`` or ``1`` or more than 32 consecutive ``01`` or ``10`` are generated,
    the RNG hardware will set a error flag and halt to prevent non-random output being read. If this happens,
    the RNG hardware needs to be restarted in order to work again.