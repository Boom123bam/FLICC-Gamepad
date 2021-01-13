/* Copyright 2020 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "joystick.h"
//#include <print.h>
#include "analog.h"

//CHANGE THIS
char arrow_keys[4] = {KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT}; // up, left, down, right


static uint8_t joystickMode = 0;
static uint8_t joystick_modes = 2; // amount of modes
static int actuation = 256; // actuation point for arrows (0-511)

enum my_keycodes {
  JSMODE = SAFE_RANGE,
};

bool arrows[4];

// layer leds
#define LED1 D7 // pin 6
#define LED2 C6 // pin 5
#define LED3 D0 // pin 3

// runs on startup
void keyboard_pre_init_user(void) {
    // set pins as output
    setPinOutput(LED1);
    setPinOutput(LED2);
    setPinOutput(LED3);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    MO(1),
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_LCTL,   KC_LGUI,   KC_LALT,   KC_RALT,             KC_SPC
    ),

    [1] = LAYOUT(
        KC_ESC,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   JSMODE,             KC_TRNS
    ),
    

};




//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

//#ifdef CONSOLE_ENABLE
//    uprintf("kc:%u x:%u y:%u mode:%u\n", analogReadPin(F5), analogReadPin(F4), keycode, joystickMode, record->event.pressed);
//#endif 
    switch(keycode) {
    case JSMODE:
        if (record->event.pressed) {
            joystickMode++;
        	if (joystickMode == joystick_modes){
        		joystickMode = 0;
            }
        }
    }
    return true;
}

void joystick_task(){

	switch (joystickMode) {
	case 0: // gamepad
		joystick_status.axes[0] = -(analogReadPin(F5)/4 - 127);
		joystick_status.axes[1] = analogReadPin(F4)/4 - 128;
		joystick_status.status |= JS_UPDATED;
        send_joystick_packet(&joystick_status);
		break;
    case 1: // arrows
        if (!arrows[0] && analogReadPin(F5) - 512 > actuation){
            arrows[0] = true;
            register_code16(arrow_keys[1]);
        }
        else if (arrows[0] &&  analogReadPin(F5) - 512 < actuation){
            arrows[0] = false;
            unregister_code16(arrow_keys[1]);
        }
        if (!arrows[1] && analogReadPin(F5) - 512 < -actuation){
            arrows[1] = true;
            register_code16(arrow_keys[3]);
        }
        else if (arrows[1] && analogReadPin(F5) - 512 > -actuation){
            arrows[1] = false;
            unregister_code16(arrow_keys[3]);
        }
        if (!arrows[2] && analogReadPin(F4) - 512 > actuation){
            arrows[2] = true;
            register_code16(arrow_keys[2]);
        }
        else if (arrows[2] &&  analogReadPin(F4) - 512 < actuation){
            arrows[2] = false;
            unregister_code16(arrow_keys[2]);
        }
        if (!arrows[3] && analogReadPin(F4) - 512 < -actuation){
            arrows[3] = true;
            register_code16(arrow_keys[0]);
        }
        else if (arrows[3] && analogReadPin(F4) - 512 > -actuation){
            arrows[3] = false;
            unregister_code16(arrow_keys[0]);
        }
        break;

    /*case 2: // mouse

        report_mouse_t currentReport = pointint_device_get_report()
        currentReport.x = (analogReadPin(F5)-512)/4;
        currentReport.y = -(analogReadPin(F4)-512)/4;
        pointint_device_set_report(currentReport);
        poining_device_send();
        break;*/
	}
}

// Automatically sets leds based on the layer
uint32_t layer_state_set_user(uint32_t state) {

    // first turn all leds off
    writePin(LED1, 0);
    writePin(LED2, 0);
    writePin(LED3, 0);

    switch(biton32(state)) {
        case 0:
            // no lights
            break;

        case 1:
            writePin(LED1, 50);
            break;

        case 2:
            writePin(LED2, 50);
            break;

        case 3:
            writePin(LED3, 50);
            break;

        case 4:
            writePin(LED1, 50);
            writePin(LED2, 50);
            break;

        case 5:
            writePin(LED1, 50);
            writePin(LED3, 50);
            break;

        case 6:
            writePin(LED2, 50);
            writePin(LED3, 50);
            break;

        case 7:
            writePin(LED1, 50);
            writePin(LED2, 50);
            writePin(LED3, 50);
            break;

    }
    return state;
}
