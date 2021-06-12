GPIO Access
===========

Using Sysfs
-----------

The easiest way to access GPIOs is through ``sysfs``. This works for all pins that haven't been defined in the device tree and are being used by any driver.

To use a GPIO, it first needs to be exported and configured:

.. code-block:: shell

    $ echo [gpio_number] > /sys/class/gpio/export

.. code-block:: shell

    $ echo [in|out] > /sys/class/gpio/gpio[gpio_number]/direction

.. code-block:: shell

    $ cat /sys/class/gpio/gpio[gpio_number]/value
    $ echo [0|1] > /sys/class/gpio/gpio[gpio_number]/value

The ``gpio_number`` value can be calculated as follows.

.. raw:: html

    <form>
        <select name="port" id="port" onchange="doGPIOCalculation()">
            <option value="0">GPIO A</option>
            <option value="1">GPIO B</option>
            <option value="2">GPIO C</option>
            <option value="3">GPIO D</option>
            <option value="4">GPIO E</option>
            <option value="5">GPIO F</option>
            <option value="6">GPIO G</option>
            <option value="7">GPIO H</option>
            <option value="8">GPIO I</option>
            <option value="9">GPIO J</option>
            <option value="10">GPIO K</option>
        </select>

        <select name="pin" id="pin" onchange="doGPIOCalculation()">
            <option value="0">Pin 0</option>
            <option value="1">Pin 1</option>
            <option value="2">Pin 2</option>
            <option value="3">Pin 3</option>
            <option value="4">Pin 4</option>
            <option value="5">Pin 5</option>
            <option value="6">Pin 6</option>
            <option value="7">Pin 7</option>
            <option value="8">Pin 8</option>
            <option value="9">Pin 9</option>
            <option value="10">Pin 10</option>
            <option value="11">Pin 11</option>
            <option value="12">Pin 12</option>
            <option value="13">Pin 13</option>
            <option value="14">Pin 14</option>
            <option value="15">Pin 15</option>
        </select>
    </form>

    <script>
        function doGPIOCalculation() {
            var gpio = document.getElementById("port").value;
            var pin = document.getElementById("pin").value;

            var value = (parseInt(gpio) * 16) + parseInt(pin);

            var calculation = document.getElementById("gpio_calculation");
            calculation.innerHTML = "GPIO = (Port * 16) + Pin = (" + gpio + " * 16) + " + pin + " = " + value;

        }
    </script>

|

.. raw:: html

    Calculation: <code class="docutils literal notranslate"><span class="pre" id="gpio_calculation"></span></code>

    <script>doGPIOCalculation();</script>