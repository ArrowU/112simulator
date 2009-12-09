#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

//#include "RessourceManager.h"
#include "CallCenter.h"
//#include "Operator.h"

using namespace std;

void commandLine();
void interpret(string command);
void help();
void exit();
void strSplit(vector<string>& vecteur, string chaine, char separateur);



int main()
{
	printf("Starting 112 Server : new Version !\n");
	// --- Parse Arguments ---
	// --- Start Ressource Manager ---
	// --- Start Call Center ---
	CallCenter* callCenter=new CallCenter();
	// --- Start Command Line ---
	commandLine();
	return 0;
}

void commandLine()
{
	printf("Welcome, please type help to view availavable commands\n");
	while(true)
	{
		printf("\n> ");
		string command;
		cin>>command;
		interpret(command);
	}
}

void interpret(string command)
{
	vector<string> commandTokens;
	strSplit(commandTokens,command,' ');

	if(commandTokens[0].compare("help")==0) 
		help();
	else if(commandTokens[0].compare("exit")==0) 
		exit();
	else printf("Invalid Command, please type help to view available commands\n");
}

void help()
{
	printf("\n");
	printf("exit : closes the program\n");
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
