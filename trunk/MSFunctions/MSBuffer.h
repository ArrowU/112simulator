#ifndef _MSBUFFER_H
#define _MSBUFFER_H

#include <stdio.h>
#include "MSMutex.h"
#include "MSSemaphore.h"

template <class T> 
class MSBuffer
{
	//--- Attributs ---
	//--- Constantes statiques ---
public:
	static const int WAIT_FOR_ELEMENT = 1;
	static const int RETURN_NULL_IF_EMPTY = 0;
private:
	T** queue;
	int readIndex;
	int writeIndex;
	int currentSize;
	int maxSize;
	MSMutex *threadSafeLock;
	MSSemaphore *emptyLock;
	MSSemaphore *fullLock;


	//--- Méthodes ---
public:
	MSBuffer(int);
	~MSBuffer();
	void addElement(T*);
	T* getElement(int);
	int getCurrentSize();
	int getMaxSize();
	bool isEmpty();
	bool isFull();
	MSMutex getThreadSafeLock();
	MSSemaphore getFullLock();
	MSSemaphore getEmptyLock();

};

template <class T> 
MSBuffer<T>::MSBuffer(int size)
{
	//printf("Creating MSBuffer\n");
	//queue=new std::queue<T>;
	threadSafeLock=new MSMutex(MSMutex::START_LOCKED); // Le Mutex est bloquant
	emptyLock=new MSSemaphore(size,MSSemaphore::START_EMPTY); // Le sémaphore est bloquant lors de sa création
	fullLock=new MSSemaphore(size,MSSemaphore::START_FULL); // Le sémaphore est non bloquant lors de sa création
	//printf("MSBuffer Mutex and Semaphores created\n"); 

	maxSize=size;
	currentSize=0;
	readIndex=0;
	writeIndex=0;
	queue= new T*[size];

	threadSafeLock->unlock();
}

template <class T> 
void MSBuffer<T>::addElement(T* element)
{
	if(fullLock->waitForUnlock(-1))
	{
		if(threadSafeLock->waitForUnlock(-1))
		{
			queue[writeIndex]=element;
			writeIndex++;
			writeIndex=writeIndex%maxSize;
			currentSize++;
		}
		else
	{
		printf("Error while adding element to the queue in MSBuffer : threadSafeLock wait failed \n");
        system("pause");
	}
	}
	else
	{
		printf("Error while adding element to the queue in MSBuffer : fullLock wait failed \n");
        system("pause");
	}
	emptyLock->unlock(1);
	threadSafeLock->unlock();
}


template <class T> 
T* MSBuffer<T>::getElement(int mode=WAIT_FOR_ELEMENT)
{
	T* element;
	if(mode==WAIT_FOR_ELEMENT){
		if(emptyLock->waitForUnlock(-1))
		{
			if(threadSafeLock->waitForUnlock(-1))
			{
				element=queue[readIndex];
				readIndex++;
				readIndex=readIndex%maxSize;
				currentSize--;
			}
			else
			{
				printf("Error while getting element of the queue in MSBuffer : threadSafeLock wait failed \n");
				system("pause");
			}
		}
		else
		{
			printf("Error while getting element of the queue in MSBuffer : emptyLock wait failed \n");
			system("pause");
		}
		fullLock->unlock(1);
		threadSafeLock->unlock();
		return element;
	}
	else if(mode==RETURN_NULL_IF_EMPTY)
	{
		if(emptyLock->waitForUnlock(0))
		{
			if(threadSafeLock->waitForUnlock(0))
			{
				element=queue[readIndex];
				readIndex++;
				readIndex=readIndex%maxSize;
				currentSize--;
			}
			else
			{
				printf("Error while getting element of the queue in MSBuffer : threadSafeLock wait failed \n");
				system("pause");
			}
		}
		else
		{
			return NULL;
		}
		fullLock->unlock(1);
		threadSafeLock->unlock();
		return element;
	}
}

template <class T> 
int MSBuffer<T>::getMaxSize()
{
	return maxSize;
}

template <class T> 
int MSBuffer<T>::getCurrentSize()
{
	return currentSize;
}

template <class T> 
bool MSBuffer<T>::isEmpty()
{
	bool empty;
	if(threadSafeLock.waitForUnlock())
	{
		if(currentSize==0) empty=true;
		else empty=false;
	}
	else
	{
		printf("Error while checking emptiness in MSBuffer : threadSafeLock wait failed \n");
		system("pause");
	}
	threadSafeLock.unlock();
	return empty;
}

template <class T> 
bool MSBuffer<T>::isFull()
{
	bool full;
	if(threadSafeLock.waitForUnlock())
	{
		if(currentSize==maxSize) full=true;
		else full=false;
	}
	else
	{
		printf("Error while checking fullness in MSBuffer : threadSafeLock wait failed \n");
		system("pause");
	}
	threadSafeLock.unlock();
	return full;
}

template <class T> 
MSMutex MSBuffer<T>::getThreadSafeLock()
{
	return threadSafeLock;
}

template <class T> 
MSSemaphore MSBuffer<T>::getFullLock()
{
	return fullLock;
}

template <class T> 
MSSemaphore MSBuffer<T>::getEmptyLock()
{
	return emptyLock;
}


#endif