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
	static const DWORD BUFSIZE = 512;
private:
	//--- Autre ---
	HANDLE hPipe;
	LPCTSTR name;
	int mode;
	int bufferSize;

	//--- Méthodes ---
public:
	MSPipe(LPCTSTR);
	~MSPipe();
	void create();
	MSPipeInstance* getNextConnection();
	void setMode(int);
	int getMode();
	//void setBufferSize(int);
	//int getBufferSize();
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
	MSPipeInstance(HANDLE);
	~MSPipeInstance();
	void read(LPVOID,int);
	void write(LPCVOID,int);
	HANDLE getHandle();
	void close();
private:
};

#endif