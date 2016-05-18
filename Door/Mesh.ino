void meshReceive(){
  while (network.available()) {
    RF24NetworkHeader header;
    network.peek(header);
    switch(header.type){
      case 'S':
      {
        struct settings_t {
          uint8_t valMin;
          uint8_t valMax;
          uint8_t timeOpen;
        };
        settings_t settings;
        boolean answer = false;
        network.read(header,&settings,sizeof(settings));
        answer = saveSettings(settings.timeOpen, settings.valMax, settings.valMin);
        mesh.write(&answer, 'S', sizeof(answer), header.from_node);
        break;
      }
      case 'O':
      {
        boolean action = false;
        network.read(header,&action,sizeof(action));
        if(action){
          //openDoor();
          //servoPorte.write(90);
          digitalWrite(LOQUET, HIGH);
          digitalWrite(LED_VERTE, HIGH);
          ouvert = true;
          while(!mesh.write(&ouvert, 'O', sizeof(ouvert), mesh.getNodeID(header.from_node))){
            delay(delay_fail);
            Serial.println("Echec transmition ouverture telecommande");
          }
          doorTimer = millis();
        } else {
          //closeDoor();
          //servoPorte.write(0);
          digitalWrite(LOQUET, LOW);
          digitalWrite(LED_VERTE, LOW);
          ouvert = false;
          while(!mesh.write(&ouvert, 'O', sizeof(ouvert), mesh.getNodeID(header.from_node))){
            delay(delay_fail);
            Serial.println("Echec transmition fermeture telecommande");
          }
        }
        break;
      }
      default: 
        network.read(header,0,0); 
        Serial.println(header.type);
        break;
    }
  }
}

uint8_t registerNetwork(){
  if(EEPROM.read(100) > 0 &&  EEPROM.read(100) < 255){
    Serial.print(F("read eeprom 100 : "));
    Serial.println(uint8_t(EEPROM.read(100)));
    return uint8_t(EEPROM.read(100));
  }
  else {
    mesh.setNodeID(255);
    Serial.println(F("ID 255"));
    delay(50);
    Serial.println(F("Connecting to the mesh..."));
    mesh.begin();
    boolean active = true;
    mesh.write(&displayTimer, 'N', sizeof(displayTimer));
    uint8_t myID = 255;
    while(active){
      mesh.update();
      while (network.available()) {
        RF24NetworkHeader header;
        network.read(header, &myID, sizeof(myID));
        Serial.print("New ID : ");
        Serial.println(myID);
        active = false;
      }
    }
    delay(500);
    EEPROM.write(100,myID);
    Serial.print(F("Let's reset"));
    soft_restart();
  }
}

void meshPing() {
  // Send to the master node every second
  if (millis() - displayTimer >= 5000) {
    displayTimer = millis();

    // Send an 'M' type message containing the current millis()
    if (!mesh.write(&displayTimer, 'M', sizeof(displayTimer))) {

      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
      }
    } else {
      Serial.print("Send OK: "); Serial.println(displayTimer);
    }
  }
}
