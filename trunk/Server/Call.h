#ifndef _CALL_H
#define _CALL_H

//#include "Ressource.h"
//#include "Operator.h"

enum CallOrigin
{
	nursingHome,
	school,
	privateIndividual
};

class Call
{
	//--- Attributs ---
	public:
		static const int NURSING_HOME=1;
		static const int SCHOOL=2;
		static const int PRIVATE_INDIVIDUAL=3;
	private:
		//int origin;
		int operatorId;
		int operatorCallCount;
		int requiredChoppers;
		int requiredAmbulances;
		int requiredMedics;
		int requiredTeams;
		int source;
		//Ressource* reservedRessources;

		//--- Méthodes ---
	public:
		Call(int,int,int,int,int);
		Call();
		~Call();
		void setOperatorId(int);
		int getOperatorId();
		//Ressource* getReservedRessource();
		void setOperatorCallCount(int);
		int getOperatorCallCount();
		void setRequiredChoppers(int);
		int getRequiredChoppers();
		void setRequiredAmbulances(int);
		int getRequiredAmbulances();
		void setRequiredMedics(int);
		int getRequiredMedics();
		void setRequiredTeams(int);
		int getRequiredTeams();
		int getSource();
		void isImpossibleCall();
	private:
		
};

#endif