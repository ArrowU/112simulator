#include "RessourceManager.h"
#include <iostream>


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
	for (int i = 0; i < choppers.getMaxSize(); i++)
	{
		choppers.addElement(new Ressource(Ressource::CHOPPER, i);
	}
	for (int i = 0; i < ambulancess.getMaxSize(); i++)
	{
		ambulances.addElement(new Ressource(Ressource::AMBULANCE, i);
	}
	for (int i = 0; i < medics.getMaxSize(); i++)
	{
		medics.addElement(new Ressource(Ressource::MEDIC, i);
	}
	for (int i = 0; i < teams.getMaxSize(); i++)
	{
		teams.addElement(new Ressource(Ressource::TEAM, i);
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
}

void RessourceManager::start()
{
	threadSafeLock0.waitForUnlock(MSMutex::WAIT_INFINITE);
	checkList(waitingListPrio0);
	newCall0 = false;
	threadSafeLock0.unlock();
	if (!newCall0)
	{
		threadSafeLock1.waitForUnlock(MSMutex::WAIT_INFINITE);
		checkList(waitingListPrio1);
		newCall1 = false;
		threadSafeLock1.unlock();
	}
	if (!newCall0 && !newCall1)
	{
		threadSafeLock2.waitForUnlock(MSMutex::WAIT_INFINITE);
		checkList(waitingListPrio2);
		newCall2 = false;
		threadSafeLock2.unlock();
	}
	if (!newCall0 && !newCall1 && !newCall2)
	{
		threadSafeLock3.waitForUnlock(MSMutex::WAIT_INFINITE);
		checkList(waitingListPrio3);
		newCall3 = false;
		threadSafeLock3.unlock();
	}
}

void RessourceManager::addCallToWaitingList(Call call)
{
	//test de possibilite de l'appel
	requiredChoppers = call.getRequiredChoppers();
	requiredAmbulances = call.getRequiredAmbulances();
	requiredMedics = call.getRequiredMedics();
	requiredTeams = call.getRequiredTeams();

	if (requiredChoppers > choppers.getMaxSize() || requiredAmbulances > ambulances.getMaxSize() || requiredMedics > medics.getMaxSize() || requiredTeams > teams.getMaxSize())
	{
		call.isImpossibleCall();
	}
	// si possible, encodage dans les listes d'attente
	else
	{
		switch (call.getSource)
		{
			case Call::NURSING_HOME
				threadSafeLock1.waitForUnlock(MSMutex::WAIT_INFINITE);
				waitingListPrio1.addElement(call);
				threadSafeLock1.unlock;
				newCall1 = true;
				break;

			case Call::SCHOOL
				threadSafeLock2.waitForUnlock(MSMutex::WAIT_INFINITE);
				waitingListPrio2.addElement(call);
				threadSafeLock2.unlock;
				newCall2 = true;
				break;

			case Call::PRIVATE_INDIVIDUAL
				threadSafeLock3.waitForUnlock(MSMutex::WAIT_INFINITE);
				waitingListPrio3.addElement(call);
				threadSafeLock3.unlock;
				newCall3 = true;
				break;
		}
	}
}

void RessourceManager::finishedMission(Call call)
{
}

bool RessourceManager::possibleMission(Call call)
{
	if (requiredChoppers > choppers.getCurrentSize() || requiredAmbulances > ambulances.getCurrentSize() || requiredMedics > medics.getCurrentSize() || requiredTeams > teams.getCurrentSize())
		return false;
	else
		return true;
}

void RessourceManager::checkList(MSBuffer<Call> waitingList)
{
	for (int i = 0; i < waitingList.getCurrentSize(); i++)
	{
		Call waiting = waitingList.getElement();
		if (possibleMission(waiting))
		{
			//on lance la mission
		}
		else
		{
			// on remet l'appel dans la liste...
			waitingList.addElement(waiting);
		}
	}
}