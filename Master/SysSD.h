// SD Class Header - By Clément BEGNAUD


#ifndef SYSSD_H
#define SYSSD_H

#include <String.h>
#include <SPI.h>
//#include <iostream>
#include "User.h"
#include "Error.h"
#include "Warning.h"
#include "Door.h"



class SysSD {
	
	public:
	//Constructeur par défaut
	SysSD();
	bool createLog_Nodes();
	bool createLog_Users();
	bool createLog_Admins();
	bool createLog_Settings();
	bool createLog_Actions();
	bool createLog_Errors();
	bool createLog_Stats();
	bool addAction(String titre, String message);
	bool addPeople(String nom, String prenom, String cardID);
	bool editPeople(String nom, String prenom, String cardID);
	bool removePeople(String nom, String prenom, String cardID);
	bool addNode(String titre, uint8_t nodeID, String type, uint8_t settings[]);
	bool editNode(String titre, uint8_t nodeID, String type, uint8_t settings[]);
	bool removeNode(String titre, uint8_t nodeID, String type, uint8_t settings[]);
	bool editSetting();
	String readSettings();
	bool addError(String error);
	bool addWarning(String warning);
	bool findUserCardID(String match);
	bool findUserCardID(String match, uint8_t* line);
 	bool findUserCardID(String match, uint8_t* line, String userStr[]);
	String glandouillHeure();
	
	
	
	private:
	//Attributs
	
};

#endif
