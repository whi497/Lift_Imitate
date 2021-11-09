#pragma once
#include"user.h"
#include"class.h"
#include"datatype.h"
using namespace std;

class ConCenter {
public:
	Time Ltime;
	LiftN Lift[2];
	QueneList List[5][2];
	LiftStack Stack[2][5];
	LiftROrder RunOrder[2];
	int Call[5][2];

	//ConCenter();
	Person* peoarrive(int i, float& t);
	Status Inquene(QueneList& L, Person*& p, int& call);
	int peoinout(LiftStack& S, QueneList& L, int num, float t);
	Status LiftH(Person*& p);
	Status LiftRun(float t);
};

int distList_Peo(LiftN& L, Person*& p);
