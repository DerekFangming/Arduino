#include "Servo.h"
#include "SevSeg.h"

//Plugins
SevSeg sevseg;
Servo servo;

//pins
int servoPin = 14;
int servoAngle = 0;
int buttonPin = 19;

//Time remaining
int hours = 0;
int minutes = 0;
int seconds = 0;

//Controls time and toggle the time mark
int previousMillis = 0;
bool timeToggle = false;

//7 seg settings
byte numDigits = 4;
byte digitPins[] = {10, 11, 12, 13};
byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
bool resistorsOnSegments = true; 
bool updateWithDelaysIn = true;
byte hardwareConfig = COMMON_CATHODE; 
bool updateWithDelays = false;
bool leadingZeros = true;
bool disableDecPoint = false;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(buttonPin, INPUT);
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}
int val = 0;

int preVal = 0;
int valCount = 0;
bool topping = true;
void loop() {
  int curVal = analogRead(buttonPin);
  if (topping) {
    if (curVal == 1023){
      if (preVal == 1023) {
        if (valCount < 15) {
          if (++valCount == 15) {
            topping = false;
          }
        }
      } else {
        valCount = 0;
      }
    }
  } else {
    if (curVal < 1023) {
      if (preVal < 1023){
        if (valCount > 0) {
          if (--valCount == 0) {
            topping = true;
            hours ++;
          }
        }
      } else {
        valCount = 15;
      }
    }
  }
  preVal = curVal;
  
  int currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    updateTimeRemaining();
    timeToggle = !timeToggle;
  }

  if (timeToggle){
    sevseg.setNumber(hours * 100 + minutes, 2);
    sevseg.refreshDisplay();
  } else {
    sevseg.setNumber(hours * 100 + minutes, 0);
    sevseg.refreshDisplay();
  }

  if (seconds == 0 && minutes == 0 && hours == 0) {
    servo.write(115);
  } else {
    servo.write(0);
  }
}

void updateTimeRemaining() {
  if (seconds > 0) {
    seconds --;
  } else if (minutes > 0) {
    minutes --;
    seconds = 59;
  } else if (hours > 0) {
    hours --;
    minutes = 59;
    seconds = 59;
  }
}

