#include <iostream>
#include <fstream>

#include "../Server/Call.h"
#include "MSPipe.h"

using namespace std;

int main()
{
	//connection au pipe

	//lecture des données et envoi
	ifstream file("calls.txt", ios::in);
	if(file)
    {
		int source, choppers, ambulances, medics;
		while(file>>source>>ambulances>>medics>>choppers)
		{
			int teams = ambulances + choppers;
			medics = medics + choppers;

			CallInfo testInfo;
			testInfo.requiredAmbulances=ambulances;
			testInfo.requiredChoppers=choppers;
			testInfo.requiredMedics=medics;
			testInfo.requiredTeams=teams;
			testInfo.source=source;

			//= new Call(choppers, ambulances, medics, teams, source);
			cout<<"envoi ok de la source "<<source<<endl;

			//envoi vers le pipe
			MSPipeInstance* myInstance=MSPipe::connect(TEXT("\\\\.\\pipe\\mynamedpipe"));
			myInstance->write(&testInfo,sizeof(CallInfo));
			//myInstance->close();
			//delete myInstance;
		}
		file.close();
    }
	else
		cout << "failed to open the file!" << endl;

	system("pause");
	return(0);
}