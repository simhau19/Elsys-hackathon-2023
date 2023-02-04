#include <Arduino.h>

/*
MAPPING:
  
  Sensor 1    Grønn   IO32
  Sensor 1    Hvit    IO33
  
  Sensor 2    Hvit    IO25
  Sensor 2    Grønn   IO26
  
  
  Servo 1     

*/

int tolerance = 80;
int unchanged = 0

int servoPins [2];
Servo servos [2];

int pressurePins [2];

int pressureMeasurements [2];

void setup() {
  
  Serial.begin(9600);
  
  for (int index = 0; index < 2; index++) {
    servos[index].attach(servoPins[index]);
  }
  
  adjustAngle(80);
  
}

void adjustAngle(int newAngle) {
  
  Serial.println("Adjusting to " + newAngle + " °.");
  
  // adjust to set correct angle
  
  servos[0].write(newAngle);
  servos[1].write(newAngle + 20);
  
}

bool pressureChanged() {
  
  int currentA = pressureMeasurements[0];
  int currentB = pressureMeasurements[1];
  
  int newA = analogRead(pressurePins[0]);
  int newB = analogRead(pressurePins[1]);
  
  int changeA = (newA - currentA) * (newA - currentA)
  int changeB = (newB - currentB) * (newB - currentB)
  
  if (changeA + changeB < tolerance) {
    unchanged++;
  } else {
    unchanged = 0;
  }
  
  pressureMeasurements[0] = newA;
  pressureMeasurements[1] = newB;
  
}

int counter = 0;

void loop() {
  
  adjustAngle(80 + counter);
  counter++;
  
  Serial.println("Hello world! LOL");
  delay(1000);
  
}
