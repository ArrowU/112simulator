#ifndef _MSMUTEX_H
#define _MSMUTEX_H

#include "windows.h"

class MSMutex
{
	//--- Attributs ---
public:
	//--- Constantes statiques ---
	static const bool START_LOCKED = true;
	static const bool START_UNLOCKED = false;
	static const int WAIT_INFINITE = -1;
private:
	//--- Autre ---
	HANDLE winSemaphore;

	//--- M�thodes ---
public:
	MSMutex(bool);
	~MSMutex();
	bool waitForUnlock(int);
	void unlock();
	HANDLE getHandle();
private:

};

#endif