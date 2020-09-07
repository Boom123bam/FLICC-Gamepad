# Build Guide

## Parts
### Included
| Item | Count |
|:-|:-|
| PCB                   | 1      |
| Plate (+pin headers)  | 1      |
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

You can also test the LEDs by connecting the longer end to either pin 3,5 or 6 and the shorter end to a GND pin.

If it works, you're all set to move on!


## Soldering

### Pro-micro

Solder the pro micro in with the pin headers, as shown in the image. Make sure it's sitting flush before soldering.
![image](https://i.imgur.com/qnvoUzn.jpg)

Then, cut the extra pins on the botton.

### USB Stuff

This is perhaps the hardest part of the build.

Take the micro-usb connector and tin(add a bit of solder) the soldering points. Helping hands (ones for soldering) are highly recommended.
Place the tip of the soldering iron on the edge of the solder pad and apply solder onto the pad. Try not to burn the black plastic.

![image](https://i.imgur.com/ibTlG2V.jpg)

Left: un-tinned | Right: tinned

Plug the connector into the pro-micro.
