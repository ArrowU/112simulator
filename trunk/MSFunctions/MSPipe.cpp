#include "MSPipe.h"

MSPipe::MSPipe(LPCTSTR name)
{
	this->name=name;
	//this->mode=mode;
}

void MSPipe::create()
{
	//DWORD dwBufferSize=bufferSize;
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
	int test=0;
	hPipe = CreateNamedPipe( 
          name,             // pipe name 
          PIPE_ACCESS_DUPLEX,       // read/write access 
          PIPE_TYPE_MESSAGE |       // message type pipe 
          PIPE_READMODE_MESSAGE |   // message-read mode 
          PIPE_WAIT,                // blocking mode 
          PIPE_UNLIMITED_INSTANCES, // max. instances  
          BUFSIZE,                  // output buffer size 
          BUFSIZE,                  // input buffer size 
          0,                        // client time-out 
          NULL);                    // default security attribute 

	test=1;
} 

HANDLE MSPipe::getHandle()
{
	return hPipe;
}

MSPipeInstance* MSPipe::connect(LPCTSTR pipeName)
{
	//MSPipe* myPipe=new MSPipe(pipeName);
	HANDLE myHandle = CreateFile( 
         pipeName,   // pipe name 
         GENERIC_READ |  // read and write access 
         GENERIC_WRITE, 
         0,              // no sharing 
         NULL,           // default security attributes
         OPEN_EXISTING,  // opens existing pipe 
         0,              // default attributes 
         NULL);          // no template file 
	
	if (myHandle != INVALID_HANDLE_VALUE){	
		DWORD dwMode = PIPE_READMODE_MESSAGE|PIPE_WAIT; 
		
		BOOL fSuccess = SetNamedPipeHandleState( 
		myHandle,    // pipe handle 
		&dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 
		
		if(fSuccess==TRUE)
		{
			MSPipeInstance* myPipeInstance=new MSPipeInstance(myHandle);
			return myPipeInstance;
		}
		else
		{
			printf("Pipe connection error, could not change pipe Mode: %d\n", GetLastError());
			exit(-1);
			return NULL;
		}
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
	MSPipeInstance* instance=NULL;
	BOOL fConnected = ConnectNamedPipe(hPipe, NULL)? 
         TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 

	if(fConnected)
	{
		instance=new MSPipeInstance(hPipe);
	}
	else
	{
		printf("Pipe connection error: %d\n", GetLastError());
        //exit(-1);
	}
	return instance;
}

MSPipeInstance::MSPipeInstance(HANDLE handle)
{
	//this->parentPipe=parent;
	this->hPipe=handle;
	int test=0;
}

void MSPipeInstance::write(LPCVOID data,int size)
{
	DWORD written;
	  BOOL writeResult= WriteFile(
		hPipe,
		data,
		size,
		&written,
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
	DWORD read;
	BOOL readResult= ReadFile(
		hPipe,
		data,
		size,
		&read,
		NULL
	);	
	if(readResult==false)
	{
		printf("PipeInstance read error: %d\n", GetLastError());
        exit(-1);
	}
}

HANDLE MSPipeInstance::getHandle()
{
	return hPipe;
}