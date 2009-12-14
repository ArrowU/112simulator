#ifndef _CALL_H
#define _CALL_H

#include "MSBuffer.h"
#include "CallInfo.h"

class Operator;
class Ressource;

class Call
{
	//--- Attributs ---
	public:
		static const int NURSING_HOME=1;
		static const int SCHOOL=2;
		static const int PRIVATE_INDIVIDUAL=3;
	private:
		int operatorCallCount;
		CallInfo info;
		Operator* myOperator;
		MSBuffer<Ressource> *ressources;
		int waitedTime;

		//--- Méthodes ---
	public:
		Call(CallInfo info);
		Call();
		~Call();
		void setOperator(Operator*);
		Operator* getOperator();
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
		void readyToStart();
		void abort();
		void addRessource( Ressource *);
		MSBuffer<Ressource>* getUsedRessources();
		Ressource *freeRessources();
		bool hasRessources();
		int getWaitedTime();
		void setWaitedTime(int);
		
};

#endif