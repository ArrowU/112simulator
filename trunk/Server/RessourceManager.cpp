#include "RessourceManager.h"
#include <iostream>
//using namespace std;

RessourceManager::RessourceManager()
{
	// initialisation des ressources
	ressourceMaxAmbulances = 5;
	ressourceMaxChoppers = 1;
	ressourceMaxMedics = 3;
	ressourceMaxTeams = 5;
	// connexion au pipe
}

void RessourceManager::start()
{
	bool missionStarted;
	while (true)
	{
		missionStarted = false;
		// on balaye en permanence les chaine d'attente
		//si une chaine a lance une mission on recommence de 0
		missionStarted = callCheckup(waitingListPrio0);
		if (!missionStarted)
			missionStarted = callCheckup(waitingListPrio1);
		if (!missionStarted)
			missionStarted = callCheckup(waitingListPrio2);
		if (!missionStarted)
			missionStarted = callCheckup(waitingListPrio3);
	}
}

void RessourceManager::addCallToWaitingList(Call call)
{
	// placement de l'appel en fct de sa priorite
	if(call.getRequiredChoppers() <=  ressourceMaxChoppers && call.getRequiredAmbulances() <=  ressourceMaxAmbulances && call.getRequiredMedics() <=  ressourceMaxMedics && call.getRequiredTeams() <=  ressourceMaxTeams)
	{
		switch (call.getSource())
		{
		case 0:
			waitingListPrio1.push(call);
			break;
		case 1:
			waitingListPrio2.push(call);
			break;
		case 2:
			waitingListPrio3.push(call);
			break;
		}
	}
	else
	{
		std::cout<<"appel impossible a traiter"<<std::endl;
	}
}

bool RessourceManager::missionPossible(Call call)
{
	// condition a corriger
	if(call.getRequiredChoppers() <=  ressourceMaxChoppers && call.getRequiredAmbulances() <=  ressourceMaxAmbulances && call.getRequiredMedics() <=  ressourceMaxMedics && call.getRequiredTeams() <=  ressourceMaxTeams)
	{
		return true;
	}
}

bool RessourceManager::callCheckup(std::queue<Call> queue)
{
	bool missionStarted = false;
	std::queue<Call> listProv;

	while(!queue.empty())
	{
		if(missionPossible(queue.front()))
		{
			// lancement de la mission
			missionStarted = true;
		}
		else
		{
			listProv.push(queue.front());
		}
		queue.pop();
	}
	while (!listProv.empty())
	{
		queue.push(listProv.front());
		listProv.pop();
	}
	return missionStarted;
}