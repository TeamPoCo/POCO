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

void meshReceive() {
  while (network.available()) {
    RF24NetworkHeader header;
    network.peek(header);
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
      case 'O':
      {
        boolean action = false;
        network.read(header,&action,sizeof(action));
        mesh.write(&action, 'O', sizeof(action), 0);
        if(action){
          Serial.println("La porte a été ouverte");
          digitalWrite(LED_VERTE, HIGH);
          digitalWrite(LED_ROUGE, LOW);
        } else {
          Serial.println("La porte a été fermée");
          digitalWrite(LED_VERTE, LOW);
          digitalWrite(LED_ROUGE, HIGH);
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

uint8_t register_board(){
  if(EEPROM.read(100) > 0 &&  EEPROM.read(100) < 255){
    Serial.print(F("read eeprom 100 : "));
    Serial.println(int(EEPROM.read(100)));
    return EEPROM.read(100);
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

