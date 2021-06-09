Yggdrasil Platform
==================

.. image:: assets/title.jpg
   :width: 100%
   :alt: Yggdrasil
   :align: center

.. important::

   Yggdrasil is the embedded development platform for Students at the Bern University of Applied Sciences. It’s designed specifically to allow a unified learning experience throughout the Bachelor studies by combining Bare-Metal Microcontroller development and modern Linux / Android programming into a single multi-purpose development board.


Overview
--------

The Yggdrasil development platform consists of two parts. 

One is the **Yggdrasil peripheral board**. 
It contains most of the peripherals used during development and has many interfaces to connect additional hardware to it.

The other one are the **World Boards**. They are small SODIMM314 compatible SoC cards that contain some SoC and everything that's needed for it to run. They can plugged in directly into the **World Connector** on the bottom of Yggdrasil.


Source code
-----------

Source code for all libraries, examples, templates, ports as well as this documentation can be found easily on `GitLab <https://gitlab.ti.bfh.ch/yggdrasil>`_.

.. toctree::
   :maxdepth: 1
   :caption: Contents:
   :hidden:
   
   yggdrasil/yggdrasil
   world_boards/world_boards
   libyggdrasil/libyggdrasil