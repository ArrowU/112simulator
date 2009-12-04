#ifndef _RESSOURCEMANAGER_H
#define _RESSOURCEMANAGER_H

#include "Ressource.h"
#include "MSBuffer.h"
#include "MSThread.h"
#include "MSMutex.h";
#include "Call.h"


class RessourceManager : public MSThread
{
	//--- Attributs ---
	private:
		MSBuffer<Ressource> *ambulances;
		MSBuffer<Ressource> *choppers;
		MSBuffer<Ressource> *medics;
		MSBuffer<Ressource> *teams;
		MSBuffer<Call> waitingListPrio1;
		MSBuffer<Call> waitingListPrio2;
		MSBuffer<Call> waitingListPrio3;
		MSBuffer<Call> waitingListPrio0; // liste pour le traitement en urgence
		MSMutex *threadSafeLock1;
		MSMutex *threadSafeLock2;
		MSMutex *threadSafeLock3;
		MSMutex *threadSafeLock0;
		MSMutex *threadSafeLockRessources;
		bool newCall1;
		bool newCall2;
		bool newCall3;
		bool newCall0;

		//--- M�thodes ---
	public:
		RessourceManager();
		~RessourceManager();
		void start();
		void addCall(Call);
		void finishedMission(Call);
		

		/* Options pour des points en plus:

		addRessource(RessourceType);
		removeRessource(RessourceType);

		*/
	private:
		bool possibleMission(Call);
		void checkList(MSBuffer<Call>);
		
};

#endif