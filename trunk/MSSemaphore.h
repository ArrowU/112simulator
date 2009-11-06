#ifndef _MSSEMAPHORE_H
#define _MSSEMAPHORE_H

#include "windows.h"

class MSSemaphore
{
	//--- Attributs ---
public:
	//--- Constantes statiques ---
	static const int START_FULL = -1;
	static const int START_EMPTY = 0;
private:
	//--- Autre ---
	HANDLE winSemaphore;

	//--- Méthodes ---
public:
	MSSemaphore(int,int);
	~MSSemaphore();
	bool waitForUnlock(int);
	void unlock(int);
	HANDLE getHandle();
private:

};

#endif