#include "CallCenter.h"

CallCenter::CallCenter()
{
	nursingHomeBuffer=new MSBuffer<Call>(512);
	schoolBuffer=new MSBuffer<Call>(512);
	privateIndividualBuffer=new MSBuffer<Call>(512);
	// --- Start pipe ---
	// --- Start operators ---
}