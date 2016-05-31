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
    found = this->findUserCardID(nom, prenom, &line); // Verification que l'ID correspond bien à la personne qu'on cherche.
  }
  if (found){
    String currentUser[3];
    this->removePeople(currentUser[0], currentUser[0], currentUser[0]);
    this->addPeople(nom, prenom, cardID);
	}
 return found;
}

/**
 * Efface l'utilisateur donné
 * 
 */
bool SysSD::removePeople(String nom, String prenom, String cardID){
	uint8_t nLigne;
  bool found = this->findUserCardID(cardID, &nLigne);
  bool efface = false;
  if (found){
    efface = this->effacerLigne("/", "users.txt", nLigne);
  }
	return efface;
}

/**
 * Parcourt les dossiers afin de supprimer les autorisations residuelles
 * 
 * @return /!\ true /!\
 * 
 * A VALIDER
 */
bool SysSD::cleanCardID(String cardID){
  File root = SD.open("/");
  String path;
  while (true) {
    path = "/";
    File entry =  root.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    if (entry.isDirectory()) {
      path += entry.name(); path += "/";
      if(SD.exists(path+cardID)){
        SD.remove(path+cardID);
      }
    }
    entry.close();
  }
  
  return true;
}

/**
 * Parcourt les dossiers afin d'adapter les autorisations residuelles
 */ 
