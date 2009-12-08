#ifndef _OPERATOR_H
#define _OPERATOR_H

#include "CallCenter.h"
#include "RessourceManager.h"
#include "Call.h"

class CallCenter;
class RessourceManager;

class Operator
{
	//--- Attributs ---
private:
	int id;
	CallCenter *callCenter;
	RessourceManager *ressourceManager;
	int callCount;

	//--- Méthodes ---
public:
	Operator(int,CallCenter*);
	~Operator();
	int getId();
	CallCenter* getCallCenter();
	int getCallCount();
	void incrementCallCount();
	void setRessourceManager(RessourceManager*);
	RessourceManager* getRessourceManager();
private:

};

#endif