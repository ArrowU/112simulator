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
	//--- Méthodes ---
public:
	CallCenter();
	~CallCenter();
	Call* getNextCall();
private:

};

#endif