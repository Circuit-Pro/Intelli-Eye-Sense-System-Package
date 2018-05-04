

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
int LTOK = 0;
int USOK = 0;
int LD = 0;
int UD = 0;
int FD = 0;

int FDF = UD - FD;


unsigned long pulseWidth;

#define TRIG_PIN 4
#define ECHO_PIN 5
#define ECHO_INT 0

HC_SR04 UsSensor(TRIG_PIN, ECHO_PIN, ECHO_INT);

void setup() {
  
  Serial.begin(115200);
  // Lidar Setup
  pinMode(2, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(2, LOW); // Set trigger LOW for continuous read

  pinMode(3, INPUT); // Set pin 3 as monitor pin
  //Ultrasonic Setup

  //System Check and Communication Setup 
  Wire.begin(ID); //Device ID: if not set properly system crash.
  D = Wire.read();
  if (D == 00000){
    //Lidar Check
    pulseWidth = pulseIn(3, HIGH); //LIDAR: Count how long the pulse is high in microseconds
   if(pulseWidth > 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance
   LTOK = 1;
  }
  else {
    LTOK = 0;
    }
    
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
    if(USOK & LTOK == 1)
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
  //Get Lidar Data
  pulseWidth = pulseIn(3, HIGH); //LIDAR: Count how long the pulse is high in microseconds
  
  if(pulseWidth != 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance  
  }
  //Get Ultrasonic Data
  UsSensor.start();
  if(UsSensor.isFinished()){
  UD = UsSensor.getRange();
  }
  
  // Sensor Fusion Trust Calculation
  if (FDF < 10 && FDF > -10)
{
  // Sensor Fusion
  FD = UD + LD;
  //Fused Distance Data Reporting
  Wire.beginTransmission(8);
  Wire.write(10000 + ID);
  Wire.write(FD);
  Wire.endTransmission();
}
else{
//If Fused Data Not Availible
//Lidar Check
    pulseWidth = pulseIn(3, HIGH); //LIDAR: Count how long the pulse is high in microseconds
   if(pulseWidth > 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance
   LTOK = 1;
  }
  else {
    LTOK = 0;
    }
    
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

    //
    if(USOK & LTOK == 1)
    {
  // Sensor Fusion
  FD = UD + LD;
  //Fused Distance Data Reporting
  Wire.beginTransmission(8);
  Wire.write(10000 + ID);
  Wire.write(FD);
  Wire.endTransmission();
    }
      if (FDF < 20 && FDF > -20) {
        // Sensor Fusion
        FD = UD + LD;
        //Send Degraded Data
        Wire.beginTransmission(8);
        Wire.write(00110 + ID);
        Wire.write(FD);
        Wire.endTransmission();
      }
   }
}

