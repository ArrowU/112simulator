#include "MSPipe.h"

MSPipe::MSPipe(LPCTSTR name, int mode=READ_WRITE)
{
	this->name=name;
	this->mode=mode;
	this->bufferSize=512;
}

void MSPipe::create()
{
	DWORD dwBufferSize=bufferSize;
/*
	//CString cName=name.c_str();
    //LPCSTR lpszPipename = name.c_str();

	std::string s=name;

	#ifdef UNICODE
	std::wstring stemp = s2ws(s); // Temporary buffer is required	
	LPCWSTR resultName = stemp.c_str();
	#else
	LPCWSTR resultName = s.c_str();
	#endif
	*/

	winPipe=CreateNamedPipe( 
          name,             // pipe name 
          PIPE_ACCESS_DUPLEX,       // read/write access 
          PIPE_TYPE_MESSAGE |       // message type pipe 
          PIPE_READMODE_MESSAGE |   // message-read mode 
          PIPE_WAIT,                // blocking mode 
          PIPE_UNLIMITED_INSTANCES, // max. instances  
          dwBufferSize,                  // output buffer size 
          dwBufferSize,                  // input buffer size 
          0,                        // client time-out 
          NULL);                    // default security attribute 	
} 

int MSPipe::getBufferSize()
{
	return bufferSize;
}

HANDLE MSPipe::getHandle()
{
	return winPipe;
}

MSPipeInstance* MSPipe::connect(LPCTSTR pipeName)
{
	MSPipe* myPipe=new MSPipe(pipeName);
	HANDLE myHandle = CreateFile( 
         pipeName,   // pipe name 
         GENERIC_READ |  // read and write access 
         GENERIC_WRITE, 
         0,              // no sharing 
         NULL,           // default security attributes
         OPEN_EXISTING,  // opens existing pipe 
         0,              // default attributes 
         NULL);          // no template file 

	if(myHandle!=INVALID_HANDLE_VALUE)
	{
		MSPipeInstance* myPipeInstance=new MSPipeInstance(myPipe,myHandle);
		return myPipeInstance;
	}
	else
	{
		printf("Pipe connection error: %d\n", GetLastError());
        exit(-1);
		return NULL;
	}
}


MSPipeInstance* MSPipe::getNextConnection()
{
	MSPipeInstance* instance;
	BOOL fConnected = ConnectNamedPipe(winPipe, NULL)? 
         TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 

	if(fConnected)
	{
		instance=new MSPipeInstance(this,winPipe);
	}
	else
	{
		printf("Pipe connection error: %d\n", GetLastError());
        //exit(-1);
	}
	return instance;
}

MSPipeInstance::MSPipeInstance(MSPipe *parent, HANDLE handle)
{
	this->parentPipe=parent;
	this->hPipe=handle;
}

void MSPipeInstance::write(LPCVOID data,int size)
{
	BOOL writeResult= WriteFile(
		hPipe,
		data,
		size,
		NULL,
		NULL
	);
	if(writeResult==false)
	{
		printf("PipeInstance write error: %d\n", GetLastError());
        exit(-1);
	}
}

void MSPipeInstance::read(LPVOID data,int size)
{
	BOOL readResult= ReadFile(
		hPipe,
		data,
		size,
		NULL,
		NULL
	);	
	if(readResult==false)
	{
		printf("PipeInstance read error: %d\n", GetLastError());
        exit(-1);
	}
}