// SysSD Class - By Clément BEGNAUD

#include <string>
#include <SPI.h>
#include <SD.h>

#include "SysSD.h"

using namespace std;

const int SD_chipSelect = 4;

//Constructeur par défaut
SysSD::SysSD(){
	//Détection de la carte SD
	if (!*this.begin(SD_chipSelect)) {
		//------  COMMENT INDIQUER L'ERREUR DANS CE CAS?   ------
		//------   COMMENT VERIFIER L'ESPACE DISPONIBLE SUR LA CARTE?   ------
		return;
	} else {
		//Détection des logs et création des logs manquants le cas échéant
		// et Avertir que des logs manquaient
		//Log "errors.txt"
		if (!*this.exists("errors.txt")) {
			File errors = SD.open("errors.txt", FILE_WRITE);
			errors.close();
			*this.addWarning(Warning.logDoesNotExist("errors.txt"));
		}
		//Log "doors.txt"
		if (!*this.exists("doors.txt")) {
			*this.createLog_Doors();
			*this.addWarning(Warning.logDoesNotExist("doors.txt"));
		}
		//Log "users.txt"
		if (!*this.exists("users.txt")) {
			*this.createLog_Users();
			*this.addWarning(Warning.logDoesNotExist("users.txt"));
		}
		//Log "admins.txt"
		if (!*this.exists("admins.txt")) {
			*this.createLog_Admins();
			*this.addWarning(Warning.logDoesNotExist("admins.txt"));
		}
		//Log "settings.txt"
		if (!*this.exists("settings.txt")) {
			*this.createLog_Settings();
			*this.addWarning(Warning.logDoesNotExist("settings.txt"));
		}
		//Log "actions.txt"
		if (!*this.exists("actions.txt")) {
			*this.createLog_Actions();
			*this.addWarning(Warning.logDoesNotExist("actions.txt"));
		}
	}
}

bool SysSD::createLog_Doors(){
	File doors = *this.open("example.txt", FILE_WRITE);
	doors.close();
}

bool SysSD::createLog_Users(){
	File users = *this.open("users.txt", FILE_WRITE);
	users.close();
}

bool SysSD::createLog_Admins(){
	File admins = *this.open("admins.txt", FILE_WRITE);
	admins.close();
}

bool SysSD::createLog_Settings(){
	File settings = *this.open("settings.txt", FILE_WRITE);
	settings.close();
}

bool SysSD::createLog_Actions(){
	File actions = *this.open("actions.txt", FILE_WRITE);
	actions.close();
}

bool SysSD::createLog_Errors(){
	File errors = *this.open("errors.txt", FILE_WRITE);
	errors.close();
}

bool SysSD::addAction(String titre, String message){
	File actions = *this.open("actions.txt", FILE_WRITE);
	if(actions){
		String action = "[" + titre + "] " + message;
		*this.println(action);
	} else {
		*this.addError(Error.cannotOpen("action.txt"));
	}
	errors.close();
}

bool SysSD::addPeople(String nom, String prenom, String cardID){
	File users = *this.open("users.txt", FILE_WRITE);
	if(actions){
		String user = "" + nom + " " + prenom + " " + cardID;
		*this.println(user);
	} else {
		*this.addError(Error.cannotOpen("action.txt"));
	}
	users.close();
}

bool SysSD::editPeople(String nom, String prenom, String cardID){
	
}

bool SysSD::removePeople(String nom, String prenom, String cardID){
	
}

bool SysSD::addNode(String titre, uint_8t nodeID, String type, uint_8t[] settings){
	File doors = *this.open("doors.txt", FILE_WRITE);
	if(doors){
		String door = "" + titre + " " + nodeID + " " + type + " " + settings;
		*this.println(door);
	} else {
		*this.addError(Error.cannotOpen("doors.txt"));
	}
	users.doors();
}

bool SysSD::editNode(String titre, uint_8t nodeID, String type, uint_8t[] settings){
	
}

bool SysSD::removeNode(String titre, uint_8t nodeID, String type, uint_8t[] settings){
	
}

bool SysSd::editSetting(){
	
}

String SysSd::readSettings(){
	
}

bool SysSD::addError(String str){
	bool result = true;
	File errors = *this.open("errors.txt", FILE_WRITE);
	if (errors){}
		File.println(error);
	} else {
		result = false;
	}
	return result;
}

bool SysSD::addWarning(String str){
	bool result = true;
	File errors = *this.open("errors.txt", FILE_WRITE);
	if (errors){}
		File.println(warning);
	} else {
		result = false;
	}
	return result;
}