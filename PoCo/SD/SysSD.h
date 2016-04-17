// SD Class Header - By Clément BEGNAUD


#ifndef SYSSD_H
#define SYSSD_H


class SysSD : public SD{
	
	public:
	//Constructeur par défaut
	SD();
	bool createLog_Doors();
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
	bool addNode(String titre, uint_8t nodeID, String type, uint_8t[] settings);
	bool editNode(String titre, uint_8t nodeID, String type, uint_8t[] settings);
	bool removeNode(String titre, uint_8t nodeID, String type, uint_8t[] settings);
	bool SysSd::editSetting();
	String SysSd::readSettings();
	bool addError(String str);
	bool addWarning(String str);
	
	
	
	private:
	//Attributs
	
};

#endif