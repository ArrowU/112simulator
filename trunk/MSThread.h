#ifndef _MSTHREAD_H
#define _MSTHREAD_H

#include <windows.h>

class MSThread
{
	//--- Attributs ---
public:
	//--- Constantes statiques ---
	static const int PRIORITY_BELOW_NORMAL = 1;
	static const int PRIORITY_NORMAL = 2;
	static const int PRIORITY_ABOVE_NORMAL = 3;
private:
	//--- Autres ---
	HANDLE quitEvent;
	HANDLE T;
	int m_priority;

	//--- Méthodes ---
protected:	
	MSThread(int); // Constructeur en protected -> classe abstraite
	~MSThread(void);

public:
	void run();
	void pause();
	void resume();
	int getPriority();
	void setPriority(int);
	bool waitForFinish(int);
	HANDLE getHandle();
	virtual void start();	
};
#endif