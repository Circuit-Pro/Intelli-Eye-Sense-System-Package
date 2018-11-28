void CWS(){ // Collision Warning System
  // High Speed Forward Collision Warning
  
  //Low Speed Collision Warning
  if(FWRP <= 45.72){
    digitalWrite(ERR, HIGH);
    digitalWrite(BPER, HIGH);
    }
     if(FWCP <= 45.72){
    digitalWrite(ERR, HIGH);
  digitalWrite(BPER, HIGH);
    }
     if(FWLP <= 45.72){
    digitalWrite(ERR, HIGH);
    digitalWrite(BPER, HIGH);
    } 
    if(LSSP <= 45.72){
    digitalWrite(ERR, HIGH);
  digitalWrite(BPER, HIGH);
    } 
    if(BLSP <= 45.72){
    digitalWrite(ERR, HIGH);
    digitalWrite(BPER, HIGH);
    }
    if(BCSP <= 45.72){
    digitalWrite(ERR, HIGH);
    digitalWrite(BPER, HIGH);
    }
    if(BRSP <= 45.72){
    digitalWrite(ERR, HIGH);
    digitalWrite(BPER, HIGH);
    }
    if(RSSP <= 45.72){
    digitalWrite(ERR, HIGH);
    digitalWrite(BPER, HIGH);
    }
    digitalWrite(ERR, LOW);
    digitalWrite(BPER, LOW);
}
