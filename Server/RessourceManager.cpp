#include "RessourceManager.h"
#include <stdio.h>


RessourceManager::RessourceManager()
{
	// initialisation des buffers
	waitingListPrio1 = new MSBuffer<Call>(10);
	waitingListPrio2 = new MSBuffer<Call>(10);
	waitingListPrio3 = new MSBuffer<Call>(10);
	waitingListPrio1 = new MSBuffer<Call>(10);
	choppers = new MSBuffer<Ressource>(1);
	ambulances = new MSBuffer<Ressource>(5);
	medics = new MSBuffer<Ressource>(3);
	teams = new MSBuffer<Ressource>(5);

	// initialisation des ressources
	for (int i = 0; i < choppers->getMaxSize(); i++)
	{
		choppers->addElement(new Ressource(Ressource::CHOPPER, i));
	}
	for (int i = 0; i < ambulances->getMaxSize(); i++)
	{
		ambulances->addElement(new Ressource(Ressource::AMBULANCE, i));
	}
	for (int i = 0; i < medics->getMaxSize(); i++)
	{
		medics->addElement(new Ressource(Ressource::MEDIC, i));
	}
	for (int i = 0; i < teams->getMaxSize(); i++)
	{
		teams->addElement(new Ressource(Ressource::TEAM, i));
	}

	// initialisation des mutex et des balises
	threadSafeLock1 = new MSMutex(MSMutex::START_UNLOCKED);
	threadSafeLock2 = new MSMutex(MSMutex::START_UNLOCKED);
	threadSafeLock3 = new MSMutex(MSMutex::START_UNLOCKED);
	threadSafeLock0 = new MSMutex(MSMutex::START_UNLOCKED);
	threadSafeLockRessources = new MSMutex(MSMutex::START_UNLOCKED);
	newCall1 = false;
	newCall2 = false;
	newCall3 = false;
	newCall0 = false;
	printf("RessourceManager created... \n");
}

void RessourceManager::start()
{
	printf("RessourceManager launched... \n");
	threadSafeLock0->waitForUnlock(MSMutex::WAIT_INFINITE);
	checkList(waitingListPrio0);
	newCall0 = false;
	threadSafeLock0->unlock();
	if (!newCall0)
	{
		threadSafeLock1->waitForUnlock(MSMutex::WAIT_INFINITE);
		checkList(waitingListPrio1);
		newCall1 = false;
		threadSafeLock1->unlock();
	}
	if (!newCall0 && !newCall1)
	{
		threadSafeLock2->waitForUnlock(MSMutex::WAIT_INFINITE);
		checkList(waitingListPrio2);
		newCall2 = false;
		threadSafeLock2->unlock();
	}
	if (!newCall0 && !newCall1 && !newCall2)
	{
		threadSafeLock3->waitForUnlock(MSMutex::WAIT_INFINITE);
		checkList(waitingListPrio3);
		newCall3 = false;
		threadSafeLock3->unlock();
	}
}

void RessourceManager::addCallToWaitingList(Call* call)
{
	//test de possibilite de l'appel
	int requiredChoppers = call->getRequiredChoppers();
	int requiredAmbulances = call->getRequiredAmbulances();
	int requiredMedics = call->getRequiredMedics();
	int requiredTeams = call->getRequiredTeams();

	if (requiredChoppers > choppers->getMaxSize() || requiredAmbulances > ambulances->getMaxSize() || requiredMedics > medics->getMaxSize() || requiredTeams > teams->getMaxSize())
	{
		call->isImpossibleCall();
	}
	// si possible, encodage dans les listes d'attente
	else
	{
		switch (call->getSource())
		{
		case Call::NURSING_HOME:
				threadSafeLock1->waitForUnlock(MSMutex::WAIT_INFINITE);
				waitingListPrio1->addElement(call);
				newCall1 = true;
				threadSafeLock1->unlock();
				break;

		case Call::SCHOOL:
				threadSafeLock2->waitForUnlock(MSMutex::WAIT_INFINITE);
				waitingListPrio2->addElement(call);
				newCall2 = true;
				threadSafeLock2->unlock();
				break;

		case Call::PRIVATE_INDIVIDUAL:
				threadSafeLock3->waitForUnlock(MSMutex::WAIT_INFINITE);
				waitingListPrio3->addElement(call);
				newCall3 = true;
				threadSafeLock3->unlock();
				break;
		}
	}
	printf("Call checked... \n");
}

void RessourceManager::finishedMission(Call* call)
{
}

bool RessourceManager::possibleMission(Call* call)
{
	if (call->getRequiredChoppers() > choppers->getCurrentSize() || call->getRequiredAmbulances() > ambulances->getCurrentSize() || call->getRequiredMedics() > medics->getCurrentSize() || call->getRequiredTeams() > teams->getCurrentSize())
		return false;
	else
		return true;
}

void RessourceManager::checkList(MSBuffer<Call>* waitingList)
{
	for (int i = 0; i < waitingList->getCurrentSize(); i++)
	{
		Call* waiting = waitingList->getElement(MSBuffer<Call>::RETURN_NULL_IF_EMPTY);
		if (possibleMission(waiting))
		{
			//on lance la mission
		}
		else
		{
			// on remet l'appel dans la liste...
			waitingList->addElement(waiting);
		}
	}
}