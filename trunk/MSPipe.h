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
	std::string name;
	int mode;
	int bufferSize;

	//--- Méthodes ---
public:
	MSPipe(std::string,int);
	~MSPipe();
	void create();
	MSPipeInstance* getNextConnection();
	void setMode(int);
	int getMode();
	void setBufferSize(int);
	int getBufferSize();
private:
	std::wstring s2ws(const std::string&);

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
	std::string read();
	void write(std::string);
	void close();
private:
};

#endif