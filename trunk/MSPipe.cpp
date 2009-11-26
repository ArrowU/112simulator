#include "MSPipe.h"

MSPipe::MSPipe(std::string name, int mode=READ_WRITE)
{
	this->name=name;
	this->mode=mode;
	this->bufferSize=512;
}

void MSPipe::create()
{
	DWORD dwBufferSize=bufferSize;

	//CString cName=name.c_str();
    //LPCSTR lpszPipename = name.c_str();

	std::string s=name;

	#ifdef UNICODE
	std::wstring stemp = s2ws(s); // Temporary buffer is required	
	LPCWSTR resultName = stemp.c_str();
	#else
	LPCWSTR resultName = s.c_str();
	#endif

	winPipe=CreateNamedPipe( 
          resultName,             // pipe name 
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

MSPipeInstance* MSPipe::getNextConnection()
{
	MSPipeInstance* instance;
	bool fConnected = ConnectNamedPipe(winPipe, NULL);
	if(fConnected)
	{
		instance=new MSPipeInstance(this,winPipe);
	}
	else
	{
		printf("Pipe connection error: %d\n", GetLastError());
        exit(-1);
	}
	return instance;
}

std::wstring MSPipe::s2ws(const std::string& s)
{
 int len;
 int slength = (int)s.length() + 1;
 len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
 wchar_t* buf = new wchar_t[len];
 MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
 std::wstring r(buf);
 delete[] buf;
 return r;
}

MSPipeInstance::MSPipeInstance(MSPipe *parent, HANDLE handle)
{
	this->parentPipe=parent;
	this->hPipe=handle;
}

void MSPipeInstance::write(std::string message)
{
	const char* pcharMsg=message.c_str();
	BOOL writeResul= WriteFile(
		hPipe,
		pcharMsg,
		sizeof(pcharMsg),
		NULL,
		NULL
	);		
}

std::string MSPipeInstance::read()
{
	char* buffer=new char[parentPipe->getBufferSize()];
	BOOL readResul= ReadFile(
		hPipe,
		buffer,
		sizeof(buffer),
		NULL,
		NULL
	);	
	std::string message(buffer);
	return message;
}