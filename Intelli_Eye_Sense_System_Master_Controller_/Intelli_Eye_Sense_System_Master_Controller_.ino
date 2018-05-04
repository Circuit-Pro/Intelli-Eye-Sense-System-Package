// Intelli Eye Sense System Master Controller
// Revision A. Update! camera switch from Pixy to JeVois
// Teensy 3.5
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
// LOVC PID Values
float Kp=0.1, Ki=0.5, Kd=0;
int output_bits = 8;
bool output_signed = false;

unsigned long previousMillis = 0;      

const long interval = 15; 

const int analogIn = A0;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;

#include <FastPID.h>
#include <PID_v1.h>
#include <Servo.h>
#include <Wire.h>


double Setpoint, Input, Output;
PID BR(&Input, &Output, &Setpoint,2,5,1, DIRECT); // Breaking PID

FastPID SPDC(Kp, Ki, Kd, output_bits, output_signed); //Steering PID

Servo Steering;
Servo Break;
Servo Accelerator;

int SP = 2; // Steering Potentiometer Input
int ERR = 24; // Sensor Error Warning Indicator
int BPER = 25; // Warning Beeper
int SSP = 0; // Speed set point?

int FWRP = 0;
int FWRPVS = 0;
int FWRPVS2 = 0;
int FWCP = 0;
int FWCPVS = 0;
int FWCPVS2 = 0;
int FWLP = 0;
int FWLPVS = 0;
int FWLPVS2 = 0;
int LSSP = 0;
int BLSP = 0;
int BLSP2 = 0;
int BCSP = 0;
int BCSP2 = 0;
int BRSP = 0;
int BRSP2 = 0;
int RSSP = 0;

int IVSR = 0;
int IVSC = 0;
int IVSL = 0;

int D = 0;
int B = 0;

// MATH int
int IPR = 0;
int MPH = 0;
int BC = 0;
 
 volatile byte half_revolutions;
 unsigned int rpm;
 unsigned long timeold;

  
void setup() {
Wire.begin(8);
Serial.begin(115200);
pinMode(ERR, OUTPUT);
pinMode(BPER, OUTPUT);
D = Wire.read();

  // Begin initialization of Sensors and System Check

  Wire.beginTransmission(9);  // transmit to device #2
  Wire.write(00000);          //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if (D == 11119){
    FWRP = 1;
    D = 0;
    }
    else {
      digitalWrite(ERR, HIGH);
      Serial.println("ERROR SENSOR 9 FWRP FAULT!");
      Serial.print(2);
    }
  delay(10);
  
  Wire.beginTransmission(10);  // transmit to device #3
  Wire.write(00000);         //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if (D == 11111){
    FWCP = 1;
    D = 0;
    }
    else {
      digitalWrite(ERR, HIGH);
    Serial.println("ERROR SENSOR FWCP FAULT!");
    Serial.print(3);
    }
    delay(10);
  
  Wire.beginTransmission(11);  // transmit to device #4
  Wire.write(00000);         //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if(D == 11111){
    FWLP = 1;
    D = 0;
    }
    else {
      digitalWrite(ERR, HIGH);
    Serial.println("ERROR SENSOR FWLP FAULT!");
    Serial.print(4);
    } 
  delay(10);
  
  Wire.beginTransmission(12);  // transmit to device #5
  Wire.write(00000);         //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if(D == 11111){
    LSSP = 1;
    D = 0;
    }
     else {
      digitalWrite(ERR, HIGH);
    Serial.println("ERROR SENSOR LSSP FAULT!");
    Serial.print(5);
    }
  delay(10);
  
  Wire.beginTransmission(13);  // transmit to device #6
  Wire.write(00000);         //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if(D == 11111){
    BLSP = 1;
    }
 else {
      digitalWrite(ERR, HIGH);
    Serial.println("ERROR SENSOR BLSP FAULT!");
    Serial.print(6);
    }  delay(10);
  
  Wire.beginTransmission(14);  // transmit to device #7
  Wire.write(00000);         //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if(D == 11111){
    BCSP = 1;
    D = 0;
    }
 else {
      digitalWrite(ERR, HIGH);
    Serial.println("ERROR SENSOR BCSP FAULT!");
    Serial.print(7);
    }  delay(10);
  
  Wire.beginTransmission(15);  // transmit to device #8
  Wire.write(00000);         //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if(D == 11111){
    BRSP = 1;
    D = 0;
    }
 else {
      digitalWrite(ERR, HIGH);
    Serial.println("ERROR SENSOR BRSP FAULT!");
    Serial.print(8);
    }  delay(10);
  
  Wire.beginTransmission(16);  // transmit to device #9
  Wire.write(00000);         //Sends startup request and check
  Wire.endTransmission();     // stop transmitting
  Wire.read();
  if(D == 11111){
    RSSP = 1;
    D = 0;
    }
 else {
      digitalWrite(ERR, HIGH);
    Serial.println("ERROR SENSOR RSSP FAULT!");
    Serial.print(9);
    }    
  delay(10);
STSC();

attachInterrupt(0, rpm_fun, RISING);
   half_revolutions = 0;
   rpm = 0;
   timeold = 0;

// Breaking PID

Input = MPH;
  Setpoint = IVSC;
  //turn the PID on
  BR.SetMode(AUTOMATIC);
}


byte TSP = 0; // Targeted Steering Position from F.C.S.P
byte ASP = 0; // Actual Sterring Position



void loop() {
  //MATH
  IPR = (84.823 * rpm);
  MPH = (IPR * 60);
  BC = (IVSC - MPH);
  
  D = Wire.read();
   ASP = analogRead(SP);
   
   if (half_revolutions >= 20) { 
     //Update RPM every 20 counts, increase this for better RPM resolution,
     //decrease for faster update
     rpm = 30*1000/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
     Serial.println(rpm,DEC);  
   }
   //Fusion Data Storage
   Wire.read();
  if(D == 10009){
    D = 0;
    Wire.read();
    D = FWRP;
    }
    
    if(D == 10010){
    D = 0;
    Wire.read();
    D = FWCP;
    }
    
    if(D == 10011){
    D = 0;
    Wire.read();
    D = FWLP;
    }
    
    if(D == 10012){
    D = 0;
    Wire.read();
    D = LSSP;
    }
    
    if(D == 10013){
    D = 0;
    Wire.read();
    D = BLSP;
    }
    
    if(D == 10014){
    D = 0;
    Wire.read();
    D = BCSP;
    }
    
    if(D == 10015){
    D = 0;
    Wire.read();
    D = BRSP;
    }

    if(D == 10016){
    D = 0;
    Wire.read();
    D = RSSP;
    }

    //Degraded Fusion Data
    
  Wire.read();
  if(D == 11119){
    Wire.read();
    D = FWRP;
    }
    D = 0;
    if(D == 00110){
    Wire.read();
    D = FWCP;
    }
    D = 0;
    
    if(D == 00111){
    Wire.read();
    D = FWLP;
    }
    D = 0;
    
    if(D == 00112){
    Wire.read();
    D = LSSP;
    }
    D = 0;
    
    if(D == 00113){
    Wire.read();
    D = BLSP;
    }
    D = 0;
    
    if(D == 00114){
    Wire.read();
    D = BCSP;
    }
    D = 0;
    
    if(D == 00115){
    Wire.read();
    D = BRSP;
    }
    D = 0;
    
    if(D == 00116){
    Wire.read();
    D = RSSP;
    }
    D = 0;
    CWS();
    CPS();
    SMO();
}



 






