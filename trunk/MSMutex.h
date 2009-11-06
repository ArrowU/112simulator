#ifndef _MSMUTEX_H
#define _MSMUTEX_H

#include "windows.h"

class MSMutex
{
	//--- Attributs ---
public:
	//--- Constantes statiques ---
	static const bool START_LOCKED = false;
	static const bool START_UNLOCKED = true;
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