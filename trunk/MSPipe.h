#ifndef _MSPIPE_H
#define _MSPIPE_H

#include "windows.h"

#include <string>

class MSPipeInstance;

class MSPipe
{
	//--- Attributs ---
public:
	//--- Constantes statiques ---
	static const int READ_ONLY = 1;
	static const int WRITE_ONLY = 2;
	static const int READ_WRITE = 3;
private:
	//--- Autre ---
	HANDLE winPipe;
	LPCTSTR name;
	int mode;
	int bufferSize;

	//--- Méthodes ---
public:
	MSPipe(LPCTSTR,int);
	~MSPipe();
	void create();
	MSPipeInstance* getNextConnection();
	void setMode(int);
	int getMode();
	void setBufferSize(int);
	int getBufferSize();
	HANDLE getHandle();
	static MSPipeInstance* connect(LPCTSTR);
private:
	

};

class MSPipeInstance
{
		//--- Attributs ---
public:
	//--- Constantes statiques ---
private:
	//--- Autre ---
	HANDLE hPipe;
	MSPipe* parentPipe;

	//--- Méthodes ---
public:
	MSPipeInstance(MSPipe*,HANDLE);
	~MSPipeInstance();
	void read(LPVOID,int);
	void write(LPCVOID,int);
	void close();
private:
};

#endif