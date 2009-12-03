#include "MSThread.h"
#include <stdio.h>

MSThread::MSThread()
{
	m_priority=PRIORITY_NORMAL;
}

MSThread::MSThread(int priority=PRIORITY_NORMAL)
{
	m_priority=priority;
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

void MSThread::setPriority(int priority)
{
	m_priority=priority;
	if(T!=NULL)
	{
		switch (m_priority)		//on fixe la priorite du thread
		{	
			case PRIORITY_BELOW_NORMAL:
				SetThreadPriority(T, THREAD_PRIORITY_BELOW_NORMAL);
				break;
			case PRIORITY_NORMAL:
				SetThreadPriority(T, THREAD_PRIORITY_NORMAL);
				break;
			case PRIORITY_ABOVE_NORMAL:
				SetThreadPriority(T, THREAD_PRIORITY_ABOVE_NORMAL);
				break;
			default:
				SetThreadPriority(T, THREAD_PRIORITY_NORMAL);
				break;
		}
	}
}

int MSThread::getPriority()
{
	return m_priority;
}

void MSThread::run(void)
{
	T = CreateThread(NULL, 0, MyThread, this, CREATE_SUSPENDED, NULL); // thread créé mais pas lancé
	if(T!=NULL){
		setPriority(m_priority); // on fixe la priorité
		ResumeThread(T);	//on lance le thread
	}
	else
	{
		printf("MSThread run() error : Thread handle not created in class MSSemaphore: %d\n", GetLastError());
		system("pause");
	}
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
