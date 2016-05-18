void checkTag(){
  valid = false;
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 25);
  //success = false;
  if(success){
    for (int i=0;i<keyCount && !valid;i++) {
      for (int j=0;j<7 && !valid;j++) {
        if (uid[j] != validKeys[i][j]) {
          break;
        }
        if (j==uidLength-1) {
          valid = true;
        }
      }
    }
    if (valid){
      Serial.println("card ok");
      boolean ouvrir = true;
      while(!mesh.write(&ouvrir, 'O', sizeof(ouvrir), 1)){
            delay(3);
            Serial.println("Echec transmition demande ouverture");
      }
    } else {
      nfc.PrintHex(uid, uidLength);
      delayLedTimer = millis();
    }
  }
}

