#include "MSFileSystem.h"

#include "windows.h"

#include <strsafe.h>
#include <sys/stat.h>

void MSFileSystem::deleteDirectory(LPCTSTR dir)
{
	TCHAR szDir[MAX_PATH+1];  // +1 for the double null terminate
	SHFILEOPSTRUCTW fos = {0};

	StringCchCopy(szDir, MAX_PATH, dir);
	int len = lstrlenW(szDir);
	szDir[len+1] = 0; // double null terminate for SHFileOperation

	// delete the folder and everything inside
	fos.wFunc = FO_DELETE;
	fos.pFrom = szDir;
	fos.fFlags = FOF_NO_UI;
	SHFileOperation( &fos );
}

void MSFileSystem::createDirectory(LPCTSTR dir)
{
	if(!CreateDirectory(dir,NULL))
		printf("CreateDirectory : Erreur (%d)\n", GetLastError());

}

void MSFileSystem::createFile(LPCTSTR filePath)
{
	HANDLE fileHandle = CreateFile(
	  filePath,
	  GENERIC_READ | GENERIC_WRITE ,
	  0,
	  NULL,
	  1,
	  FILE_ATTRIBUTE_NORMAL,
	  NULL
	);
	CloseHandle(fileHandle);
}

void MSFileSystem::createLink(LPCTSTR source,LPCTSTR destination)
{
	CreateSymbolicLink(
		source,
		destination,
		0
	);
}

bool MSFileSystem::exists(LPCTSTR dir)
{
	DWORD attr = GetFileAttributes(dir);

	if(attr != INVALID_FILE_ATTRIBUTES)
		return true;
	else
		return false;
}