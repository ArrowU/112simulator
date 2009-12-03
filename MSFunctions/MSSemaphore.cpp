#include "MSSemaphore.h"
#include <stdio.h>


MSSemaphore::MSSemaphore(int maxCount,int initialCount=START_FULL)
{
	if(initialCount==START_FULL) initialCount=maxCount;
	else if(initialCount==START_EMPTY) initialCount=0;
	DWORD dwInitialCount = static_cast<DWORD>(initialCount);
	DWORD dwMaxCount = static_cast<DWORD>(maxCount);
	
	winSemaphore= CreateSemaphore( 
        NULL,           // default security attributes
        dwInitialCount,  // initial count
        dwMaxCount,  // maximum count
        NULL);

	if (winSemaphore == NULL) 
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        system("pause");
    }
}

bool MSSemaphore::waitForUnlock(int timeout=-1)
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
				printf("Semaphore wait error in class MSSemaphore: %d\n", GetLastError());
				system("pause");
				break;
    }
    return bResult;
}

void MSSemaphore::unlock(int ressourceCount=1)
{
	DWORD dwRessourceCount = static_cast<DWORD>(ressourceCount);
	bool bResult = ReleaseSemaphore(
		winSemaphore,  // handle to semaphore
        dwRessourceCount,            // increase count by ressourceCount
        NULL );       // not interested in previous count
    
	if(bResult==false)
	{
		printf("Semaphore unlock error in class MSSemaphore: %d\n", GetLastError());
		system("pause");
	}
}

HANDLE MSSemaphore::getHandle()
{
	return winSemaphore;
}