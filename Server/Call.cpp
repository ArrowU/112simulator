#include "Call.h"
#include <stdio.h>

Call::~Call()
{
}

Call::Call(int choppers, int ambulances, int medics, int teams, int source) : requiredChoppers(choppers), requiredAmbulances(ambulances), requiredMedics(medics), requiredTeams(teams)
{
	this->source=source;
	ressources = new MSBuffer<Ressource>(10);
}

Call::Call()
{
}

void Call::setOperator(Operator* op)
{
	this->myOperator=op;
}

/*
Ressource* Call::getReservedRessource()
{
}
*/

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

Ressource* Call::getRessource()
{
	return NULL;
}