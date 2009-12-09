#ifndef _CALL_H
#define _CALL_H

#include "Ressource.h"
#include "Operator.h"
#include "MSBuffer.h"
#include "RessourceManager.h"

class Operator;

class Call
{
	//--- Attributs ---
	public:
		static const int NURSING_HOME=1;
		static const int SCHOOL=2;
		static const int PRIVATE_INDIVIDUAL=3;
	private:
		int operatorCallCount;
		int requiredChoppers;
		int requiredAmbulances;
		int requiredMedics;
		int requiredTeams;
		int source;
		Operator* myOperator;
		MSBuffer<Ressource> *ressources;

		RessourceManager *ressourceManager;

		//--- Méthodes ---
	public:
		Call(int,int,int,int,int);
		Call();
		~Call();
		void setOperator(Operator*);
		Operator* getOperatorId();
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
		void addRessource( Ressource *);
	
	private:
		void freeRessources();
		
};

#endif