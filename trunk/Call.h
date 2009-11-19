#ifndef _CALL_H
#define _CALL_H

#include "Ressource.h"
//#include "Operator.h"

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
		int operatorId;
		int operatorCallCount;
		int requiredChoppers;
		int requiredAmbulances;
		int requiredMedicalisedTeams;
		int requiredNonMedicalisedTeams;
		Ressource* reservedRessources;

		//--- M�thodes ---
	public:
		Call(int,int,int,int);
		Call();
		~Call();
		void setOperatorId(int);
		int getOperatorId();
		Ressource* getReservedRessource();
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