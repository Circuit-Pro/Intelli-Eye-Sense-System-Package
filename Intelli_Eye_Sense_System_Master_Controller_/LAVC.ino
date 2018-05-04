void LAVC(){ // Lateral Vehicle Control
  Wire.read();
  if(D == 00001)
  Steering.attach(3);
  Steering.write(TSP);
  
  }
