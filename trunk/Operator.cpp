#include "Operator.h"
#include "MSThread.h"
#include <stdio.h>

// --- Classe OperatorThread ---
class OperatorThread : public MSThread
{
	private :
		Operator *myOperator;

	public: 
		OperatorThread();
		void start();
		void setOperator(Operator*);
};

OperatorThread::OperatorThread()
{
}

void OperatorThread::start()
{
	//while(true)
	//{
		Call *call = myOperator->getCallCenter()->getNextCall();
		myOperator->incrementCallCount();
		call->setOperatorId(myOperator->getId());
		call->setOperatorCallCount(myOperator->getCallCount());
		printf("Je l'ai eu");
		// --- Crée le Thread de chargement des ressource au ressourceManager ---
	//}
}

void OperatorThread::setOperator(Operator* op)
{
	myOperator=op;
}
// --- END ---



Operator::Operator(int id,CallCenter* callCenter)
{
	//printf("Operator starting\n");
	this->id=id;
	this->callCenter=callCenter;
	callCount=0;
	OperatorThread *opThread=new OperatorThread();
	opThread->setOperator(this);
	opThread->run();
}

Operator::~Operator()
{
}

CallCenter* Operator::getCallCenter()
{
	return callCenter;
}

int Operator::getCallCount()
{
	return callCount;
}

void Operator::incrementCallCount()
{
	callCount++;
}

int Operator::getId()
{
	return id;
}