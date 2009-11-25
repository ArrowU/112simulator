#include "CallCenter.h"
#include "Operator.h"
#include "MSPipe.h"
#include "MSThread.h"
#include <stdio.h>

class CallCenterPipeManagerThread : public MSThread
{
private:
	MSPipe* pipe;
public:
	CallCenterPipeManagerThread();
	void start();
	void setPipe(MSPipe*);
};

CallCenterPipeManagerThread::CallCenterPipeManagerThread()
{
}

void CallCenterPipeManagerThread::setPipe(MSPipe* pipe)
{
	this->pipe=pipe;
}

void CallCenterPipeManagerThread::start()
{
	while(1)
	{
		pipe->create();
		MSPipeInstance* newInstance=pipe->getNextConnection();
		printf("New connection\n");
	}
}

CallCenter::CallCenter()
{
	printf("Starting Call Center\n");
	nursingHomeBuffer=new MSBuffer<Call>(512);
	schoolBuffer=new MSBuffer<Call>(512);
	privateIndividualBuffer=new MSBuffer<Call>(512);
	// --- Start pipe ---
	MSPipe* myPipe;
	myPipe=new MSPipe(TEXT("\\\\.\\pipe\\mynamedpipe"),MSPipe::READ_WRITE);
	//myPipe->create();

	CallCenterPipeManagerThread* myPipeManagerThread=new CallCenterPipeManagerThread();
	myPipeManagerThread->setPipe(myPipe);
	myPipeManagerThread->run();

	// --- Start operators ---
	Operator* op=new Operator(1,this);
}

CallCenter::~CallCenter()
{
}

Call* CallCenter::getNextCall()
{
	return new Call();
}