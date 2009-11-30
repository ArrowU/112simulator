#ifndef DEF_CALLOBJECT
#define DEF_CALLOBJECT

class CallObject
{
public:
	CallObject();
	CallObject(int, int, int, int, int);
    ~CallObject();
	int getSource();
	int getTeam();
	int getMedic();
	int getCar();
	int getHelicopter();


private:
	int source;
	int team;
	int medic;
	int car;
	int helicopter;
};

#endif