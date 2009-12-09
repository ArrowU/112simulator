#include "Operator.h"

#include "MSThread.h"

#include "CallCenter.h"
#include "RessourceManager.h"
#include "Call.h"

#include "windows.h"
#include <time.h>
#include <stdio.h>

// --- Classe MissionRunningThread ---
class MissionRunningThread : public MSThread
{
	private :
		Call* call;
	public :
		MissionRunningThread();
		void start();
		void setCall(Call*);
};

MissionRunningThread::MissionRunningThread(){
}

void MissionRunningThread::setCall(Call * c)
{
	this->call=c;
}

void MissionRunningThread::start()
{
	srand( (unsigned)time( NULL ) );
	int time=2500+(rand()*(2000/RAND_MAX)); // entre 2500 et 4500
	Sleep(time);
	call->freeRessources();
}

// --- Operator ---

Operator::Operator(int id,CallCenter* callCenter)
{
	//printf("Operator starting\n");
	this->id=id;
	this->callCenter=callCenter;
	callCount=0;
	callWaitingForRessources=new MSMutex(MSMutex::START_LOCKED);
	callAborted=false;
	//this->run();
}

Operator::~Operator()
{
}

void Operator::start()
{
	while(true)
	{
		Call* call = callCenter->getNextCall();
		callCount++;
		call->setOperator(this);
		call->setOperatorCallCount(callCount);
		//printf("Je l'ai eu");
		ressourceManager->addCallToWaitingList(call);
		callWaitingForRessources->waitForUnlock(MSMutex::WAIT_INFINITE);
		if(!callAborted)
		{
			MissionRunningThread* missionThread=new MissionRunningThread();
			missionThread->setCall(call);
			missionThread->run();
		}
		else
		{
			printf("Zut, appel Impossible");
		}
	}
}

CallCenter* Operator::getCallCenter()
{
	return callCenter;
}

int Operator::getCallCount()
{
	return callCount;
}

void Operator::incrementCallCount()
{
	callCount++;
}

int Operator::getId()
{
	return id;
}

void Operator::setRessourceManager(RessourceManager* resMan)
{
	this->ressourceManager=resMan;
}

RessourceManager* Operator::getRessourceManager()
{
	return this->ressourceManager;
}

void Operator::currentCallReadyToStart()
{
	callAborted=false;
	callWaitingForRessources->unlock();
}

void Operator::currentCallAborted()
{
	callAborted=true;
	callWaitingForRessources->unlock();
}