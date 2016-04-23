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
		//Log "nodes.txt"
		if (!*this.exists("nodes.txt")) {
			*this.createLog_Nodes();
			*this.addWarning(Warning.logDoesNotExist("nodes.txt"));
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

/**
*	Crée le log "nodes.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Nodes(){
	bool cree = false;
	File nodes = *this.open("nodes.txt", FILE_WRITE);
	if(nodes) bool cree = true;
	nodes.close();
	return cree;
}

/**
*	Crée le log "users.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Users(){
	bool cree = false;
	File users = *this.open("users.txt", FILE_WRITE);
	if(nodes) bool cree = true;
	users.close();
	return cree;
}

/**
*	Crée le log "admins.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Admins(){
	bool cree = false;
	File admins = *this.open("admins.txt", FILE_WRITE);
	if(nodes) bool cree = true;
	admins.close();
	return cree;
}

/**
*	Crée le log "settings.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Settings(){
	bool cree = false;
	File settings = *this.open("settings.txt", FILE_WRITE);
	if(nodes) bool cree = true;
	settings.close();
	return cree;
}

/**
*	Crée le log "actions.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Actions(){
	bool cree = false;
	File actions = *this.open("actions.txt", FILE_WRITE);
	if(nodes) bool cree = true;
	actions.close();
	return cree;
}

/**
*	Crée le log "errors.txt".
*	
*	À TESTER/VALIDER
*/
bool SysSD::createLog_Errors(){
	bool cree = false;
	File errors = *this.open("errors.txt", FILE_WRITE);
	if(nodes) bool cree = true;
	errors.close();
	return cree;
}

/**
*	Ajoute une action au log "action.txt".
*	
*	COMMENT GERER LA DATE?
*/
bool SysSD::addAction(String titre, String message){
	File actions = *this.open("actions.txt", FILE_WRITE);
	if(actions){
		String action = /*formatDate() + */"[" + titre + "] " + message;
		*this.println(action);
	} else {
		*this.addError(Error.cannotOpen("action.txt"));
	}
	errors.close();
}

/**
*	Ajoute un utilisateur au log "users.txt".
*	
*	À TESTER/VALIDER
*/
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

bool SysSD::addNode(String titre, uint_8t nodesID, String type, uint_8t[] settings){
	File nodes = *this.open("nodes.txt", FILE_WRITE);
	if(nodes){
		String door = "" + titre + " " + nodesID + " " + type + " " + settings;
		*this.println(door);
	} else {
		*this.addError(Error.cannotOpen("nodes.txt"));
	}
	users.nodes();
}

bool SysSD::editNode(String titre, uint_8t nodesID, String type, uint_8t[] settings){
	
}

bool SysSD::removeNode(String titre, uint_8t nodesID, String type, uint_8t[] settings){
	
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