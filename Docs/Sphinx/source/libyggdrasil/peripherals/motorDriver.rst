.. _MotorDriverPeripheral:

DC Motor Driver
===============
**Toshiba TC78H660FTG dial H Bridge**

.. admonition:: Datasheets
    
    * `TC78H660FTG Datasheet </_static/datasheets/yggdrasil/TC78H660FTG.pdf>`_ 

Description
-----------

The TC78H660FTG is a dual H Bridge driver IC which incorporates DMOS
with low on-resistance in output transistors. It can control two DC brushed motors or one stepping motor.

.. note::
    The driver IC got multi error detect functions built in, such as:

    * Thermal shutdown (TSD)
    * Over current (ISD)
    * Under voltage lockout(UVLO)

    After an occurred error, the driver must be reactivated.

Usage
-----

Each motor can be set individually as shown in the example below.

.. tabs::

    .. code-tab:: c

        // Enable the motor on channel A with a duty cycle of 75% in cw direction
        yggdrasil_MotorDriver_SetSpeed(MotorDriverChannel_A, 75);

        // Enable the motor on channel B with a duty cycle of 10% in ccw direction
        yggdrasil_MotorDriver_SetSpeed(MotorDriverChannel_B, -10);

    .. code-tab:: cpp

        // Enable the motor on channel A with a duty cycle of 75% in cw direction
        bsp::ygg::prph::MotorDriver::setSpeed(bsp::ygg::prph::MotorDriver::Channel::A, 75);

        // Enable the motor on channel B with a duty cycle of 10% in ccw direction
        bsp::ygg::prph::MotorDriver::setSpeed(bsp::ygg::prph::MotorDriver::Channel::B, -10);


To handle errors correctly, the error state should be checked. If there occurs an error such as an over current, the driver will be shut down until a proper restart.
The easiest way to do this is, tu put the driver in standby, wait for at least 100ms and wake him up again.
The example below is not suitable for a system without an rtos and may need some modification. But this is the simplest possible implementation.

.. tabs::

    .. code-tab:: c

        while (1) {
            // Enable the motor on channel B with a duty cycle of 100% in cw direction
            yggdrasil_MotorDriver_SetSpeed(MotorDriverChannel_B, 100);

            // Check the state of the driver
            while (!yggdrasil_MotorDriver_GetError());

            // Shut down the driver, set the driver to standby
            yggdrasil_MotorDriver_Standby(true);
            // Delay until restart
            core_Delay(100);

            /* Your error handling */

            // Restart the driver
            yggdrasil_MotorDriver_Standby(false);
        }

    .. code-tab:: cpp

        while (true) {
            // Enable the motor on channel B with a duty cycle of 100% in cw direction
            bsp::ygg::prph::MotorDriver::setSpeed(bsp::ygg::prph::MotorDriver::Channel::B, 100);

            // Check the state of the driver
            while (!bsp::ygg::prph::MotorDriver::getError());

            // Shut down the driver, set the driver to standby
            bsp::ygg::prph::MotorDriver::standby(true);
            // Delay until restart
            bsp::core::delay(100);

            /* Your error handling */

            // Restart the driver
            bsp::ygg::prph::MotorDriver::standby(false);
        }
