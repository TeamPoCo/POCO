/** Modification of RF24Mesh_Example_Master.ino by TMRh20 and RF24Mesh_Example_Master_Statics by TMRh20
 * 
 *
 * This example sketch shows how to send data to nodes bassed on their ID.
 *
 * The nodes can change physical or logical position in the network, and reconnect through different
 * routing nodes as required. The master node manages the address assignments for the individual nodes
 * in a manner similar to DHCP.
 *
 **/
 
 
#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"
#include <SPI.h>
 
/***** Configure the chosen CE,CS pins *****/
RF24 radio(7,8);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

struct payload_t {
  unsigned int type;
  unsigned int query;
};

uint32_t ctr=0;

uint8_t nodesID[253] = {0};


void setup() {
  Serial.begin(115200);
 
  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  // Connect to the mesh
  mesh.begin();
 
}
 
uint32_t displayTimer = 0;

uint8_t nextFreeID() {
  uint8_t i = 0;
  while(nodesID[i] == 1){
    i++;
  }
  nodesID[i] = 1;
  return i+1;
}


void loop() {    
 
  // Call mesh.update to keep the network updated
  mesh.update();
 
  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();
 
 
  // Check for incoming data from the sensors
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);
    Serial.println(header.type);
    Serial.print("Got ");
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
    case 'M': 
    {
      uint32_t dat=0;
      network.read(header,&dat,sizeof(dat));
      Serial.print(dat);
      Serial.print(" from RF24Network address 0");
      Serial.println(header.from_node, OCT);
      break;
    }
    case 'N':
    {
      char dat='I';
      network.read(header,&dat,sizeof(dat));
      uint8_t newID = nextFreeID();
      addAction("INFO", "L'équipement de type " + String(dat) + " l'ID attribué est le numéro" + String(newID) + ". Il faut à présent le configurer :)");
      mesh.write(&newID, 'N', sizeof(newID), 255);
      break;
    }
    case 'C':
    {
      String dat="0";
      network.read(header,&dat,sizeof(dat));
      //uint8_t* tabDoor = checkID(dat, header.from_node);
      uint8_t tabDoor[] = {14,57,2};
      addAction("INFO", "Le pass ID " + String(dat) + " a été lu par le lecteur ID " + String(header.from_node));
      mesh.write(&tabDoor, 'C', sizeof(tabDoor), header.from_node);
      break;
    }
    case 'O':
    {
      boolean dat = false;
      network.read(header,&dat,sizeof(dat));
      if (dat)
        addAction("INFO", "La porte ID " + String(header.from_node) + " a été ouverte avec succès");
      else
        addAction("ERROR", "Erreur lors de la tetative d'ouverture de la porte ID " + String(header.from_node));
      break;
    }
    case 'L':
    {
      String dat[] = {"INFO", "Nothing to say"};
      network.read(header,&dat,sizeof(dat));
      addAction(dat[0], dat[1]);
      break;
    }
    default: 
      network.read(header,0,0); 
      Serial.println(header.type);
      break;
    }
  }
 
 
  // Send each node a message every five seconds
  // Send a different message to node 1, containing another counter instead of millis()
  if(millis() - displayTimer > 5000){
    ctr++;
    for (int i = 0; i < mesh.addrListTop; i++) {
      payload_t payload = {millis(),ctr};
      if (mesh.addrList[i].nodeID == 255) {  //Searching for node one from address list
        payload = {ctr%3,ctr};
      }
      RF24NetworkHeader header(mesh.addrList[i].address, OCT); //Constructing a header
      Serial.println( (network.write(header, &payload, sizeof(payload)) == 1 ? "Send OK" : "Send Fail")); //Sending an message
      
    }
    displayTimer = millis();
  }
}

void addAction(String titre, String message){
  Serial.print(titre);
  Serial .print(" - ");
  Serial.println(message);
}

