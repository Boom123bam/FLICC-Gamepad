# FLICC Gamepad

## Setup

specify your bootload in rules.mk
example:

`BOOTLOADER = caterina`

## Flashing
`make flicc:<keymap name>:avrdude`

example:

`make flicc:default:avrdude`

or:

`make flicc:mk:avrdude`
