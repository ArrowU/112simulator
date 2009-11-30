#ifndef _RESSOURCE_H
#define _RESSOURCE_H

enum RessourceType
{
	chopper,
	ambulance,
	medicalisedTeam,
	nonMedicalisedTeam
};

class Ressource
{
	//--- Attributs ---
	private:
		RessourceType type;
		int id;

		//--- Méthodes ---
	public:
		Ressource(RessourceType,int);
		~Ressource();
		RessourceType getType();
		int getId();
	private:
		
};

#endif