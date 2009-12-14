#ifndef _MSFILESYSTEM_H
#define _MSFILESYSTEM_H

#include "windows.h"

class MSFileSystem
{
	//--- Attributs ---
public:
	//--- Constantes statiques ---
private:
	//--- Autre ---

	//--- Méthodes ---
public:
	static void deleteDirectory(LPCTSTR);
	static void createDirectory(LPCTSTR);
	static void createFile(LPCTSTR);
	static void createLink(LPCTSTR,LPCTSTR);
	static bool exists(LPCTSTR);
private:
	//static BOOL IsDots(const TCHAR* str);

};

#endif
