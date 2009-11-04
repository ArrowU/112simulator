#ifndef _MSMUTEX_H
#define _MSMUTEX_H

#include "windows.h"

class MSMutex
{
	//--- Attributs ---
private:
	//--- Constantes statiques ---
	static const bool START_LOCKED = false;
	static const bool START_UNLOCKED = true;

	//--- Autre ---
	HANDLE winSemaphore;

	//--- Méthodes ---
public:
	MSMutex(bool);
	~MSMutex();
	bool waitForUnlock(int);
	void unlock();
private:

};

#endif