#ifndef _CALLCENTER_H
#define _CALLCENTER_H

#include "Call.h"
#include "MSBuffer.h"

class CallCenter
{
	//--- Attributs ---
private:
	MSBuffer<Call> *nursingHomeBuffer;
	MSBuffer<Call> *schoolBuffer;
	MSBuffer<Call> *privateIndividualBuffer;
	MSSemaphore *callSemaphore;
	//--- Méthodes ---
public:
	CallCenter();
	~CallCenter();
	Call* getNextCall();
	void addCall(Call *);
private:

};

#endif