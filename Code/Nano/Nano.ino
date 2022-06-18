#include <Wire.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5,4,3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  Wire.begin();
}

byte x = 0;

void loop()
{
  char customKey = customKeypad.getKey();
  
  if (customKey){
      Wire.beginTransmission(4);
      Wire.write(customKey);      
      Wire.endTransmission();  
  }
}
