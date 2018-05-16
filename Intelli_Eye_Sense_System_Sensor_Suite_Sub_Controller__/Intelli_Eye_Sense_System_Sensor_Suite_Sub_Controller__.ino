

//Intelli Eye Sense System Sensor Suite Sub Controller 
// Teensy 3.2
/* 
 *  Board ID List
 *  Master - 8
 *  FWRP - 9
 *  FWCP - 10
 *  FWLP - 11
 *  LSSP - 12
 *  BLSP - 13
 *  BCSP - 14
 *  BRSP - 15
 *  RSSP - 16
 */ 
 
#include <Wire.h>
#include <LIDARLite.h>
#include "HC_SR04.h"


int ID = 10; //Device ID: if not set properly system crash. 
//If Device has #9 as i2c address check command table for special commands 

int D = 0;

int USOK = 0;

int LD = 0;
int UD = 0;
int FD = 0;

int FDF = UD - FD;

// Camera Intialize
#define SERIAL Serial1

unsigned long pulseWidth;

#define TRIG_PIN 4
#define ECHO_PIN 5
#define ECHO_INT 0

int RS = 6;

HC_SR04 UsSensor(TRIG_PIN, ECHO_PIN, ECHO_INT);

void setup() {
  
  Serial.begin(115200);
  // Lidar Setup
  pinMode(2, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(2, LOW); // Set trigger LOW for continuous read

  pinMode(3, INPUT); // Set pin 3 as monitor pin
  

 

  //System Check and Communication Setup 
  Wire.begin(ID); //Device ID: if not set properly system crash.
  D = Wire.read();
  if (D == 00000){
    //Ultrasonic Check
     UsSensor.begin();
     UsSensor.start();
     if(UsSensor.isFinished()){
      UD = UsSensor.getRange();
      }
      
   if(UD > 0)
  {
   USOK = 1;
  }
  else {
    USOK = 0;
    }

    //Report Local System Status
    if(USOK == 1)
    {
      
     Wire.beginTransmission(8);
     Wire.write(11111); 
    Wire.endTransmission();
    D = 0;
    Wire.read();
    }
    else{
      Wire.beginTransmission(8);
      Wire.write(00000);
    Wire.endTransmission();
    D = 0;
    Wire.read();
    }
    }

}

void loop() {
  
  //Get Ultrasonic Data
  UsSensor.start();
  if(UsSensor.isFinished()){
  UD = UsSensor.getRange();
  }
  

  //Distance Data Reporting
  Wire.beginTransmission(ID);
  Wire.write(10000 + ID);
  Wire.write(UD);
  Wire.endTransmission();
    
    //Ultrasonic Get Data
     UsSensor.begin();
     UsSensor.start();
     if(UsSensor.isFinished()){
      UD = UsSensor.getRange();
      }
 // Only Enable This for Device ID 10
  if ( Serial1.available()) // Check to see if at least one character is available
  {
    char x = Serial1.read();
    Wire.beginTransmission(10);
    Wire.write(10000 + ID);
    Wire.write(x);
    Wire.endTransmission();
       
  }
}


