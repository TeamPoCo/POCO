// SysSD Class - By Clément BEGNAUD

#include <string.h>
#include <Stream.h>
//#include <iostream>
#include <SPI.h>
#include <SD.h>

#include "SysSD.h"

using namespace std;

const int SD_chipSelect = 4;

//Constructeur par défaut
SysSD::SysSD(){
	//Détection de la carte SD
	if (!SD.begin(SD_chipSelect)) {
		//------  COMMENT INDIQUER L'ERREUR DANS CE CAS?   ------
		//------   COMMENT VERIFIER L'ESPACE DISPONIBLE SUR LA CARTE?   ------
		return;
	} else {
		//Détection des logs et création des logs manquants le cas échéant
		// et Avertir que des logs manquaient
		//Log "errors.txt"
		if (SD.exists("errors.txt")) {
			File errors = SD.open("errors.txt", FILE_WRITE);
			errors.close();
			this->addWarning(Warning::logDoesNotExist("errors.txt"));
		}
		//Log "nodes.txt"
		if (!SD.exists("nodes.txt")) {
			this->createLog_Nodes();
			this->addWarning(Warning::logDoesNotExist("nodes.txt"));
		}
		//Log "users.txt"
		if (!SD.exists("users.txt")) {
			this->createLog_Users();
			this->addWarning(Warning::logDoesNotExist("users.txt"));
		}
		//Log "admins.txt"
		if (!SD.exists("admins.txt")) {
			this->createLog_Admins();
			this->addWarning(Warning::logDoesNotExist("admins.txt"));
		}
		//Log "settings.txt"
		if (!SD.exists("settings.txt")) {
			this->createLog_Settings();
			this->addWarning(Warning::logDoesNotExist("settings.txt"));
		}
		//Log "actions.txt"
		if (!SD.exists("actions.txt")) {
			this->createLog_Actions();
			this->addWarning(Warning::logDoesNotExist("actions.txt"));
		}
	}
}

/**
*	Crée le log "nodes.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Nodes(){
	bool cree = false;
	File nodes = SD.open("nodes.txt", FILE_WRITE);
	if(nodes) {
		bool cree = true;
		nodes.close();
	}
	return cree;
}

/**
*	Crée le log "users.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Users(){
	bool cree = false;
	File users = SD.open("users.txt", FILE_WRITE);
	if(users) {
	  bool cree = true;
	  users.close();
	}
	return cree;
}

/**
*	Crée le log "admins.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Admins(){
	bool cree = false;
	File admins = SD.open("admins.txt", FILE_WRITE);
	if(admins) {
	  bool cree = true;
	  admins.close();
	}
	return cree;
}

/**
*	Crée le log "settings.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Settings(){
	bool cree = false;
	File settings = SD.open("settings.txt", FILE_WRITE);
	if(settings) {
	  bool cree = true;
	  settings.close();
	}
	return cree;
}

/**
*	Crée le log "actions.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Actions(){
	bool cree = false;
	File actions = SD.open("actions.txt", FILE_WRITE);
	if(actions) {
	  bool cree = true;
	  actions.close();
	}
	return cree;
}

/**
*	Crée le log "errors.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Errors(){
	bool cree = false;
	File errors = SD.open("errors.txt", FILE_WRITE);
	if(errors) {
	  bool cree = true;
	  errors.close();
	}
	return cree;
}

/**
*	Ajoute une action au log "action.txt".
*	
*	COMMENT GERER LA DATE?
*/
bool SysSD::addAction(String titre, String message){
	File actions = SD.open("actions.txt", FILE_WRITE);
	if(actions){
		String action = /*formatDate() + */ this->glandouillHeure();
		action+=" [" + titre + "] " + message;
		actions.println(action);
	} else {
		this->addError(Error::cannotOpen("action.txt"));
	}
	actions.close();
}

/**
*	Ajoute un utilisateur au log "users.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::addPeople(String nom, String prenom, String cardID){
	File users = SD.open("users.txt", FILE_WRITE);
	if(users){
		String userStr = "" + nom + " " + prenom + " " + cardID;
		users.println(userStr);
	} else {
		this->addError(Error::cannotOpen("action.txt"));
	}
	users.close();
}


/**
* Cherche l'utilisateur correspondant à cardID, et change son Nom et son Prénom
*
* À COMPLETER
*/
bool SysSD::editPeople(String nom, String prenom, String cardID){
	uint8_t line;
	bool found = this->findUserCardID(cardID, &line);
  if (found){
    String currentUser[3];
    this->findUserCardID(cardID, &line, currentUser);
    this->removePeople(currentUser[0], currentUser[0], currentUser[0]);
    this->addPeople(nom, prenom, cardID);
	}
 return found;
}

