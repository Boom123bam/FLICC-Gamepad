# FLICC Gamepad

## Setup

specify your bootload in rules.mk
example:

`BOOTLOADER = caterina`

## Flashing
`make flicc:<keymap name>:avrdude`

example (caterina):

`make flicc:default:avrdude`

or (atmel-dfu):

`make flicc:default:dfu`

see more info at [QMK Flashing Firmware](https://beta.docs.qmk.fm/tutorial/newbs_flashing)
