#include <Arduino.h>
#include <Servo.h>
#include <main.h>
#include <HX711.h>
#include <stdio.h>
//#include <nettside.h>
/*
MAPPING:
  
  Sensor 1    Grønn   IO32
  Sensor 1    Hvit    IO33
  
  Sensor 2    Hvit    IO25
  Sensor 2    Grønn   IO26
  
  
  Servo 1     

*/
HX711 loadcell1;
HX711 loadcell2;
int tolerance = 80;
int unchanged = 0;

#define servoPin 8
Servo servo;

bool servoOn = true;

int pressurePins [2];

int pressureMeasurements [2];

void setup() {
  
  Serial.begin(9600);
  
  servo.attach(servoPin);
  //nettside_init();
  loadcell1.begin(3, 2);
  loadcell1.set_scale(5895655);
  loadcell1.set_offset(0);
  loadcell2.begin(5,6);
  loadcell2.set_scale(5895655);
  loadcell2.set_offset(0);
  
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
  
  if(servoOn){
    for (int i = 0; i < 45; i++)
    {
      adjustAngle(i);
      delay(20);
    }
    
    
    delay(100);

    for (int i = 0; i < 45; i++)
    {
      adjustAngle(45-i);
      delay(20);
    }
    delay(100);
  }

  if(Serial.available()){
    char byte = Serial.read();
    Serial.println(byte);
    while(Serial.available()){
      Serial.read();
    }

    if(byte == '1'){
      servoOn = true;
    }else{
      servoOn = false;
      adjustAngle(45);
    }

  }
  
  
  {
  //char loadcellValues[100];
  //sprintf(loadcellValues, "{loadcell_1:%d,loadcell_2:%d}",loadcell1.get_value(),loadcell2.get_value());
  Serial.print("{\"loadcell_1\":");
  Serial.print(loadcell1.get_value(5),1);
  Serial.print(",\"loadcell_2\":");
  Serial.print(loadcell2.get_value(5),1);
  Serial.println("}");
  //Serial.println(loadcell1.get_value(5));
  }

}

int getPressure(){
  return 20;
}

