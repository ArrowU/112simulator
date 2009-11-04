#ifndef _CALLCENTER_H
#define _CALLCENTER_H

#include "MSBuffer.h"
#include "Call.h"

class CallCenter
{
	//--- Attributs ---
private:
	MSBuffer<Call> nursingHomeBuffer;
	MSBuffer<Call> schoolBuffer;
	MSBuffer<Call> privateIndividualBuffer;
	//--- M�thodes ---
public:
	CallCenter();
	~CallCenter();
	Call getNextCall();
private:

};

#endif