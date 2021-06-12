.. _asgard_a7_getting_started:

Linux
=====

Setup
-----

To start developing on the Yggdrasil platform with Linux using Asgard, the following things are needed:

.. seealso::
    * `VSCode <https://code.visualstudio.com/>`_
    * `Asgard Linux Template <https://gitlab.ti.bfh.ch/yggdrasil/asgard/asgard_linux_template>`_
    * Asgard Toolchain
    * A WSL2 or Linux setup
    * Meson

Download and install VSCode. Then either setup WSL2 or a Linux VM if you're using Windows or use a native Linux installation.

Download the Asgard Toolchain and extract it to ``/opt/yggdrasil``. If desired, add the ``/opt/yggdrasil/bin`` folder to your ``PATH``.

Getting Started
---------------

Clone the Asgard Linux Template (make sure to clone all submodules with ``--recurse-submodules``) into your Development directory. To setup everything now, run

.. code-block:: shell

    $ meson build --cross-file=yggdrasil

To compile the project use

.. code-block:: shell

    $ meson compile -C build