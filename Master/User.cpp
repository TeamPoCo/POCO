// User Class - By Clément BEGNAUD

#include <string.h>
#include <SPI.h>
//#include <iostream.h>
#include "User.h"

using namespace std;

// CONSTRUCTEURS

/*
* Constructeur par défaut
*
*
*/
User::User(String nom, String prenom, String cardID){
	this->setNom(nom);
	this->setPrenom(prenom);
	this->setCardID((uint8_t)cardID.toInt());
}


// ACCESSEURS

void User::setNom(String nom){
	this->_nom = nom;
}
	
	
String User::getNom(){
	return this->_nom;
}
	
	
void User::setPrenom(String prenom){
	this->_prenom = prenom;
}


String User::getPrenom(){
	return this->_prenom;
}
	
	
void User::setCardID(uint8_t cardID){
	this->_cardID = cardID;
}
	
	
uint8_t User::getCardID(){
	return this->_cardID;
}
