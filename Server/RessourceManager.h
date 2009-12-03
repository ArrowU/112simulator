#ifndef _RESSOURCEMANAGER_H
#define _RESSOURCEMANAGER_H

#include <queue>
#include "Ressource.h"
#include "MSBuffer.h"
#include "MSThread.h"
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
		std::queue<Call> waitingListPrio1;
		std::queue<Call> waitingListPrio2;
		std::queue<Call> waitingListPrio3;
		std::queue<Call> waitingListPrio0; // liste pour le traitement en urgence

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
		bool callCheckup(std::queue<Call>);
		
};

#endif