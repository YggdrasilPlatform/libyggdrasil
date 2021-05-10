Asgard
======

Resources
---------

.. seealso::
    * `MPU STM32MP157C Datasheet <_static/datasheets/asgard/STM32MP157C/datasheet.pdf>`_ 
    * `MPU STM32MP157C Reference manual <_static/datasheets/asgard/STM32MP157C/reference_manual.pdf>`_ 
    * `MPU Arm Cortex M4 Reference manual <_static/datasheets/asgard/STM32MP157C/coreM4_reference_manual.pdf>`_ 
    * `MPU Arm Cortex A7 Reference manual <_static/datasheets/asgard/STM32MP157C/coreA7_reference_manual.pdf>`_ 
    * `PMIC STPMIC1 Datasheet <_static/datasheets/asgard/STPMIC1/datasheet.pdf>`_ 
    * `Ethernet Phy DP83867 Datasheet <_static/datasheets/asgard/DP83867/datasheet.pdf>`_ 
    * `DDR3L SDRAM MT41K256M16TW Datasheet <_static/datasheets/asgard/DDR3LSDRAM/datasheet.pdf>`_ 


Peripherals
-----------

MPU STM32MP157C
^^^^^^^^^^^^^^^

Core
""""
* 32-bit dual-core Arm® Cortex®-A7
    * L1 32-Kbyte I / 32-Kbyte D for each core
    * 256-Kbyte unified level 2 cache
    * Arm® NEON™ and Arm® TrustZone®
* 32-bit Arm® Cortex®-M4 with FPU/MPU
    * Up to 209 MHz (Up to 703 CoreMark®)

Memories
""""""""
* External DDR memory of 1 Gbyte DDR3/DDR3L-1066 16/32-bit
* 708 Kbytes of internal SRAM: 256 Kbytes of AXI SYSRAM + 384 Kbytes of AHB SRAM + 64 Kbytes of AHB SRAM in Backup domain and 4 Kbytes of SRAM in Backup domain
* Dual mode Quad-SPI memory interface
* Flexible external memory controller with up to 16-bit data bus: parallel interface to connect external ICs and SLC NAND memories with up to 8-bit ECC

Security/safety
"""""""""""""""
* Secure boot, TrustZone® peripherals, active tamper
* Cortex®-M4 resources isolation

Graphics
""""""""
* 3D GPU: Vivante® - OpenGL® ES 2.0
    * Up to 26 Mtriangle/s, 133 Mpixel/s
* LCD-TFT controller, up to 24-bit // RGB888
    * up to WXGA (1366 × 768) @60 fps or up to Full HD (1920 × 1080) @30 fps
    * Pixel clock up to 90 MHz
    * Two layers with programmable colour LUT
* MIPI® DSI 2 data lanes up to 1 GHz each


General-purpose input/outputs
"""""""""""""""""""""""""""""
* 176 I/O ports with interrupt capability
* Up to 8 secure I/Os
* Up to 6 Wakeup, 3 tampers, 1 active tamper















PMIC STPMIC1A
^^^^^^^^^^^^^

Ethernet Phy
^^^^^^^^^^^^

DDR3L SDRAM MT41K256M16TW
^^^^^^^^^^^^^^^^^^^^^^^^^