// User Class Header - By Clément BEGNAUD


#ifndef USER_H
#define USER_H

#include <string.h>
#include <SPI.h>
//#include <iostream>

class User{


public: 
  	User();
	User(String nom, String prenom, String cardID);
	
	//ACCESSEURS:
	void setNom(String nom); String getNom();
	void setPrenom(String prenom); String getPrenom();
	void setCardID(uint8_t cardID); uint8_t getCardID();
	

private:
	String _nom;
	String _prenom;
	uint8_t _cardID;
};

#endif
