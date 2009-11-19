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
private:
	//--- Autre ---
	HANDLE winSemaphore;

	//--- Méthodes ---
public:
	MSMutex(bool);
	~MSMutex();
	bool waitForUnlock(int);
	void unlock();
	HANDLE getHandle();
private:

};

#endif