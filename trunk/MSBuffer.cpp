#include "MSBuffer.h"
#include <stdio.h>

template <class T> 
MSBuffer<T>::MSBuffer()
{
	queue=new std::queue<T>;
	threadSafeLock=new MSMutex();
	emptyLock=new MSMutex(LOCKED); // The vector is empty
}

template <class T> 
void MSBuffer<T>::addElement(T element)
{
	if(threadSafeLock.waitForUnlock())
	{
		vector.push_back(element);
	}
	else
	{
		printf("Error while adding element to the vector in MSBuffer \n");
        exit(-1);
	}
	emptyLock.unlock();
	threadSafeLock.unlock();
}

template <class T> 
T MSBuffer<T>::getElement()
{
	T element;
	if(emptyLock.waitForUnlock())
	{
		if(threadSafeLock.waitForUnlock())
		{
			element=vector.front();
			vector.
		}
		else
		{
		}
	}
	else
	{
	}
}