void COMS(){
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

    // US SENSOR DATA LD Not avalible
    Wire.read();
  if(D == 11119){
    Wire.read();
    D = FWRP;
    }
    D = 0;
    if(D == 10110){
    Wire.read();
    D = FWCP;
    }
    D = 0;
    
    if(D == 10111){
    Wire.read();
    D = FWLP;
    }
    D = 0;
    
    if(D == 10112){
    Wire.read();
    D = LSSP;
    }
    D = 0;
    
    if(D == 10113){
    Wire.read();
    D = BLSP;
    }
    D = 0;
    
    if(D == 10114){
    Wire.read();
    D = BCSP;
    }
    D = 0;
    
    if(D == 10115){
    Wire.read();
    D = BRSP;
    }
    D = 0;
    
    if(D == 10116){
    Wire.read();
    D = RSSP;
    }
    D = 0;
   
  }
