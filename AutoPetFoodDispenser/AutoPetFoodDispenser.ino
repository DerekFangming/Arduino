#include "Servo.h"
#include "SevSeg.h"
SevSeg sevseg; 

int servoPin = 14;
Servo servo;
int servoAngle = 0;

int buttonPin = 19;


void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);

  pinMode(buttonPin, INPUT);

  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  bool updateWithDelays = false;
  bool leadingZeros = true;
  bool disableDecPoint = false;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}
int cur = 0;
bool a = false;
int minutes = 20;
int val = 0;

int preVal = 0;
int valCount = 0;
bool topping = true;
void loop() {
  int curVal = analogRead(buttonPin);
  if (topping) {
    if (curVal == 1023){
      if (preVal == 1023) {
        if (valCount < 5) {
          if (++valCount == 5) {
            topping = false;
          }
        }
      } else {
        valCount = 1;
      }
    }
  } else {
    if (curVal < 1023) {
      if (preVal < 1023){
        if (valCount > 0) {
          if (--valCount == 0) {
            topping = true;
            minutes ++;
          }
        }
      } else {
        valCount = 5;
      }
    }
  }

  preVal = curVal;
  Serial.println(valCount);
//  val = digitalRead(buttonPin);
//
//  int val1 = analogRead(buttonPin);
//  
//  Serial.println(val1);
//  if (val == HIGH) {         // check if the input is HIGH (button released)
//    minutes ++;
//  }
  
  int millies = millis();
  if (millies - cur >= 1000) {
    cur = millies;
    a = !a;
  }

  if (a){
    sevseg.setNumber(8888);
    sevseg.refreshDisplay();
  } else {
    sevseg.setNumber(600 + minutes, 0);
    sevseg.refreshDisplay();
  }

//servo.write(0);
//delay(2000);
//servo.write(115);
//delay(2000);
//  servo.write(0);      // Turn SG90 servo Left to 45 degrees
//  delay(2000);          // Wait 1 second
//  servo.write(90);      // Turn SG90 servo back to 90 degrees (center position)
//  delay(2000);          // Wait 1 second
//  servo.write(180);     // Turn SG90 servo Right to 135 degrees
//  delay(2000);          // Wait 1 second
//  servo.write(90);      // Turn SG90 servo back to 90 degrees (center position)
//  delay(2000);
}
