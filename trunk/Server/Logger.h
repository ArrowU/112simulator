#ifndef _LOGGER_H
#define _LOGGER_H

#include "Call.h"
#include <vector>

class Logger 
{
	public :
		Logger();
		virtual void log(Call*);
};

class LogManager : public Logger
{
	//--- Attributs ---
private:
	static LogManager* instance;
	//LogManager* LogManager::instance=NULL;
	std::vector<Logger*>* loggerList;

	//--- Méthodes ---
public:
	LogManager();
	~LogManager();
	static LogManager* getInstance();
	void log(Call*);
private:

};

class FileSystemLogger : public Logger
{
	//--- Attributs ---
private:

	//--- Méthodes ---
public:
	FileSystemLogger();
	~FileSystemLogger();
	void log(Call*);
private:
};


#endif