bool SysSD::cleanCardID(String oldCardID, String newCardID){
  File root = SD.open("/");
  String path;
  while (true) {
    path = "/";
    File entry =  root.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    if (entry.isDirectory()) {
      path += entry.name(); path += "/";
      if(SD.exists(path+oldCardID)){
        this->renommer(path, oldCardID, path, newCardID);
      }
    }
    entry.close();
  }
  
  return true;
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

/**
 * Ajoute un message d'erreur au log "warning.txt"
 */
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

/**
 * Ajoute un message warning au log "warning.txt"
 */
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
* @param cardID   La chaine de caracteres contenant l'ID à trouver
* @param *line    Pointeur -> le numéro de la ligne définissant l'utilisateur
* @return         Si l'utilisateur a été trouvé
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
* 
* @param nom      La chaine de caracteres contenant le nom à trouver
* @param prenom   La chaine de caracteres contenant le prenom à touver
* @param *line    Pointeur -> le numéro de la ligne définissant l'utilisateur
* @return         Si l'utilisateur a été trouvé
* 
*  A VALIDER/TESTER
*/
bool SysSD::findUserCardID(String nom, String prenom, uint8_t* line){
  bool found = false;
  String l_line = "";
  File users = SD.open("users.txt", FILE_READ);
  uint8_t nbLine = 0;
  while (users.available() != 0) {
    nbLine++;
    l_line = users.readStringUntil('\n');
    l_line = l_line.substring(l_line.length(), 3);
    if (l_line == (""+nom + prenom)) {
      found = true;
      *line = nbLine;
      break;
    }
  }
  users.close();
  return found;
}

/**
 * Efface une ligne d'un fichier.
 * 
 * @param chemin        Le chemin du fichier
 * @param nomFichier    Le nom du fichier à modifier
 * @param numeroLigne   La ligne à effacer.
 * @return              La ligne a été effacée et le fichier temporaire a ete supprime
 */

boolean SysSD::effacerLigne(String chemin, String nomFichier, uint8_t numeroLigne){
  boolean ligneParcourue = false;
  boolean bufSuppr = false;
  File fichier = SD.open(chemin + nomFichier, FILE_READ);
  if(SD.exists(chemin + "buffer.txt")){
    SD.remove(chemin + "buffer.txt"); 
  }
  File buf = SD.open(chemin + "buffer.txt", FILE_WRITE);
  String ligne = ""; uint8_t numLigne = 0; uint8_t i;
  while(fichier.available()){             // Lecture du fichier ligne par ligne
    ligne += fichier.readStringUntil('\n');
    if (numLigne != numeroLigne-1){           
      buf.println(""+ligne);
    } else {
      ligneParcourue = true;
    }
    ligne = "";                           // Réinitialisation de la chaîne de caractère "ligne"
    numLigne++;
  }
  fichier.close(); buf.close();           // Fermeture du fichier
  SD.remove(chemin + nomFichier);
  renommer(chemin, "buffer.txt", chemin,  nomFichier);
  /*if (SD.exists(chemin + "buffer.txt")) { // Suppressin du fichier "buffer.txt" si restant
    SD.remove(chemin + "buffer.txt"); 
  }*/
  bufSuppr = !SD.exists(chemin + "buffer.txt");
  
  return (ligneParcourue && bufSuppr);
}


/**
 * Créée une copie du fichier d'entree, la ligne indiquée étant supprimee.
 * 
 * @param cheminIN        Le chemin du fichier
 * @param nomFichierIN    Le nom du fichier à modifier
 * @param cheminOUT       Le chemin du fichier
 * @param nomFichierOUT   Le nom du fichier à modifier
 * @param numeroLigne     La ligne à effacer.
 * @param suppr           Si le fichier de sortie existe deja, donne l'autorisation ou non d'écraser le fichier de sortie existant
 * @return                Si une erreur s'est produite.
 */
boolean SysSD::effacerLigneVers(String cheminIN, String nomFichierIN, String cheminOUT, String nomFichierOUT, uint8_t numeroLigne, boolean suppr){
  boolean ligneParcourue = false;
  boolean ok = true;
  File fIn = SD.open(cheminIN + nomFichierIN, FILE_READ);
  if(SD.exists(cheminOUT)){
    if(SD.exists(cheminOUT + nomFichierOUT)){
      if (suppr){                             // Autorisation d'ecrasement accordee.
        SD.remove(cheminOUT + nomFichierOUT); 
      } else {                                // Autorisation d'ecrasement non accordee.
        ok = false; // Le fichier de sortie existe deja, et il n'est pasautorise de le supprimer.
      }
    }
  } else {
    ok = false; // Le chemin specifie n'existe pas.
  }
  if (ok){  // Si toutes les conditions nécessaires sont valides, on procède alors.
    File fOut = SD.open(cheminOUT + nomFichierOUT, FILE_WRITE);
    String ligne = ""; uint8_t numLigne = 0; uint8_t i;
    while(fIn.available()){             // Lecture du fichier ligne par ligne
      ligne += fIn.readStringUntil('\n');
      if (numLigne != numeroLigne-1){          
        fOut.println(""+ligne);
      } else {
        ligneParcourue = true;
      }
      ligne = "";                           // Réinitialisation de la chaîne de caractère "ligne"
      numLigne++;
    }
    fIn.close(); fOut.close();           // Fermeture des fichiers
  }
  return (ok && ligneParcourue) ;
}

/**
 * Créée une copie du fichier d'entree, la ligne indiquée étant supprimee.
 * 
 * @param cheminIN        Le chemin du fichier
 * @param nomFichierIN    Le nom du fichier à renommer
 * @param cheminOUT       Le chemin du fichier
 * @param nomFichierOUT   Le nom du fichier après renomage
 * @return                Si le renommage a bien fonctionné
 */
boolean SysSD::renommer(String cheminIN, String nomFichierIN, String cheminOUT, String nomFichierOUT){
  boolean ok = true;
  File fIn = SD.open(cheminIN + nomFichierIN, FILE_READ);
  if(SD.exists(cheminOUT)){
    if((cheminIN + nomFichierIN) == (cheminOUT + nomFichierOUT)){
       ok = false; // Le fichier de sortie existe deja, et il n'est pas autorise de le supprimer.
    }
  } else {
    ok = false; // Le chemin specifie n'existe pas.
  }
  if (ok){  // Si toutes les conditions nécessaires sont valides, on procède alors.
    File fOut = SD.open(cheminOUT + nomFichierOUT, FILE_WRITE);
    String ligne = ""; uint8_t numLigne = 0; uint8_t i;
    while(fIn.available()){             // Lecture du fichier ligne par ligne
      ligne += fIn.readStringUntil('\n');      
      fOut.println(""+ligne);
      ligne = ""; 
    }
                // Réinitialisation de la chaîne de caractère "ligne"
    fOut.close();
    }
   fIn.close();            // Fermeture des fichiers
   if (SD.exists(cheminIN + nomFichierIN)) { // Suppressin du fichier "buffer.txt" si restant
    SD.remove(cheminIN + nomFichierIN); 
   }
  return ok  ;
}


/**
 * Methode qui renvoie une date... fantasiste
 */
String SysSD::glandouillHeure(){
	String s = "00/00/2666 - 00:00:00";
	return s;
}
