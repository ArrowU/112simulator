#ifndef _RESSOURCEMANAGER_H
#define _RESSOURCEMANAGER_H

#include "Ressource.h"
#include "MSBuffer.h"

class RessourceManager
{
	//--- Attributs ---
	private:
		MSBuffer<Ressource> *ambulances;
		MSBuffer<Ressource> *choppers;
		MSBuffer<Ressource> *medicalisedTeams;
		MSBuffer<Ressource> *nonMedicalisedTeams;

		//--- Méthodes ---
	public:
		RessourceManager();
		~RessourceManager();
		Ressource getRessource(RessourceType);
		void freeRessource(Ressource);

		/* Options pour des points en plus:

		addRessource(RessourceType);
		removeRessource(RessourceType);

		*/
	private:
		
};

#endif