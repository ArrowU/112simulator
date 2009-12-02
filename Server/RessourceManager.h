#ifndef _RESSOURCEMANAGER_H
#define _RESSOURCEMANAGER_H

#include <queue>
#include "Ressource.h"
#include "MSBuffer.h"
#include "MSThread"
#include "Call.h"


class RessourceManager : public MSThread
{
	//--- Attributs ---
	private:
		int ressourceMaxAmbulances;
		int ressourceMaxChoppers;
		int ressourceMaxMedics;
		int ressourceMaxTeams;
		MSBuffer<Ressource> *ambulances;
		MSBuffer<Ressource> *choppers;
		MSBuffer<Ressource> *medicalisedTeams;
		MSBuffer<Ressource> *nonMedicalisedTeams;
		queue<Call> waitingListPrio1;
		queue<Call> waitingListPrio2;
		queue<Call> waitingListPrio3;
		queue<Call> waitingListPrio0; // liste pour le traitement en urgence

		//--- Méthodes ---
	public:
		RessourceManager();
		~RessourceManager();
		void start();
		//Ressource getRessource(RessourceType);
		void freeRessource(Ressource);
		void addCallToWaitingList(Call);

		/* Options pour des points en plus:

		addRessource(RessourceType);
		removeRessource(RessourceType);

		*/
	private:
		bool missionPossible(Call);
		bool callCheckup(queue<Call>);
		
};

#endif