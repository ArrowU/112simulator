#ifndef _RESSOURCE_H
#define _RESSOURCE_H

class Ressource
{
	//--- Attributs ---
public:
	//--- Constantes statiques ---
	static const int CHOPPER = 0;
	static const int AMBULANCE = 1;
	static const int MEDIC = 2;
	static const int TEAM = 3;
	
private:
		int type;
		int id;

		//--- Méthodes ---
public:
		Ressource(int, int); // type, id
		~Ressource();
		int getType();
		int getId();
	
private:
		
};

#endif