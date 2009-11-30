#include "CallObject.h"

#include <iostream>
using namespace std;

CallObject::CallObject()
{
}

CallObject::CallObject(int m_source, int m_team, int m_medic, int m_car, int m_helicopter) : source(m_source), team(m_team), medic(m_medic), car(m_car), helicopter(m_helicopter)
{
	cout<<source<<" "<<team<<" "<<medic<<" "<<car<<" "<<helicopter<<endl;
}

CallObject::~CallObject()
{
}

int CallObject::getSource()
{
	return source;
}

int CallObject::getTeam()
{
	return team;
}

int CallObject::getMedic()
{
	return medic;
}

int CallObject::getCar()
{
	return car;
}

int CallObject::getHelicopter()
{
	return helicopter;
}