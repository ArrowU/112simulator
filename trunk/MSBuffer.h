#ifndef _MSBUFFER_H
#define _MSBUFFER_H

#include <vector>
#include "MSMutex.h"

template <class T> 
class MSBuffer
{
	//--- Attributs ---
private:
	//T[] queue;
	int readIndex;
	MSMutex threadSafeLock;
	MSMutex emptyLock;


	//--- Méthodes ---
public:
	MSBuffer();
	~MSBuffer();
	void addElement(T);
	T getElement();
};

#endif