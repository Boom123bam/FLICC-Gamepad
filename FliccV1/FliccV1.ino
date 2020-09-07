#include <Joystick.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Keypad.h>

// special buttons
#define LAYER -1 // change layer
#define LEFT_CLICK -2 // mouse left
#define RIGHT_CLICK -3 // mouse right
#define MIDDLE_CLICK -4 // mouse middle
#define BUTTON_1 -5 // Triangle/Y
#define BUTTON_2 -6 // Circle/B
#define BUTTON_3 -7 // Cross/A
#define BUTTON_4 -8 // Square/X
#define BUTTON_5 -9 // LB
#define BUTTON_6 -10 // RB
#define BUTTON_7 -11 // LT
#define BUTTON_8 -12 // RT
#define BUTTON_9 -13 // Center 1(select)
#define BUTTON_10 -14 // Center 2(start)
#define BUTTON_11 -15 // L2
#define BUTTON_12 -16 // R2

//joystick modes
#define JOYSTICK 0
#define MOUSE 1
#define WASD 2
#define DOUBLE 3


//CHANGE:
//joystick:
const byte deadzone = 20; // 0=low deadzone, 127 = high deadzone
int wasdAct = 256; // Joystick actuation point for wasd (0-511)
int dbAct1 = 100;
int dbAct2 = 510;
char wasd[] = {'w', 'a', 's', 'd'};
char arrows[] = {KEY_UP_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW};
char db1[] = {KEY_UP_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW};
char db2[] = {'i', 'j', 'k', 'l'}; //double movement binds for fortnite
bool db = true; // activate double movement binds
const byte mouseRefresh = 1000;
const byte layers = 4;
const byte brightness = 50 ; // led brightness from 0 to 255


//DON'T CHANGE
int XAxis, YAxis; // x and y of joystick
int mouseSens = 10;// sensitivity when mouse mode
const int joystickMax = 1024; // max value of joystick
bool wasdstate[4];
bool dbstate1[4]; // previous state of double movement binds
bool dbstate2[4];
byte layer; // 0:mouse 1:analog 2:wasd 3:double
const byte COLS = 7;
const byte ROWS = 5;
byte mouseCount;


// Layouts

char keys[layers][ROWS][COLS] = {
  {
    {KEY_ESC, '1', '2', '3', '4', '5', '6'},
    {KEY_TAB, 'q', 'w', 'e', 'r', 't', 0},
    {KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 0},
    {KEY_LEFT_SHIFT, '/', 'z', 'x', 'c', 'v', 'b'},
    {KEY_LEFT_CTRL, KEY_LEFT_GUI, LAYER, 0, 0, MIDDLE_CLICK, ' '}

  },

  {
    {KEY_ESC, '1', '2', '3', '4', '5', '6'},
    {KEY_TAB, 'q', 'w', 'e', 'r', 't', 0},
    {KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 0},
    {KEY_LEFT_SHIFT, '/', 'z', 'x', 'c', 'v', 'b'},
    {KEY_LEFT_CTRL, KEY_LEFT_GUI, LAYER, 0, 0, LEFT_CLICK, ' '}
  },

  {
    {KEY_ESC, '1', '2', '3', '4', '5', '6'},
    {KEY_TAB, 'q', KEY_UP_ARROW, 'e', 'r', 't', 0},
    {KEY_CAPS_LOCK, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, 'f', 'g', 0},
    {KEY_LEFT_SHIFT, '/', 'z', 'x', 'c', 'v', 'b'},
    {KEY_LEFT_CTRL, KEY_LEFT_GUI, LAYER, 0, 0, LEFT_CLICK, ' '}
  },

  {
    {KEY_ESC, '1', '2', '3', '4', '5', '6'},
    {KEY_TAB, 'q', 'w', 'e', 'r', 't', 0},
    {KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 0},
    {KEY_LEFT_SHIFT, '/', 'z', 'x', 'c', 'v', 'b'},
    {KEY_LEFT_CTRL, KEY_LEFT_GUI, LAYER, 0, 0, KEY_LEFT_ALT, ' '}
  }
};

// Joystick modes for each layout
byte joystickMode[layers] = {JOYSTICK, MOUSE, WASD, DOUBLE};

// LED configuration for each layout 1=on 0=off
byte layerLEDs[layers][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};


byte colPins[COLS] = {9, 8, 7, 4, 2, 0, 1};
byte rowPins[ROWS] = {18, 15, 14, 16, 10};

int RXLED = 17; // RX LED
int TXLED = 30; // TX LED

// layer leds
int LED1 = 6;
int LED2 = 5;
int LED3 = 3;


