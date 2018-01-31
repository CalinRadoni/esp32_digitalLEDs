esp32_digitalLEDs
=================

(This is a *reStructuredText* version of ``README.md`` file)

Controls *WS2812B type* digital LEDs using the RMT peripheral of ESP32.

This implementation uses the RMT driver from ESP-IDF and uses one RMT channel 
for a LED strip **leaving the other channels free, under the control of the RMT driver**.
Here are some key points of this implementation:

- the control of the LEDs is separated in code from the control of the RMT peripheral;
- the other RMT channels can be used as needed;
- the RMT peripheral is used through ESP-IDF's own driver.

Right now the whole negative point is that this code uses a lot of RAM, *because of the 
way the driver and peripheral works*, but this will change *if/when* the driver will be 
updated with a hook in transmission code.

About timings
-------------

Timings are from datasheets.
According to `Worldsemi's datasheets <http://www.world-semi.com>`_ there are a few timings sets:

- one for WS2812
- one for WS2812B, WS2812C, WS2812S, WS2813 and WS2815
- one for WS2812D

In `cpldcpu (Tim's Blog) <https://cpldcpu.wordpress.com>`_ are some interesting investigations about timings of various digital LEDs.

Dependencies
------------

`Espressif IoT Development Framework`_

Hardware details
----------------

The code was tested using the following:

- ESP32-DevKitC board
- custom level convertor
- LED strip with 300 WS2812B digital LEDs
- good quality 5V power source

Development Environment
-----------------------

Main tools used where `Espressif IoT Development Framework`_ and *ESP32 toolchain for Linux*
(see `Standard Setup of Toolchain for Linux <https://github.com/espressif/esp-idf/blob/master/docs/get-started/linux-setup.rst>`_ 
for the latest version).

The code was mainly edited in `Visual Studio Code`_ but for shorter periods of time
I have used `Eclipse IDE for C/C++ Developers <https://www.eclipse.org>`_ and `Atom <https://atom.io/>`_ editor.

Version control with `Git <https://git-scm.com>`_.

License
-------

``esp32_digitalLEDs``'s software and documentation is released under the `GNU GPLv3`_ License. See the ``LICENSE-GPLv3.txt`` file.

``esp32_digitalLEDs``'s hardware schematics are licensed under a `Creative Commons Attribution-ShareAlike 4.0 International License`_.
See the ``LICENSE-CC-BY-SA-4.0.txt`` file.

Mentions
--------

I have *tested* the `MartyMacGyver's ESP32-Digital-RGB-LED-Drivers <https://github.com/MartyMacGyver/ESP32-Digital-RGB-LED-Drivers>`_.
The code is working OK, **but** it *captures* the whole RMT peripheral because it uses its custom interrupt handler routine.

.. _Espressif IoT Development Framework: https://github.com/espressif/esp-idf
.. _Visual Studio Code: https://code.visualstudio.com
.. _GNU GPLv3: http://www.gnu.org/licenses/gpl-3.0.html
.. _Creative Commons Attribution-ShareAlike 4.0 International License: http://creativecommons.org/licenses/by-sa/4.0/
