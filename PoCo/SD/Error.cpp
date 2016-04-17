// Error Class - By Clément BEGNAUD

#include <string>
#include "Error.h"

using namespace std;

static String Error::cannotOpen(String nomFichier){
	String error = "[Error] Le fichier \"" + nomFichier;
	error += "\" n'a pas pu être ouvert." ;
	return error;
}