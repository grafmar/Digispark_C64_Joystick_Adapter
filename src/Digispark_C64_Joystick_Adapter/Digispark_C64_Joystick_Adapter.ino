//DigiJoystickC64 test and usage documentation

#include "DigiJoystickC64.h"

void setup() {
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(5,INPUT);
}

void loop() {
  uint8_t inputValue = 0U;
  for (uint8_t i = 0; i < 8U; i++) {
    inputValue >>= 1;
    digitalWrite(0,(i&0x01)!=0?HIGH:LOW);
    digitalWrite(1,(i&0x02)!=0?HIGH:LOW);
    digitalWrite(2,(i&0x04)!=0?HIGH:LOW);
    DigiJoystick.delay(1); // wait 1 milliseconds
    inputValue |= (digitalRead(5) == LOW) ? 128U : 0U;
  }

  // Set buttons from lower nibble: fire1, fire2, extra button 1, extra button 2
//  DigiJoystick.setButtons((byte)(inputValue & 0x0FU));
  DigiJoystick.setButtons((byte)(inputValue>>4));
  
  if (inputValue & 0x01) {
    DigiJoystick.setY((byte) 0x00); // up
  } else if (inputValue & 0x02) {
    DigiJoystick.setY((byte) 0xFF); // down
  } else {
    DigiJoystick.setY((byte) 0x7F); // center
  }
  
  if (inputValue & 0x04) {
    DigiJoystick.setX((byte) 0x00); // left
  } else if (inputValue & 0x08) {
    DigiJoystick.setX((byte) 0xFF);  // right
  } else {
    DigiJoystick.setX((byte) 0x7F); // center
  }

}
