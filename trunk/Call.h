#ifndef _CALL_H
#define _CALL_H

#include "Ressource.h"
#include "Operator.h"
#include <vector>

enum CallOrigin
{
	school,
	nursingHome,
	privateIndividual
};

class Call
{
	//--- Attributs ---
	private:
		CallOrigin origin;
		Operator responsibleOperator;
		int operatorCallCount;
		int requiredChoppers;
		int requiredAmbulances;
		int requiredMedicalisedTeams;
		int requiredNonMedicalisedTeams;
		std::vector<Ressource> reservedRessources;

		//--- Méthodes ---
	public:
		Call(int,int,int,int);
		Call();
		~Call();
		void setOperator(Operator);
		Operator getOperator();
		std::vector<Ressource> getReservedRessource();
		void setOperatorCallCount(int);
		int getOperatorCallCount();
		void setRequiredChoppers(int);
		int getRequiredChoppers();
		void setRequiredAmbulances(int);
		int getRequiredAmbulances();
		void setRequiredMedicalisedTeams(int);
		int getRequiredMedicalisedTeams();
		void setRequiredNonMedicalisedTeams(int);
		int getRequiredNonMedicalisedTeams();
	private:
		
};

#endif