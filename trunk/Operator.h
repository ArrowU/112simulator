#ifndef _OPERATOR_H
#define _OPERATOR_H

#include "CallCenter.h"
#include "Call.h"

class Operator
{
	//--- Attributs ---
private:
	int id;
	CallCenter *callCenter;
	int callCount;

	//--- Méthodes ---
public:
	Operator(int,CallCenter*);
	~Operator();
	int getId();
	CallCenter* getCallCenter();
	int getCallCount();
	void incrementCallCount();
private:

};

#endif