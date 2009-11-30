#include "Call.h"

Call::Call()
{
}

Call::~Call()
{
}

Call::Call(int choppers, int ambulances, int medics, int teams, int source) : requiredChoppers(choppers), requiredAmbulances(ambulances), requiredMedics(medics), requiredTeams(teams)
{
	switch ( source )
	{
		case 1:
			source = nursingHome;
			break;
		case 2:
			source = school;
			break;
		case 3:
			source = privateIndividual;
			break;
	}
}

void Call::setOperatorId(int opId)
{
	operatorId=opId;
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