#ifndef _MSMUTEX_H
#define _MSMUTEX_H

#include "windows.h"

class MSMutex
{
	//--- Attributs ---
private:
	HANDLE winSemaphore;

	//--- M�thodes ---
public:
	MSMutex(DWORD);
	~MSMutex();
	bool waitForUnlock(int);
	void unlock();
private:

};

#endif