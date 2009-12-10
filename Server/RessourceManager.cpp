#include "RessourceManager.h"

#include "Ressource.h"
#include "Call.h"

#include <stdio.h>


RessourceManager::RessourceManager()
{
	// initialisation des buffers
	waitingListPrio0 = new MSBuffer<Call>(10); // prio absolue
	waitingListPrio1 = new MSBuffer<Call>(10);
	waitingListPrio2 = new MSBuffer<Call>(10);
	waitingListPrio3 = new MSBuffer<Call>(10);
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
	threadSafeLockChopper = new MSMutex(MSMutex::START_UNLOCKED);
	MSMutex *threadSafeLockAmbulance = new MSMutex(MSMutex::START_UNLOCKED);
	MSMutex *threadSafeLockMedic = new MSMutex(MSMutex::START_UNLOCKED);
	MSMutex *threadSafeLockTeam = new MSMutex(MSMutex::START_UNLOCKED);
	newCall1 = false;
	newCall2 = false;
	newCall3 = false;
	newCall0 = false;
	hasNewRessource = false;
	printf("RessourceManager created... \n");
}

void RessourceManager::start()
{
	printf("RessourceManager launched... \n");
	while (true)
	{
		threadSafeLock0->waitForUnlock(MSMutex::WAIT_INFINITE);
		checkList(waitingListPrio0);
		newCall0 = false;
		threadSafeLock0->unlock();
		hasNewRessource = false;
		if (!newCall0 && !hasNewRessource)
		{
			threadSafeLock1->waitForUnlock(MSMutex::WAIT_INFINITE);
			checkList(waitingListPrio1);
			newCall1 = false;
			threadSafeLock1->unlock();
		}
		if (!newCall0 && !newCall1 && !hasNewRessource)
		{
			threadSafeLock2->waitForUnlock(MSMutex::WAIT_INFINITE);
			checkList(waitingListPrio2);
			newCall2 = false;
			threadSafeLock2->unlock();
		}
		if (!newCall0 && !newCall1 && !newCall2 && !hasNewRessource)
		{
			threadSafeLock3->waitForUnlock(MSMutex::WAIT_INFINITE);
			checkList(waitingListPrio3);
			newCall3 = false;
			threadSafeLock3->unlock();
		}
		//incrementation du temps
		timeControl();
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
		call->abort();
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
	call->setWaitedTime(0);
	printf("Call checked... \n");
}

void RessourceManager::releaseRessource(Call *call)
{
	while (call->hasRessources())
	{
		switch(call->freeRessources()->getType())
		{
		case Ressource::CHOPPER:
			threadSafeLockChopper->waitForUnlock(MSMutex::WAIT_INFINITE);
			choppers->addElement(ressource);
			threadSafeLockChopper->unlock();
			break;
		case Ressource::AMBULANCE:
			threadSafeLockAmbulance->waitForUnlock(MSMutex::WAIT_INFINITE);
			ambulances->addElement(ressource);
			threadSafeLockAmbulance->unlock();
			break;
		case Ressource::MEDIC:
			threadSafeLockMedic->waitForUnlock(MSMutex::WAIT_INFINITE);
			medics->addElement(ressource);
			threadSafeLockMedic->unlock();
			break;
		case Ressource::TEAM:
			threadSafeLockTeam->waitForUnlock(MSMutex::WAIT_INFINITE);
			teams->addElement(ressource);
			threadSafeLockTeam->unlock();
			break;
		default:
			printf("Error in RessourceManager while trying to free Ressources \n");
			system("pause");
		
		}
	}
	hasNewRessource = true;
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
			// on ajoute les ressources
			threadSafeLockChopper->waitForUnlock(MSMutex::WAIT_INFINITE);
			for (int i = 0; i < waiting->getRequiredChoppers; i++)
			{
				waiting->addRessource(choppers->getElement());
			}
			threadSafeLockChopper->unlock();
			threadSafeLockAmbulance->waitForUnlock(MSMutex::WAIT_INFINITE);
			for (int i = 0; i < waiting->getRequiredAmbulances; i++)
			{
				waiting->addRessource(ambulances->getElement());
			}
			threadSafeLockAmbulance->unlock();
			threadSafeLockMedic->waitForUnlock(MSMutex::WAIT_INFINITE);
			for (int i = 0; i < waiting->getRequiredMedics; i++)
			{
				waiting->addRessource(medics->getElement());
			}
			threadSafeLockMedic->unlock();
			threadSafeLockTeam->waitForUnlock(MSMutex::WAIT_INFINITE);
			for (int i = 0; i < waiting->getRequiredTeams; i++)
			{
				waiting->addRessource(teams->getElement());
			}
			threadSafeLockTeam->unlock();
			//on lance la mission
			waiting->readyToStart();
			// Le call va alors prévenir l'opérateur, qui va créer les threads correspondant, qui font le sleep(rand)
			// puis libèrent les ressources, puis vont Logger l'appel;
		}
		else
		{
			// on remet l'appel dans la liste...
			waitingList->addElement(waiting);
		}
	}
}

void RessourceManager::timeControl()
{
	//liste 1
	for (int i = 0; i < waitingListPrio1->getCurrentSize(); i++)
	{
		call = waitingListPrio1->getElement();
		call->setWaitedTime(call->getWaitedTime());
		if (call->getWaitedTime > waitingTime)
		{
			threadSafeLock0->waitForUnlock(MSMutex::WAIT_INFINITE);
			call->setWaitedTime(0);
			waitingListPrio0->addElement(call);
			threadSafeLock0->unlock();
		}
		else
		{
			threadSafeLock1->waitForUnlock(MSMutex::WAIT_INFINITE);
			waitingListPrio1->addElement(call);
			threadSafeLock1->unlock();
		}
	}

	//liste 2
	for (int i = 0; i < waitingListPrio2->getCurrentSize(); i++)
	{
		call = waitingListPrio2->getElement();
		call->setWaitedTime(call->getWaitedTime());
		if (call->getWaitedTime > waitingTime)
		{
			threadSafeLock1->waitForUnlock(MSMutex::WAIT_INFINITE);
			call->setWaitedTime(0);
			waitingListPrio1->addElement(call);
			threadSafeLock1->unlock();
		}
		else
		{
			threadSafeLock2->waitForUnlock(MSMutex::WAIT_INFINITE);
			waitingListPrio2->addElement(call);
			threadSafeLock2->unlock();
		}
	}

	//liste 3
	for (int i = 0; i < waitingListPrio3->getCurrentSize(); i++)
	{
		call = waitingListPrio3->getElement();
		call->setWaitedTime(call->getWaitedTime());
		if (call->getWaitedTime > waitingTime)
		{
			threadSafeLock2->waitForUnlock(MSMutex::WAIT_INFINITE);
			call->setWaitedTime(0);
			waitingListPrio2->addElement(call);
			threadSafeLock2->unlock();
		}
		else
		{
			threadSafeLock3->waitForUnlock(MSMutex::WAIT_INFINITE);
			waitingListPrio3->addElement(call);
			threadSafeLock3->unlock();
		}
	}
}