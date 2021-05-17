RNG Hardware
============

.. note::
    The RNG harware is a true random number generator based on entropy. It allows reading of guaranteed true random data and numbers.


Simple Usage
------------

The interface allows reading of an arbitrary amount of random data into any default constructible type.

.. code-block:: cpp

    auto random32BitValue = bsp::RNG::get<u32>();
    auto random512Bytes = bsp::RNG::get<std::array<u8, 512>>();

.. important::
    Important to note is, the hardware generates 4 random bytes at once.
    If more than 4 bytes are requested, the core will wait until enough data has been generated.