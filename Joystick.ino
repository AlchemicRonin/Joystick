#include <Joystick.h>

Joystick_ Joystick;

void setup(){
  // Initialize Button Pins
  pinMode(3, INPUT_PULLUP);// SELECT / SHARE
  pinMode(4, INPUT_PULLUP);// START / OPTIONS
  pinMode(5, INPUT_PULLUP);// up
  pinMode(6, INPUT_PULLUP);// left
  pinMode(7, INPUT_PULLUP);// down
  pinMode(8, INPUT_PULLUP);// right
  pinMode(9, INPUT_PULLUP);// 1 / triangle
  pinMode(10, INPUT_PULLUP);// 4 / rectangle
  pinMode(11, INPUT_PULLUP);// 2 / circle
  pinMode(12, INPUT_PULLUP);// 3 / cross
  pinMode(13, INPUT_PULLUP);// R1
  pinMode(14, INPUT_PULLUP);// R2
  pinMode(15, INPUT_PULLUP);// L1
  pinMode(16, INPUT_PULLUP);// L2
  // Initialize Joystick Library
  Joystick.begin();
}

int buttonToPinMap[16] = {
  12,11,10,9,// right button panel
  5,7,6,8,// left button panel
  15,13,16,14,// upper button panel
  3,4,// special button panel
  1,0// joystick button panel
};

int lastButtonState[16] = {
  0,0,0,0,// right button panel
  0,0,0,0,// left button panel
  0,0,0,0,// upper button panel
  0,0,// special button 
  0,0// joystick button panel
};

void loop(){
  // right button panel
  for (int index = 0; index < 4; index++){
    int currentButtonState = !digitalRead(buttonToPinMap[index]);
    if (currentButtonState != lastButtonState[index]){
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  // left button panel
  for (int index = 4; index < 8; index++){
    int currentButtonState = !digitalRead(buttonToPinMap[index]);
    if (currentButtonState != lastButtonState[index]){
      Joystick.setButton(index+8, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  // upper button panel
  for (int index = 8; index < 12; index++){
    int currentButtonState = !digitalRead(buttonToPinMap[index]);
    if (currentButtonState != lastButtonState[index]){
      Joystick.setButton(index-4, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  // special button panel
  for (int index = 12; index < 14; index++){
    int currentButtonState = !digitalRead(buttonToPinMap[index]);
    if (currentButtonState != lastButtonState[index]){
      Joystick.setButton(index-4, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  // joystick button panel
  for (int index = 14; index < 16; index++){
    int currentButtonState = analogRead(buttonToPinMap[index]);
    if (currentButtonState <= 512){
      currentButtonState = 1;
    } else {
      currentButtonState = 0;
    }
    if (currentButtonState != lastButtonState[index]){
      Joystick.setButton(index-4, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  //two joystick panels
  Joystick.setRxAxis(1023-analogRead(2));
  Joystick.setZAxis(1023-analogRead(3));
  Joystick.setYAxis(1023-analogRead(4));
  Joystick.setXAxis(1023-analogRead(5));
}
