RTC RV-3028-C7
==============

.. seealso::
    * `RV-3028-C7 Datasheet <_static/datasheets/yggdrasil/RV-3028-C7.pdf>`_ 
    * `RV-3028-C7 Application Manual2 <_static/datasheets/yggdrasil/RV-3028-C7_App-Manual.pdf>`_ 


Description
-----------

The RV-3028-C7 is a SMT Real-Time Clock Module that incorporates an integrated CMOS circuit together with an XTAL.

* Extreme low power consumption: 45 nA @ 3 V.

Usage
-----

The example below shows how to set a new time. If the time is once set correctly, there is a backup battery which provides the rtc alway with the needed power.

.. code-block:: cpp

    tm setTime = {0};
    // Fill up the tm struct for 21 / 05 / 2021 (Friday)
    setTime.tm_year = 121;      // Year since 1900
    setTime.tm_mon = 5;         // Months since january
    setTime.tm_mday = 21;       // Day of the month
    setTime.tm_hour = 10;       // Hour
    setTime.tm_min = 30;        // Minutes
    setTime.tm_sec = 00;        // Seconds
    setTime.tm_wday = 5;        // Days since sunday

    // Send the new time to the rtc
    RealTimeClock::setTime(mktime(&setTime));


To read the time from the rtc, this example shows how. 

.. code-block:: cpp

    time_t time = RealTimeClock::getTime();


When the time should be printed, the example below shows an easy way.

.. code-block:: cpp

    std::string buffer(0xFF, 0x00);
    tm * time;

    // Read the time as a time_t
    time_t rtcTime = bsp::ygg::prph::RealTimeClock::getTime();

    // Transform to a tm struct
    time = gmtime(&rtcTime);
    // Get the time formatted
    strftime(buffer.data(), buffer.size(), "%c", time);
    printf("Time: %s \n", buffer.data());

.. seealso::
    * `strftime <https://www.cplusplus.com/reference/ctime/strftime/>`_ 
    * `tm struct <https://www.cplusplus.com/reference/ctime/tm//>`_ 