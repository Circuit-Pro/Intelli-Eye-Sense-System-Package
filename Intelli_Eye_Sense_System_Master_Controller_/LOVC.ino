void LOVC(){ // Longitudinal Vehicle Control I.E. Acceleration and Breaking
  Break.attach(6);
  Accelerator.attach(7);
  
  int setpoint = SSP / 2; 
  int feedback = half_revolutions;
  uint8_t output = SPDC.step(setpoint, feedback);
  Accelerator.write(output);
  Break.write(B);

 Input = half_revolutions;
  BR.Compute();
  B = Output;
  }
