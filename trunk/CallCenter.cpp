#include "CallCenter.h"
#include "Operator.h"
#include <stdio.h>

CallCenter::CallCenter()
{
	printf("Starting Call Center\n");
	nursingHomeBuffer=new MSBuffer<Call>(512);
	schoolBuffer=new MSBuffer<Call>(512);
	privateIndividualBuffer=new MSBuffer<Call>(512);
	// --- Start pipe ---
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