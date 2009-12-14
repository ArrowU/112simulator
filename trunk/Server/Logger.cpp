#include "Logger.h"

#include <vector>
#include <string>
#include <sstream>

#include "MSFileSystem.h"
#include "MSBuffer.h"

#include "Operator.h"
#include "Ressource.h"

Logger::Logger()
{
}

void Logger::log(Call * call)
{
}

LogManager* LogManager::instance=NULL;

LogManager::LogManager()
{
	loggerList=new std::vector<Logger*>();
	loggerList->push_back(new FileSystemLogger());

	MSFileSystem::deleteDirectory(TEXT(".\\Log"));

	MSFileSystem::createDirectory(TEXT(".\\Log"));
	MSFileSystem::createDirectory(TEXT(".\\Log\\Ressources"));
	MSFileSystem::createDirectory(TEXT(".\\Log\\Calls"));
}

LogManager* LogManager::getInstance()
{
	if(instance==NULL){
		instance = new LogManager();
	}
	return instance;
}

void LogManager::log(Call* call)
{
	for(int i=0;i<(int) loggerList->size();i++)
	{
		Logger* logger = loggerList->at(i);
		logger->log(call);
	}
}

FileSystemLogger::FileSystemLogger()
{
}

void FileSystemLogger::log(Call * call)
{
	//printf("Logging Call");
	
	// --- Répertoire Opérateux x ---
	std::basic_string<wchar_t> baseDir = TEXT(".\\Log\\Calls");
	std::basic_string<wchar_t> op = TEXT("\\Operator ");

	int opId = call->getOperator()->getId();
	// Toi aussi, profites des joies du C++ Microsoft way...
	std::basic_stringstream<wchar_t> StrStream;
	StrStream << opId;
	std::basic_string<wchar_t> nbs = StrStream.str();
	op.append(nbs);
	std::basic_string<wchar_t> opDir;
	opDir=baseDir;
	opDir.append(op);

	if( ! MSFileSystem::exists(opDir.c_str()))
		MSFileSystem::createDirectory(opDir.c_str());
	// --- End ---

	// --- Creation du répertoire de l'appel ---
	baseDir=opDir;
	std::basic_string<wchar_t> appel = TEXT("\\Call ");
	int callCount = call->getOperatorCallCount();
	// Toi aussi, profites des joies du C++ Microsoft way...
	std::basic_stringstream<wchar_t> StrStream2;
	StrStream2 << callCount;
	std::basic_string<wchar_t> nbs2 = StrStream2.str();
	appel.append(nbs2);
	std::basic_string<wchar_t> callDir;
	callDir=baseDir;
	callDir.append(appel);

	if( ! MSFileSystem::exists(callDir.c_str()))
		MSFileSystem::createDirectory(callDir.c_str());

	// --- Creation des liens symboliques ---
	std::basic_string<wchar_t> ressourceBaseDir = TEXT(".\\Log\\Ressources");
	std::basic_string<wchar_t> ressourceType;
	MSBuffer<Ressource>* usedRessource=call->getUsedRessources();
	for(int i=0;i<usedRessource->getCurrentSize();i++)
	{
		Ressource* ressource=usedRessource->at(i);
		int type = ressource->getType();
		if(type==Ressource::AMBULANCE)
			ressourceType = TEXT("\\Ambulance ");
		else if(type==Ressource::MEDIC)
			ressourceType = TEXT("\\Medic ");
		else if(type==Ressource::TEAM)
			ressourceType = TEXT("\\Team ");
		else if(type==Ressource::CHOPPER)
			ressourceType = TEXT("\\Helicopter ");
		int ressourceId=ressource->getId();

		std::basic_string<wchar_t> ressourceName=ressourceType;
		// Toi aussi, profites des joies du C++ Microsoft way...
		std::basic_stringstream<wchar_t> StrStream3;
		StrStream3 << ressourceId;
		std::basic_string<wchar_t> nbs3 = StrStream3.str();
		ressourceName.append(nbs3);
		std::basic_string<wchar_t> ressourceDir;
		ressourceDir=ressourceBaseDir;
		ressourceDir.append(ressourceName);

		if( ! MSFileSystem::exists(ressourceDir.c_str()))
		MSFileSystem::createFile(ressourceDir.c_str());

		std::basic_string<wchar_t> linkSourceDir=callDir;
		linkSourceDir.append(ressourceName);

		MSFileSystem::createLink(linkSourceDir.c_str(),ressourceDir.c_str());
	}

}







