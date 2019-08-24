## What the example does

Initializes the driver. Changes colors using `dled_pixel_rainbow_step()`.

## Connecting

The common precautions should be applied to the test circuit. See [an article from
Adafruit](https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections).

You definitely need external power (5V) for WS2812. For level shift from 3.3 V
to 5 V, simple FET level shifter should work.

Number of pixels (8 by default) can be modified by `menuconfig`
(`esp32_digitalLEDs demo application` -> `Number of pixels`).

| ESP32    | WS2812 |
|----------|--------|
| `GPIO16` | `DIN`  |
