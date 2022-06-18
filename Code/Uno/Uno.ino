#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String rcode = "";
const String code = "2509";

void setup()
{
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  
  Wire.begin(4);               
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);        
  lcd.begin(16, 2);
  lcd.print("Vnesi kodo:");
}

void loop()
{
  delay(100);
}

void receiveEvent(int howMany)
{
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  while(0 < Wire.available()) 
  {
    char c = Wire.read();
    //Serial.print(c);
    if(c == '*' || rcode.length() > 6){
      if(rcode == code){
        unlock();
      }
      else{
        deny();
      }
    }
    else{
      rcode = rcode + c;
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(rcode);
    }
  }

}

void unlock(){
  lcd.setCursor(0,1);
  lcd.print("Dobrodosel!");
  rcode = "";
  digitalWrite(7, HIGH);
}

void deny(){
  lcd.setCursor(0,1);
  lcd.print("Neveljavna koda!");
  rcode = "";
  digitalWrite(6, HIGH);
}
