# Build Guide

## Parts
### Included
| Item | Count |
|:-|:-|
| PCB                   | 1      |
| Plate                 | 1      |
| Case (+screws)        | 1      |
| Diode                 | 30     |
| Hot-swap sockets      | 30     |
| LEDs                  | 3      |
| Resistors             | 3      |
| Rubber feet           | 4      |
| ProMicro              | 1      |
| Joystick potentiometer| 1      |
| Joystick cap          | 1      |


## Testing the pro micro

Downlaod arduino IDE https://www.arduino.cc/en/main/software

Downlaod the Joystick library by MHeironimus,
follow the installation instructions on https://github.com/MHeironimus/ArduinoJoystickLibrary

Download the keypad library by Nullkraft, the same way as the joystick library
https://github.com/Nullkraft/Keypad


After downloading the libraries, download and open the firmware on this repository.
Plug the pro-micro in, and in the arduino IDE, go to tools -> port and you should see Arduino Leonardo or Arduino Micro, select it.
Go to tools -> boards and make sure it is the same as the port.

Click upload(next to the tick) and wait for it to finish.

Here is an image of the row and column pins
![image](https://i.imgur.com/XJMheTZ.jpg)

Use this to test the pro-micro by connecting a row with a column with tweezers or a wire, a button should press.
You can go to https://config.qmk.fm/#/test and test that every button works. Note that someetimes it will not activate a button because there are less buttons on some rows.

