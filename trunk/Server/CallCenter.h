#ifndef _CALLCENTER_H
#define _CALLCENTER_H

# include "MSBuffer.h"
# include "MSSemaphore.h"

class Call;

class CallCenter
{
	//--- Attributs ---
private:
	MSBuffer<Call> *nursingHomeBuffer;
	MSBuffer<Call> *schoolBuffer;
	MSBuffer<Call> *privateIndividualBuffer;
	MSSemaphore *callSemaphore;
	//--- M�thodes ---
public:
	CallCenter();
	~CallCenter();
	Call* getNextCall();
	void addCall(Call *);
private:

};

#endif