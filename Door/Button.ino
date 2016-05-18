void checkButton(){
  if(digitalRead(BOUTON)){
    digitalWrite(LOQUET, HIGH);
    digitalWrite(LED_VERTE, HIGH);
    ouvert = true;
    while(!mesh.write(&ouvert, 'O', sizeof(ouvert), 2)){
            delay(delay_fail);
            Serial.println("Echec transmition ouverture button");
    }
    doorTimer = millis();
  }
}

