#ifndef _LOGGER_H
#define _LOGGER_H

#include "Call.h"

class Logger
{
	//--- Attributs ---
private:
	Logger instance

	//--- M�thodes ---
public:
	Logger();
	~Logger();
	Logger getInstance();
	void log(Call);
private:

};

#endif