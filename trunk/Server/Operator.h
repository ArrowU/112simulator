#ifndef _OPERATOR_H
#define _OPERATOR_H

#include "MSMutex.h"
#include "MSThread.h"

class CallCenter;
class RessourceManager;

class Operator : public MSThread
{
	//--- Attributs ---
private:
	int id;
	CallCenter *callCenter;
	RessourceManager *ressourceManager;
	int callCount;
	bool callAborted;
	MSMutex* callWaitingForRessources;

	//--- Méthodes ---
public:
	Operator(int,CallCenter*);
	~Operator();
	void start();
	int getId();
	CallCenter* getCallCenter();
	int getCallCount();
	void incrementCallCount();
	void setRessourceManager(RessourceManager*);
	RessourceManager* getRessourceManager();
	void currentCallAborted();
	void currentCallReadyToStart();
private:

};

#endif