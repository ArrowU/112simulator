#ifndef _LOGGER_H
#define _LOGGER_H

#include "Call.h"

class Logger
{
	//--- Attributs ---
private:
	Logger instance

	//--- Méthodes ---
public:
	Logger();
	~Logger();
	Logger getInstance();
	void log(Call);
private:

};

#endif