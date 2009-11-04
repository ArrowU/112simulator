#include "MSMutex.h"
#include <stdio.h>


MSMutex::MSMutex(bool startLocked=false)
{
	int initialCount=1;
	if(startLocked) initialCount=0;
	DWORD dwInitialCount = static_cast<DWORD>(initialCount);
	winSemaphore= CreateSemaphore( 
        NULL,           // default security attributes
        dwInitialCount,  // initial count
        1,  // maximum count
        NULL);

	if (winSemaphore == NULL) 
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        exit(-1);
    }
}

bool MSMutex::waitForUnlock(int timeout=-1)
{
	DWORD dwTimeout;

	if(timeout<0) dwTimeout=INFINITE;
	else dwTimeout=timeout;

	DWORD dwWaitResult = WaitForSingleObject(
		winSemaphore,
		dwTimeout
	);

	bool bResult;
	switch (dwWaitResult) 
    { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
                bResult=true;
                break; 

            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT: 
                bResult=false;
                break;

			// An error occured
			default:
				printf("Semaphore wait error in class MSMutex: %d\n", GetLastError());
				exit(-1);
				break;
    }
    return bResult;
}

void MSMutex::unlock()
{
	bool bResult = ReleaseSemaphore(
		winSemaphore,  // handle to semaphore
        1,            // increase count by one
        NULL );       // not interested in previous count
    
	if(bResult==false)
	{
		printf("Semaphore unlock error in class MSMutex: %d\n", GetLastError());
		exit(-1);
	}
}