Keypad kpd = Keypad(makeKeymap(keys[0]), rowPins, colPins, ROWS, COLS);
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  12, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);

void setup() {
  // put your setup code here, to run once:
  Joystick.begin();
  Keyboard.begin();
  Mouse.begin();

  pinMode(RXLED, OUTPUT); // Set RX LED as an output
  pinMode(TXLED, OUTPUT); // Set TX LED as an output
  leds(layer);
}

void loop() {
  digitalWrite(RXLED, HIGH); // set the LED off
  digitalWrite(TXLED, HIGH); // set the LED off

  //  --CODE FOR KEYBOARD--
  if (kpd.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (kpd.key[i].stateChanged) { // if a key is pressed or relased
        switch (kpd.key[i].kstate) { // state
          case 1: // press
            presskey(kpd.key[i].kchar);
            break;
          case 3: // release
            releasekey(kpd.key[i].kchar);
        }
      }
    }
  }

  //  --CODE FOR JOYSTICK--
  switch (joystickMode[layer]) {
    case 0: // joystick
      XAxis = map(analogRead(A2), 0, 1023, joystickMax, 0);
      YAxis = map(analogRead(A3), 0, 1023, 0, joystickMax);
      Joystick.setXAxis(XAxis);
      Joystick.setYAxis(YAxis);
      break;

    case 1: // mouse
      if (mouseCount == mouseRefresh) {
        int x = analogRead(A2);
        int y = analogRead(A3);
        XAxis = map(x, 0, 1023, mouseSens, -mouseSens);
        YAxis = map(y, 0, 1023, -mouseSens, mouseSens);
        Mouse.move(XAxis, YAxis, 0);
        mouseCount = 0;
      }
      mouseCount++;
      break;

    case 2: // WASD
      XAxis = analogRead(A2);
      YAxis = analogRead(A3);
      mapwasd(wasdstate, wasd, wasdAct);
      break;

    case 3: // double binds
      XAxis = analogRead(A2);
      YAxis = analogRead(A3);
      mapwasd(dbstate1, db1, dbAct1);
      mapwasd(dbstate2, db2, dbAct2);

  }
}


void presskey(char k) {
  if ((k) < 1 && (k) > -38) { //gamepad button or mouse
    if ((k) <= -5) // gamepad buttons
      Joystick.pressButton(-k - 5);
    else
      switch (k) {
        case -1: // switch layer
          if (layer == layers - 1) {
            layer = 0;
          }
          else {
            layer++;
          }
          Keyboard.releaseAll();
          kpd.begin(makeKeymap(keys[layer]));
          leds(layer);

          break;
        case LEFT_CLICK:
          Mouse.press();
          break;
        case RIGHT_CLICK:
          Mouse.press(MOUSE_RIGHT);
          break;
        case MIDDLE_CLICK:
          Mouse.press(MOUSE_MIDDLE);
          break;
      }

  }
  else {
    Keyboard.press(k);
  }
}


void releasekey(char k) {
  if ((k) < 1 && (k) > -38) {
    if ((k) <= -5)
      Joystick.releaseButton(-k - 5);
    else
      switch (k) {
        case -2:
          Mouse.release();
          break;
        case -3:
          Mouse.release(MOUSE_RIGHT);
          break;
        case -4:
          Mouse.release(MOUSE_MIDDLE);
          break;
      }
  }
  else
    Keyboard.release(k);
}

void mapwasd(bool* state, char* keys, int act) {
  if ((YAxis >= -act + 511) != state[0]) {
    if (state[0]) {
      Keyboard.press(keys[0]);
    }
    else {
      Keyboard.release(keys[0]);
    }
    state[0] = (YAxis >= -act + 511);
  }

  if ((XAxis - 511 <= act) != state[1]) {
    if (state[1]) {
      Keyboard.press(keys[1]);
    }
    else {
      Keyboard.release(keys[1]);
    }
    state[1] = (XAxis - 511 <= act);
  }

  if ((YAxis - 511 <= act) != state[2]) {
    if (state[2]) {
      Keyboard.press(keys[2]);
    }
    else {
      Keyboard.release(keys[2]);
    }
    state[2] = (YAxis - 511 <= act);
  }

  if ((XAxis >= -act + 511) != state[3]) {
    if (state[3]) {
      Keyboard.press(keys[3]);
    }
    else {
      Keyboard.release(keys[3]);
    }
    state[3] = (XAxis >= -act + 511);
  }
}

void leds(byte layer) {
  analogWrite(LED1, brightness * layerLEDs[layer][0]);
  analogWrite(LED2, brightness * layerLEDs[layer][1]);
  analogWrite(LED3, brightness * layerLEDs[layer][2]);
}
