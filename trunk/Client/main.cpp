#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "../Server/Call.h"
#include "MSPipe.h"

using namespace std;

void commandLine();
void interpret(string command);
void readCalls(vector<string> command);
void sendCallFromCommand(vector<string>);
void sendCall(CallInfo);
void help();
void exit();
void strSplit(vector<string>& vecteur, string chaine, char separateur);
CallInfo infoFromInt(int, int, int, int);

int main()
{
	printf("Starting 112 Client !\n");
	commandLine();
	//connection au pipe
	return(0);
}

void commandLine()
{
	printf("Welcome, please type help to view availavable commands\n");
	while(true)
	{
		printf("\n> ");
		string command;
		std::getline(std::cin, command);
		//cin>>command;
		interpret(command);
	}
}

void interpret(string command)
{
	vector<string> commandTokens;
	strSplit(commandTokens,command,' ');

	if(commandTokens[0].compare("help")==0) 
		help();
	else if(commandTokens[0].compare("load")==0)
		readCalls(commandTokens);
	else if(commandTokens[0].compare("send")==0)
		sendCallFromCommand(commandTokens);
	else if(commandTokens[0].compare("exit")==0) 
		exit();
	else printf("Invalid Command, please type help to view available commands\n");
}

void help()
{
	printf("\n");
	printf("exit : closes the program\n");
	printf("load [file] : loads the content of [file] and sends it to the server\n");
	printf("send [source] [ambulances] [medics] [choppers] : sends the call to the server\n");
}

void exit()
{
	exit(EXIT_SUCCESS);
}

void strSplit(vector<string>& vecteur, string chaine, char separateur)
{
	vecteur.clear();
	string::size_type stTemp = chaine.find(separateur);
	while(stTemp != string::npos)
	{
		vecteur.push_back(chaine.substr(0, stTemp));
		chaine = chaine.substr(stTemp + 1);
		stTemp = chaine.find(separateur);
	}
	vecteur.push_back(chaine);
}

void readCalls(vector<string> command)
{
	//lecture des données et envoi
	const char * filename=command[1].c_str();
	ifstream file(filename, ios::in);
	if(file)
    {
		printf("Parsing File ");
		printf(filename);
		printf("\n");
		int source, choppers, ambulances, medics;
		int count=0;
		while(file>>source>>ambulances>>medics>>choppers)
		{
			count++;

			//= new Call(choppers, ambulances, medics, teams, source);
			CallInfo info=infoFromInt(source,ambulances,medics,choppers);
			
			printf(" Sending Call %d ...\n",count);
			sendCall(info);
			printf("...Call %d sent \n",count);
			//myInstance->close();
			//delete myInstance;
		}
		file.close();
    }
	else
		printf("Failed to open the file!");
}

void sendCallFromCommand(vector<string> command)
{
	int source=atoi(command[1].c_str());
	int ambulances=atoi(command[2].c_str());
	int medics=atoi(command[3].c_str());
	int choppers=atoi(command[4].c_str());
	CallInfo info=infoFromInt(source,ambulances,medics,choppers);
	sendCall(info);
	printf("Call sent \n");
}

CallInfo infoFromInt(int source, int ambulances, int medics ,int choppers)
{
	int teams = ambulances + choppers;
	medics = medics + choppers;
	CallInfo testInfo;
	testInfo.requiredAmbulances=ambulances;
	testInfo.requiredChoppers=choppers;
	testInfo.requiredMedics=medics;
	testInfo.requiredTeams=teams;
	testInfo.source=source;
	return testInfo;
}

void sendCall(CallInfo info)
{
	MSPipeInstance* myInstance=MSPipe::connect(TEXT("\\\\.\\pipe\\mynamedpipe"));
	myInstance->write(&info,sizeof(CallInfo));
}