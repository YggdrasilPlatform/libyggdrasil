.. _RtcPeripheral:

Real Time Clock
===============
**Micro Crystal RV-3028-C7 RTC**

.. admonition:: Datasheets
    
    * `RV-3028-C7 Datasheet </_static/datasheets/yggdrasil/RV-3028-C7.pdf>`_ 
    * `RV-3028-C7 Application Manual2 </_static/datasheets/yggdrasil/RV-3028-C7_App-Manual.pdf>`_ 


Description
-----------

The RV-3028-C7 is a SMT Real-Time Clock Module that incorporates an integrated CMOS circuit together with an XTAL.

* Extreme low power consumption: 45 nA @ 3 V.

Usage
-----

The example below shows how to set a new time. If the time is once set correctly, there is a backup battery which provides the rtc alway with the needed power.

.. tabs::

    .. code-tab:: c

        struct tm setTime = { 0 };
        // Fill up the tm struct for 24 / 05 / 2021 (Monday)
        setTime.tm_year = 121;      // Years since 1900
        setTime.tm_mon = 4;         // Months since january
        setTime.tm_mday = 24;       // Day of the month
        setTime.tm_hour = 10;       // Hour
        setTime.tm_min = 30;        // Minutes
        setTime.tm_sec = 00;        // Seconds
        setTime.tm_wday = 1;        // Days since sunday

        // Send the new time to the rtc
        yggdrasil_RealTimeClock_SetTime(mktime(&setTime));

    .. code-tab:: cpp

        tm setTime = { 0 };
        // Fill up the tm struct for 24 / 05 / 2021 (Monday)
        setTime.tm_year = 121;      // Years since 1900
        setTime.tm_mon = 4;         // Months since january
        setTime.tm_mday = 24;       // Day of the month
        setTime.tm_hour = 10;       // Hour
        setTime.tm_min = 30;        // Minutes
        setTime.tm_sec = 00;        // Seconds
        setTime.tm_wday = 1;        // Days since sunday

        // Send the new time to the rtc
        bsp::ygg::prph::RealTimeClock::setTime(mktime(&setTime));


To read the time from the rtc, this example shows how. 

.. tabs::

    .. code-tab:: c

        time_t time = yggdrasil_RealTimeClock_GetTime();

    .. code-tab:: cpp

        time_t time =  bsp::ygg::prph::RealTimeClock::getTime();


When the time should be printed, the example below shows an easy way.

.. tabs::

    .. code-tab:: c

        char buffer[0xFF] = { 0 };
        struct tm * time;

        // Read the time as a time_t
        time_t rtcTime = yggdrasil_RealTimeClock_GetTime();

        // Transform to a tm struct
        time = gmtime(&rtcTime);
        // Get the time formatted
        strftime(buffer, sizeof(buffer), "%c", time);
        printf("Time: %s \n", buffer);

    .. code-tab:: cpp

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