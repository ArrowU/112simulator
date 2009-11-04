#include "MSThread.h"

MSThread::MSThread(void) : m_priority(0)
{	
}

MSThread::MSThread(int priority) : m_priority(priority)
{
}

MSThread::~MSThread(void)
{
}

void MSThread::start(void)
{
}
DWORD WINAPI MyThread(LPVOID lpData)
{
	((MSThread*)lpData)->start();
	return EXIT_SUCCESS;
}

void MSThread::run(void)
{
	T = CreateThread(NULL, 0, MyThread, this, CREATE_SUSPENDED, NULL); // thread créé mais pas lancé
	switch (m_priority)		//on fixe la priorite du thread
	{	
		case 1:
			SetThreadPriority(T, THREAD_PRIORITY_BELOW_NORMAL);
			break;
		case 2:
			SetThreadPriority(T, THREAD_PRIORITY_NORMAL);
			break;
		case 3:
			SetThreadPriority(T, THREAD_PRIORITY_ABOVE_NORMAL);
			break;
		default:
			SetThreadPriority(T, THREAD_PRIORITY_NORMAL);
			break;
	}
	 ResumeThread(T);	//on lance le thread
}

bool MSThread::waitForFinish(int timeout=-1)
{
	DWORD dwTimeout;
	if(timeout<0) dwTimeout=INFINITE;
	else dwTimeout=timeout;

	bool bResult;
	if(T!=NULL)
	{
		bResult=WaitForSingleObject( T, dwTimeout);
		CloseHandle(T);
	}
	else
	{
		bResult=true;
	}

	return bResult;
}
