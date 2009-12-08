#include "Ressource.h"

Ressource::Ressource(int type_m, int id_m) : type(type_m), id(id_m)
{
}

int Ressource::getId()
{
	return id;
}

int Ressource::getType()
{
	return type;
}