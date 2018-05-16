void COMS(){
   //Sensor Data Storage
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

    // Lane Centering Data
    if(D == 11010){
    D = 0;
    Wire.read();
    D = TSP;
    }
  }
