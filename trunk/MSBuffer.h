#ifndef _MSBUFFER_H
#define _MSBUFFER_H

#include <vector>
#include "MSMutex.h"
#include "MSSemaphore.h"

template <class T> 
class MSBuffer
{
	//--- Attributs ---
private:
	T* queue;
	int readIndex;
	int writeIndex;
	int currentSize;
	int maxSize;
	MSMutex threadSafeLock;
	MSSemaphore emptyLock;
	MSSemaphore fullLock;


	//--- Méthodes ---
public:
	MSBuffer(int);
	~MSBuffer();
	void addElement(T);
	T getElement();
	int getCurrentSize();
	int getMaxSize();
	bool isEmpty();
	bool isFull();
	MSMutex getThreadSafeLock();
	MSSemaphore getFullLock();
	MSSemaphore getEmptyLock();

};

#endif