#pragma once
#include"user.h"
#include"class.h"
#include"datatype.h"
using namespace std;

extern int tofloor;

class ConCenter {
public:
	Time Ltime[2];
	Time Ctime;
	LiftN Lift[2];
	QueneList** List;
	LiftStack* Stack[2];
	LiftROrder RunOrder[2];
	int** Call;

	ConCenter();
	Person* peoarrive(int i, float& t);
	Status peplgiveup_check(float& t);
	Status Inquene(QueneList& L, Person*& p, int& call);
	int peoinout(LiftStack& S, QueneList& L, int num, float t);
	Status LiftH();
	Status LiftRun(float t, int i);
	// Status CheckOrder();
	// Status LiftIni();
	Status scerrorO();
	int CheckCall();
	int FindCalluphighest(int h,int low=0,int high=tofloor-1);
	int FindCalldownlowest(int h,int low=0,int high=tofloor-1);
};

// int distList_Peo(LiftN& L, Person*& p);
