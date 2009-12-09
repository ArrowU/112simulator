#include "Call.h"
#include <stdio.h>

Call::~Call()
{
}

Call::Call(int choppers, int ambulances, int medics, int teams, int source) : requiredChoppers(choppers), requiredAmbulances(ambulances), requiredMedics(medics), requiredTeams(teams)
{
	this->source=source;
	ressources = new MSBuffer<Ressource>(20);
}

Call::Call()
{
}

void Call::setOperator(Operator* op)
{
	this->myOperator=op;
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
	requiredChoppers = a;
}
		
int Call::getRequiredChoppers()
{
	return requiredChoppers;
}
		
void Call::setRequiredAmbulances(int a)
{
	requiredAmbulances = a;
}
		
int Call::getRequiredAmbulances()
{
	return requiredAmbulances;
}

void Call::setRequiredMedics(int a)
{
	requiredMedics = a;
}

int Call::getRequiredMedics()
{
	return requiredMedics;
}
		
void Call::setRequiredTeams(int a)
{
	requiredTeams = a;
}
		
int Call::getRequiredTeams()
{
	return requiredTeams;
}

int Call::getSource()
{
	return source;
}

void Call::isImpossibleCall()
{
	printf("Appel Impossible");
}

void Call::addRessource(Ressource * ressource)
{
	ressources->addElement(ressource);
}

void Call::freeRessources()
{
	while (!ressources->isEmpty())
	{
		ressourceManager->newRessource(ressources->getElement(MSBuffer<Ressource>::RETURN_NULL_IF_EMPTY));
	}
}