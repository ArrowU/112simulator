//#ifndef _MSTHREAD_H
//#define _MSTHREAD_H
//
//#include "windows.h"
//
///*** 
//Si il y a un bien un truc qui me fait CHIER c'est de voir des DWORD, WINAPI, HANDLE, LPVOID et LPDATA a tout bout de champ.
//comme il faut que les fonctions qui éxécutent les thread soient de la forme 
//"DWORD WINAPI maFonctionThread(LPVOID params)"
//tu imagines comme ca me casse les couilles. Donc avec ces deux petits typedef, les fonctions qui éxécutent des MSThread seront de la forme :
//"MSThreadCallback maFonctionThread(MSThreadParameters params)"
//c'est un peu plus long à écrire, mais au moins c'est joli, c'est clair, on a la classe, 
//et j'arrive à dormir la nuit. Pour le reste, ca change rien :D
//***/
//typedef DWORD WINAPI MSThreadCallback
//typedef LPVOID MSThreadParameters
//
//class MSThread
//{
//	//--- Attributs ---
//private:
//	HANDLE threadHandle;
//
//	//--- Méthodes ---
//public:
//	MSThread(MSThreadCallback, // Pointeur vers la fonction qui va éxécuter le thread (le joli nom c'est callback :) )
//		MSThreadParameters, // Paramètres passés à cette fonction
//		bool // True => le thread démarre dés qu'il est créé False => le thread attend un appel à la fonction start(). Et on ajoute un valeur par défaut a true pour faire joli
//		);
//	~MSThread();
//	void start(); // Si le thread attendait le signal => il démarre, sinon ne fait rien
//	void pause(); // Pause le thread => cf focntion SuspendThread sur le MSDN
//	void resume(); // Reprend l'éxécution la ou ca s'est arrete. Cf focntion ResumeThread sur le MSDN
//	void setPriority(int); // devine...
//	int getPriority(); // ...sans déconner...
//	bool waitForFinish(int); // Indice : waitForSingleObject sur le MSDN
//	HANDLE getHandle(); // Notre objectif est d'aider le dév, pas d'empecher un type de faire ce qu'il veut => on lui permet d'avoir un acces directe a l'objet windows si il veut...
//private:
//
//};
//
//#endif

#ifndef _MSTHREAD_H
#define _MSTHREAD_H

#include <windows.h>

class MSThread
{
	//--- Attributs ---
private:
	HANDLE quitEvent;
	HANDLE T;
	int m_priority;

	//--- Méthodes ---
public:
	MSThread(void);
	MSThread(int priority);
	~MSThread(void);
	void run();
	void pause();
	void resume();
	int getPriority();
	void setPriority(int);
	bool waitForFinish(int);
	HANDLE getHandle();
	virtual void start();	
};
#endif