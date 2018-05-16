void STSC(){ // Steering System Initialization
  Steering.attach(3);
  TSP = 180;
  Steering.write(TSP);
  delay(800);
  if (TSP =! ASP){ TSP_ERR();}
  TSP = 160;
  Steering.write(TSP);
  delay(800);
  if (TSP =! ASP) {TSP_ERR();}
  TSP = 200;
  Steering.write(TSP);
  delay(800);
  if (TSP =! ASP) {TSP_ERR();}
  TSP = 180;
  Steering.write(TSP); 
  }
