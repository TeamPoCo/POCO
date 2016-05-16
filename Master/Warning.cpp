// Warning Class - By Clément BEGNAUD

#include <string.h>
#include <SPI.h>
//#include <iostream>
#include "Warning.h"

using namespace std;

String Warning::logDoesNotExist(String nomFichier){
	String warning = "[Warning] Le fichier \"" + nomFichier;
	warning += "\" n'a pas été trouvé au démarrage du système. Il en sera créé un nouveau." ;
	return warning;	
}

String Warning::folderDoesNotExist(String nomDossier){
	String warning = "[Warning] Le dossier \"" + nomDossier;
	warning += "\" n'a pas été trouvé au démarrage du système. Il en sera créé un nouveau." ;
	return warning;	
}
