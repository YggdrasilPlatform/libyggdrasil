Boot Modes
==========

On Yggdrasil, a 2 bit DIP switch can be found above the Display. The value configured on it is used during bootup of the plugged in World Board to determine where to boot from.

Since the configuration varies between different SoCs, here's a list of all possible modes for all existing World Boards.


Midgard
-------

===== ===== ========================================================
BOOT0 BOOT2 Description
===== ===== ========================================================
OFF   OFF   Boot from Flash at Address ``0x0020'0000``
ON    OFF   Boot from internal Bootloader at Address ``0x0010'0000``
OFF   ON    Boot from Flash at Address ``0x0020'0000``
ON    ON    Boot from internal Bootloader at Address ``0x0010'0000``
===== ===== ========================================================


Asgard
-------

===== ===== ========================================================
BOOT0 BOOT2 Description
===== ===== ========================================================
OFF   OFF   Boot from a Serial interface (UART or USB)
ON    OFF   Boot from a Serial NOR Flash over QUADSPI
OFF   ON    Engineering mode for development with the CubeIDE
ON    ON    BOOT from SD-Card on SDMMC1
===== ===== ========================================================

If booting fails because no FSBL can be loaded from the selected source, Asgard automatically retries from a Serial interface.