#include <Arduino.h>
#include <Servo.h>
#include <main.h>
//#include <nettside.h>
/*
MAPPING:
  
  Sensor 1    Grønn   IO32
  Sensor 1    Hvit    IO33
  
  Sensor 2    Hvit    IO25
  Sensor 2    Grønn   IO26
  
  
  Servo 1     

*/

int tolerance = 80;
int unchanged = 0;

#define servoPin 8
Servo servo;

int pressurePins [2];

int pressureMeasurements [2];

void setup() {
  
  Serial.begin(9600);
  
  servo.attach(servoPin);
  //nettside_init();
  
}

void adjustAngle(int newAngle) {
  
  /*
  Serial.print("\nAdjusting to ");
  Serial.print(newAngle);
  Serial.print(" °.");
  */
  
  // adjust to set correct angle
  
  servo.write(newAngle);
  
}

bool pressureChanged() {
  
  int currentA = pressureMeasurements[0];
  int currentB = pressureMeasurements[1];
  
  int newA = analogRead(pressurePins[0]);
  int newB = analogRead(pressurePins[1]);
  
  int changeA = (newA - currentA) * (newA - currentA);
  int changeB = (newB - currentB) * (newB - currentB);
  
  if (changeA + changeB < tolerance) {
    unchanged++;
  } else {
    unchanged = 0;
  }
  
  pressureMeasurements[0] = newA;
  pressureMeasurements[1] = newB;
  return true;
}

void loop() {
  
  for (int i = 0; i < 45; i++)
  {
    adjustAngle(i);
    delay(20);
  }
  
  
  delay(1000);

  for (int i = 0; i < 45; i++)
  {
    adjustAngle(45-i);
    delay(20);
  }
  delay(1000);
  Serial.println("Hei");
  
  
}

int getPressure(){
  return 20;
}
