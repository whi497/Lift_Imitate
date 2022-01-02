#pragma once
#include"user.h"
#include"class.h"
#include"datatype.h"
using namespace std;

extern int tofloor;

class ConCenter {
public:
	Time Ltime[2];//电梯事件时间表
	Time Ctime;//系统时间时间表
	LiftN Lift[2];//两个电梯
	QueneList** List;//乘客排队队列
	LiftStack* Stack[2];//电梯中的乘客栈
	LiftROrder RunOrder[2];//电梯目的楼层表
	int** Call;//楼层请求

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
