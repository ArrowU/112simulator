#ifndef _OPERATOR_H
#define _OPERATOR_H


class Operator
{
	//--- Attributs ---
private:
	int id;
	int callCount;

	//--- Méthodes ---
public:
	Operator(int);
	~Operator();
	int getId();
private:

};

#endif