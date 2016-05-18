void redBlink(){
  if (millis()-delayLedTimer <= 1000 || redLedState == LOW){
    if (millis() - ledTimer >= 100) {
      ledTimer = millis();
      if (redLedState == LOW) {
        redLedState = HIGH;
      } else {
        redLedState = LOW;
      }
      digitalWrite(LED_ROUGE, redLedState);
    } else {
      redLedState = HIGH;
      digitalWrite(LED_ROUGE, redLedState);
    }
  }
}
