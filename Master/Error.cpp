// Error Class - By Clément BEGNAUD

#include <String.h>
#include <WString.h>
//#include <iostream.h>
#include "Error.h"


using namespace std;

String Error::cannotOpen(String nomFichier){
	String error = "[Error] Le fichier \"" + nomFichier;
	error += "\" n'a pas pu être ouvert." ;
	return error;
}