bool SysSD::removePeople(String nom, String prenom, String cardID){
	uint8_t line;
  bool found = this->findUserCardID(cardID, &line);
  if (found){
    File users = SD.open("users.txt", FILE_WRITE);
  }
	return false;
}

bool SysSD::addNode(String titre, uint8_t nodesID, String type, uint8_t settings[]){
	File nodes = SD.open("nodes.txt", FILE_WRITE);
	if(nodes){
		String door = ""; //+ titre + " " + nodesID + " " + type + " " + settings;
		nodes.println(door);
    nodes.close();
	} else {
		this->addError(Error::cannotOpen("nodes.txt"));
	}
}

bool SysSD::editNode(String titre, uint8_t nodesID, String type, uint8_t settings[]){
	return false;
}

bool SysSD::removeNode(String titre, uint8_t nodesID, String type, uint8_t settings[]){
	return false;
}

bool SysSD::editSetting(){
	return false;
}

String SysSD::readSettings(){
	return "no";
}

bool SysSD::addError(String error){
	bool result = true;
	File errors = SD.open("errors.txt", FILE_WRITE);
	if (errors){
		errors.println(error);
	} else {
		result = false;
	}
	return result;
}

bool SysSD::addWarning(String warning){
	bool result = true;
	File errors = SD.open("errors.txt", FILE_WRITE);
	if (errors){
		errors.println(warning);
	} else {
		result = false;
	}
	return result;
}


/*
* Vérifie si un utilisateur existe en se basant sur son CardID
*
*	A VALIDER/TESTER
*/
bool SysSD::findUserCardID(String cardID){
	bool found = false;
	String l_line = "";
	File users = SD.open("users.txt", FILE_READ);
	uint8_t nbLine = 0;
	while (users.available() != 0) {
		l_line = users.readStringUntil('\n');
		l_line = l_line.substring(l_line.length(), 3);
		if (l_line == cardID) {
			found = true;
			break;
		}
	}
	users.close();
	return found;
}


/*
* Vérifie si un utilisateur existe en se basant sur son CardID et donne la ligne correspondante
*
*	A VALIDER/TESTER
*/
bool SysSD::findUserCardID(String cardID, uint8_t* line){
	bool found = false;
	String l_line = "";
	File users = SD.open("users.txt", FILE_READ);
	uint8_t nbLine = 0;
	while (users.available() != 0) {
		nbLine++;
		l_line = users.readStringUntil('\n');
		l_line = l_line.substring(l_line.length(), 3);
		if (l_line == cardID) {
			found = true;
			*line = nbLine;
			break;
		}
	}
	users.close();
	return found;
}


/*
* Vérifie si un utilisateur existe en se basant sur son CardID et donne la ligne correspondante
* et renvoie une instance User correspondante
*
*	A COMPLETER VALIDER/TESTER
*/
/*bool SysSD::findUserCardID(String cardID, uint8_t* line, String userStr[]){
	bool found = false;
	String l_line = ""; String readCardID;
	File users = SD.open("users.txt", FILE_READ);
	uint8_t nbLine = 0;
  if(users){
  	while (users.available() != 0) {
  		nbLine++;
  		l_line = users.readStringUntil('\n');
  		readCardID = l_line.substring(l_line.length(), 3);
  		if (l_line == cardID) {
  			found = true;
  			*line = nbLine;
  			break;
      }
        if(c != " "){
      char c=""; String aWord;
      String[3] userTab; uint8_t userInd = 0;
      for (i=0; i<line.length(); i++){
        c = line[i];
          aWord += c;
        } else {
          userTab[userInd] = aWord;
          userInd++;
          aWord = "";
        }
      }
  	} else {
  	  this->addError(Error::cannotOpen("user.txt"));
  	}
  	users.close();
  }
	return found;
}*/

String SysSD::glandouillHeure(){
	String s = "00/00/2666 - 00:00:00";
	return s;
}
