.. _HashInterface:

Hashing Hardware
================

.. note::
    The hashing hardware gives access to hardware accelerated CRC, SHA, MD5 and HMAC calculations.
    These are mainly used to guarantee the validity of data very quickly. 


Simple Usage
------------

Implementations for the following algorithms are available:

* CRC8
    * Default Init Value: 0x00
    * Default Polynomial: 0x07
    * Default Xor Out: 0x00
* CRC16
    * Default Init Value: 0x0000
    * Default Polynomial: 0x8005
    * Default Xor Out: 0x0000
* CRC32
    * Default Init Value: 0xFFFF'FFFF
    * Default Polynomial: 0x04C1'1DB7
    * Default Xor Out: 0xFFFF'FFFF

CRC
^^^

The interface for all CRC algorithms are the same.
This is how to use the CRC32 hardware for example with default settings. In C the default values must be provided anytime.

.. tabs::

    .. code-tab:: c

        u8 data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        // Get the CRC32 result with default values
        u32 crc32 = yggdrasil_HASH_getCRC32(data, sizeof(data), 0xFFFFFFFF, 0x04C11DB7, 0xFFFFFFFF);

    .. code-tab:: cpp

        std::array<u8, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        
        // Get the CRC32 result with default values
        u32 crc32 = bsp::Hash::getCRC32(data);

To use different settings, they can be provided as additional arguments.

.. tabs::

    .. code-tab:: c

        u8 data[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

        const u32 initialValue = 0x00000000;
        const u32 polynomial   = 0x814141AB;
        const u32 xorOut       = 0x00000000;

        // Get the CRC32 result with custom settings
        u32 crc32 = yggdrasil_HASH_getCRC32(data, sizeof(data), initialValue, polynomial, xorOut);

    .. code-tab:: cpp

        std::array<u8, 10> data = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

        constexpr u32 InitialValue = 0x0000'0000;
        constexpr u32 Polynomial   = 0x8141'41AB;
        constexpr u32 XorOut       = 0x0000'0000;

        // Get the CRC32 result with custom settings
        u32 crc32 = bsp::Hash::getCRC32(data, InitialValue, Polynomial, XorOut);

.. note::
    The initial value sets what value the calculation should start on. For many hash algorithms, this can be used to add more data to a previously calculated hash.
    
    The polynomial is used for the calculation and differs between different "flavours" of the same CRC.
    
    The XorOut value specifies what bits to invert after the calculation is done. ``( Result = Result ^ XorOut )``