#include "CallCenter.h"
#include "Operator.h"
#include "MSPipe.h"
#include "MSThread.h"
#include "Call.h"
#include <stdio.h>


///////////////////////////
// PIPE INSTANCE MANAGER //
///////////////////////////
class PipeInstanceManagerThread : public MSThread
{
private:
	MSPipeInstance* pipeInstance;
	CallCenter* callCenter;
public:
	PipeInstanceManagerThread();
	void start();	
	void setPipeInstance(MSPipeInstance*);
	void setCallCenter(CallCenter*);
};

PipeInstanceManagerThread::PipeInstanceManagerThread()
{
}

void PipeInstanceManagerThread::setPipeInstance(MSPipeInstance *pipeInstance)
{
	this->pipeInstance=pipeInstance;
}

void PipeInstanceManagerThread::setCallCenter(CallCenter* callCenter)
{
	this->callCenter=callCenter;
}

void PipeInstanceManagerThread::start()
{
	Call * myCall=new Call();
	pipeInstance->read(myCall,sizeof(Call));
	//printf("Valeur recue : %d",myInt);
	//int choppers = myCall->getRequiredChoppers();
	//printf("Helicos : %d",choppers);
	callCenter->addCall(myCall);
	// Fermeture du pipe instance
}

//////////////////
// PIPE MANAGER //
//////////////////

class CallCenterPipeManagerThread : public MSThread
{
private:
	MSPipe* pipe;
	CallCenter* callCenter;
public:
	CallCenterPipeManagerThread();
	void start();
	void setPipe(MSPipe*);
	void setCallCenter (CallCenter*);
};

CallCenterPipeManagerThread::CallCenterPipeManagerThread()
{
}

void CallCenterPipeManagerThread::setPipe(MSPipe* pipe)
{
	this->pipe=pipe;
}

void CallCenterPipeManagerThread::setCallCenter(CallCenter* callCenter)
{
	this->callCenter=callCenter;
}

void CallCenterPipeManagerThread::start()
{
	while(1)
	{
		pipe->create();
		MSPipeInstance* newInstance=pipe->getNextConnection();
		//printf("New connection\n");
		PipeInstanceManagerThread *myPipeInstanceThread= new PipeInstanceManagerThread();
		myPipeInstanceThread->setPipeInstance(newInstance);
		myPipeInstanceThread->setCallCenter(callCenter);
		myPipeInstanceThread->run();
	}
}

/////////////////
// CALL CENTER //
/////////////////
CallCenter::CallCenter()
{
	printf("Starting Call Center\n");
	nursingHomeBuffer=new MSBuffer<Call>(512);
	schoolBuffer=new MSBuffer<Call>(512);
	privateIndividualBuffer=new MSBuffer<Call>(512);
	callSemaphore=new MSSemaphore(3*512,MSSemaphore::START_EMPTY);
	
	// --- Start Ressource Manager ---
	RessourceManager *ressourceManager=new RessourceManager();

	// --- Start pipe ---
	MSPipe* myPipe;
	myPipe=new MSPipe(TEXT("\\\\.\\pipe\\mynamedpipe"));

	CallCenterPipeManagerThread* myPipeManagerThread=new CallCenterPipeManagerThread();
	myPipeManagerThread->setPipe(myPipe);
	myPipeManagerThread->setCallCenter(this);
	myPipeManagerThread->run();

	// --- Start operators ---
	for(int i=0;i<3;i++){
		Operator* op=new Operator(i,this);
		op->setRessourceManager(ressourceManager);
	}
}

CallCenter::~CallCenter()
{
}

Call* CallCenter::getNextCall()
{
	Call* call;
	callSemaphore->waitForUnlock(-1);
	call=nursingHomeBuffer->getElement(MSBuffer<Call>::RETURN_NULL_IF_EMPTY);
	if(call!=NULL){ return call; }
	else call=schoolBuffer->getElement(MSBuffer<Call>::RETURN_NULL_IF_EMPTY);
	if(call!=NULL){ return call; }
	else call=privateIndividualBuffer->getElement(MSBuffer<Call>::RETURN_NULL_IF_EMPTY);
	if(call!=NULL){ return call; }
	else{
		printf("CallCenter - getNextCall : Pas d'appel pour l'opérateur malgré le sémaphore unlocké");
		system("pause");
		return NULL;
	}

}

void CallCenter::addCall(Call* call)
{
	int source=call->getSource();
	if(source==Call::NURSING_HOME) nursingHomeBuffer->addElement(call);
	else if(source==Call::SCHOOL) schoolBuffer->addElement(call);
	else if(source==Call::PRIVATE_INDIVIDUAL) privateIndividualBuffer->addElement(call);
	else {
		printf("CallCenter - addCall : origine de l'appel inconnue");
		system("pause");
	}
	callSemaphore->unlock(1);
}