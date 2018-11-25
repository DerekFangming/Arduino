
int analogPin = 0;
int fanPin = 11;

void setup() {
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(analogPin);
  float voltage = lightLevel * (5.0 / 1024.0);
  Serial.println(voltage);
  
  /*
   * 34 -> 2.35
   * 30 -> 2.39
   * 27 -> 2.42
   */

  if (voltage < 2.37) {
    digitalWrite(fanPin, LOW); 
    Serial.println("Fan on 1 minutes");
    delay(60000);
  } else {
    digitalWrite(fanPin, HIGH);
    delay(1000);
  }


}
