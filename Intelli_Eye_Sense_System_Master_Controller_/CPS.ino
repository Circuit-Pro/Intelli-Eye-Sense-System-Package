void CPS()
{
    unsigned long currentMillis = millis();
  // Int Speed Calculations
  if(FWRP <= 400){
    FWRP = FWRPVS;
     if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
     unsigned long currentMillis = millis();
    FWRP = FWRPVS2;
     }
    }
     if(FWCP <= 400){
  FWCP = FWCPVS;
     if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
     unsigned long currentMillis = millis();
    FWCP = FWCPVS2;
    }
    }
     if(FWLP <= 400){
    FWLP = FWLPVS;
     if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
     unsigned long currentMillis = millis();
    FWLP = FWLPVS2;
    }
  }
  // Speed Processing
    IVSR = (FWRPVS - FWRPVS2) / (15 * 10);
    IVSC = (FWCPVS - FWCPVS2) / (15 * 10);
    IVSL = (FWLPVS - FWLPVS2) / (15 * 10);
    
    // Prevention System
    if(IVSR >= 2.23){
      B = BC;
      }
      if(IVSC >= 2.23){
      B = BC;
      }
      if(IVSL >= 2.23){
      B = BC;
      }
      

    
}
