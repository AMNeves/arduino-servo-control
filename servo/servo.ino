/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo myservo;
Servo myservo2;// create servo object to control a servo
// twelve servo objects can be created on most boards
int x = 90, y = 90, prevX = 90, prevY = 90;
boolean newData = false;

char inData[5]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  myservo.attach(9);
  myservo2.attach(8);

  myservo.write(160);
  myservo2.write(160);
  delay(1000);
  myservo.write(0);
  myservo2.write(0);
  delay(1000);
  
  myservo.write(x);
  myservo2.write(y);
  delay(1000);
  lcd.print("Servo 1: 90");
  lcd.setCursor(0 , 1);
  lcd.print("Servo 2: 90");
}
void loop() {
    if (Serial.available() > 0) {
        if (Serial.read() == 'a') {
            x = Serial.parseInt();
            if (Serial.read() == 'b') {
                y = Serial.parseInt();
                moveTurret();
            }
        }
    
        while (Serial.available() > 0) {
            Serial.read();
        }        
    }
  lcd.setCursor(9, 0);
  lcd.print("   ");
  lcd.setCursor(9, 0);
  lcd.print(x);

  lcd.setCursor(9, 1);
  lcd.print("   ");
  lcd.setCursor(9, 1);
  lcd.print(y);
}

void moveTurret() {
    if (prevX != x || prevY != y) {
        prevX = x;
        prevY = y;

        int servoX = map(x, 0, 600, 40, 130);
        int servoY = map(y, 0, 450, 160, 80);
        
        servoX = min(servoX, 130);
        servoX = max(servoX, 40);
        servoY = min(servoY, 160);
        servoY = max(servoY, 80);
        
        myservo.write(x);
        myservo2.write(y);
        
        delay(20);
    }
}
