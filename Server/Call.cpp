#include "Call.h"

#include "Ressource.h"
#include "RessourceManager.h"
#include "Operator.h"

#include <stdio.h>

#include "CallInfo.h"

Call::~Call()
{
}

Call::Call(CallInfo info)
{
	this->info=info;
	ressources = new MSBuffer<Ressource>(20);

}

Call::Call()
{
}

void Call::setOperator(Operator* op)
{
	this->myOperator=op;
}

Operator* Call::getOperator()
{
	return myOperator;
}


void Call::setOperatorCallCount(int a)
{
	operatorCallCount = a;
}
		
int Call::getOperatorCallCount()
{
	return operatorCallCount;
}

void Call::setRequiredChoppers(int a)
{
	info.requiredChoppers = a;
}
		
int Call::getRequiredChoppers()
{
	return info.requiredChoppers;
}
		
void Call::setRequiredAmbulances(int a)
{
	info.requiredAmbulances = a;
}
		
int Call::getRequiredAmbulances()
{
	return info.requiredAmbulances;
}

void Call::setRequiredMedics(int a)
{
	info.requiredMedics = a;
}

int Call::getRequiredMedics()
{
	return info.requiredMedics;
}
		
void Call::setRequiredTeams(int a)
{
	info.requiredTeams = a;
}
		
int Call::getRequiredTeams()
{
	return info.requiredTeams;
}

int Call::getSource()
{
	return info.source;
}

void Call::abort()
{
	Ressource* myRes=new Ressource(Ressource::AMBULANCE,9);
	int t =myRes->getType();
	myOperator->currentCallAborted();
	//printf("Appel Impossible");
}

void Call::readyToStart()
{
	myOperator->currentCallReadyToStart();
}

void Call::addRessource(Ressource * ressource)
{
	ressources->addElement(ressource);
}

MSBuffer<Ressource>* Call::getUsedRessources()
{
	return ressources;
}

Ressource* Call::freeRessources()
{
	return ressources->getElement(MSBuffer<Ressource>::RETURN_NULL_IF_EMPTY);
}

bool Call::hasRessources()
{
	return !ressources->isEmpty();
}

int Call::getWaitedTime()
{
	return waitedTime;
}

void Call::setWaitedTime(int time)
{
	waitedTime = time;
}