# WeMos D1 Mini + Nokia 5110 PCD8544 LCD Module

The D1 mini board:
http://wemos.cc

Tool used to convert .bmp to byte arrays:
http://javl.github.io/image2cpp/

## Materials:
* WeMos D1 Mini
* Nokia 5110 PCD8544 84x48 monochrome LCD
* 8 jumper wires
* breadboard

## Dependencies:

Add these to your Arduino IDE using Manage Libraries.

* [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit PCD8544 Nokia 5110 LCD library](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library)
  * There is a pull request that adds ESP8266 support:
  * [adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library#27](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library/pull/27)
  * If this has not been merged yet, you will need to manually copy the changes across

## Breadboard connections:

WeMos D1 Mini | Nokia 5110 PCD8544 LCD | Description
------------- | ---------------------- | ---------------------------------------------
D2 (GPIO4)    | 0 RST                  | Output from ESP to reset display
D1 (GPIO5)    | 1 CE                   | Output from ESP to chip select/enable display
D6 (GPIO12)   | 2 DC                   | Output from display data/command to ESP
D7 (GPIO13)   | 3 Din                  | Output from ESP SPI MOSI to display data input
D5 (GPIO14)   | 4 Clk                  | Output from ESP SPI clock
3V3           | 5 Vcc                  | 3.3V from ESP to display
D0 (GPIO16)   | 6 BL                   | 3.3V to turn backlight on, or PWM
G             | 7 Gnd                  | Ground

These connections are common to all examples.

The backlight (BL) is optional.
If you would like full brightness all the time, connect BL to 3V3 and save D0 for something else.
