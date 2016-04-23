// Error Class - By Clément BEGNAUD


#include "Error.h"
#include <WString.h>

using namespace std;

String Error::cannotOpen(String nomFichier){
	String error = "[Error] Le fichier \"" + nomFichier;
	error += "\" n'a pas pu être ouvert." ;
	return error;
}
