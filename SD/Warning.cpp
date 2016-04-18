// Warning Class - By Clément BEGNAUD

#include <string>
#include "Warning.h"

using namespace std;

static String Warning::logDoesNotExist(String nomFichier){
	String warning = "[Warning] Le fichier \"" + nomFichier;
	warning += "\" n'a pas été trouvé au démarrage du système. Il en sera créé un nouveau." ;
	return warning;	
}