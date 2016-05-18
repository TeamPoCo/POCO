
/** RF24Mesh_Example.ino by TMRh20
 *
 * This example sketch shows how to manually configure a node via RF24Mesh, and send data to the
 * master node.
 * The nodes will refresh their network address as soon as a single write fails. This allows the
 * nodes to change position in relation to each other and the master node.
 */


#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>
#include "SoftReset.h"
#include <Wire.h>
#include <PN532_I2C.h>
#include "PN532.h"


/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

/**
 * User Configuration: nodeID - A unique identifier for each radio. Allows addressing
 * to change dynamically with physical changes to the mesh.
 *
 * In this example, configuration takes place below, prior to uploading the sketch to the device
 * A unique value from 1-255 must be configured for each node.
 * This will be stored in EEPROM on AVR devices, so remains persistent between further uploads, loss of power, etc.
 *
 **/

PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

#define LED_VERTE 4
#define LED_ROUGE 5

uint8_t validKeys[][7] = {
                          {0x04, 0x42, 0x16, 0x32, 0x99, 0x3B, 0x80},
                          {0x04, 0x8C, 0xBE, 0xD1, 0x8A, 0x02, 0x80},
                          {0x04, 0x1C, 0x4A, 0x32, 0x99, 0x3B, 0x80}
                         };

int keyCount = sizeof validKeys / 7;
uint8_t success;
uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
uint8_t uidLength;// Length of the UID (4 or 7 bytes depending on ISO14443A card type)
uint32_t displayTimer = 0;
uint32_t ledTimer = 0;
uint32_t delayLedTimer = 0;
boolean action = false;
boolean valid = false;
boolean redLedState = HIGH;

void setup() {
  Serial.begin(115200);
  Serial.println("Démarrage d'un module NFC");
  
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  
  digitalWrite(LED_VERTE, LOW);
  digitalWrite(LED_ROUGE, HIGH);
  
  //Connect to the mesh
  mesh.setNodeID(register_board());
  Serial.print(F("NodeID = "));
  Serial.println(mesh.getNodeID());
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin(108, RF24_250KBPS);
  
  nfc.begin();
  nfc.SAMConfig();
  Serial.println("Ready !");
}

void loop() {

  checkTag();
  
  mesh.update();
  meshReceive();
  meshPing();

  redBlink();  
}
