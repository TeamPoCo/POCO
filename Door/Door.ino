#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>
//#include <Servo.h>
#include "SoftReset.h"


/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

//Servo servoPorte;

#define LED_VERTE 4
#define BOUTON 2
#define LOQUET 9
#define SERVO 9

/**
 * User Configuration: nodeID - A unique identifier for each radio. Allows addressing
 * to change dynamically with physical changes to the mesh.
 *
 * In this example, configuration takes place below, prior to uploading the sketch to the device
 * A unique value from 1-255 must be configured for each node.
 * This will be stored in EEPROM on AVR devices, so remains persistent between further uploads, loss of power, etc.
 *
 **/


uint32_t displayTimer = 0;
uint32_t doorTimer = 0;
const int delay_fail = 3;
boolean ouvert = false;
boolean saveSettings(uint8_t timeOpen, uint8_t valMax, uint8_t valMin);

void setup() {
  Serial.begin(115200);
  Serial.println("Démarrage d'un module Door");
  
  pinMode(LOQUET, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(BOUTON, INPUT);;

  digitalWrite(LOQUET, LOW);
  digitalWrite(LED_VERTE, LOW);

  //servoPorte.attach(SERVO);
  //servoPorte.write(0);
  
  // Connect to the mesh
  mesh.setNodeID(registerNetwork());
  Serial.print(F("NodeID = "));
  Serial.println(mesh.getNodeID());
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin(108, RF24_250KBPS);

  Serial.println("Ready !"); 
}

void loop() {
  mesh.update();

  meshPing();
  meshReceive();
  
  if (millis() - doorTimer >= 3000 && ouvert) {
    digitalWrite(LOQUET, LOW);
    digitalWrite(LED_VERTE, LOW);
    ouvert = false;
    while(!mesh.write(&ouvert, 'O', sizeof(ouvert), 2)){
            delay(delay_fail);
            Serial.println("Echec transmition fermeture auto");
    }
    //servoPorte.write(0);
  }

  checkButton();
}

boolean saveSettings(uint8_t timeOpen, uint8_t valMax, uint8_t valMin){
  EEPROM.write(110,valMin);
  EEPROM.write(120,valMax);
  EEPROM.write(130,timeOpen);
  return true;
}





