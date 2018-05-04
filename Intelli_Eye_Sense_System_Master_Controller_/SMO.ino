
void SMO(){ //Manual Wheel Overide
  RawValue = analogRead(analogIn);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
 if(Amps >= 25){
  MANUAL_TSP();
  }
  }
