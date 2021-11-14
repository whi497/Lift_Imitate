#pragma once
#include"user.h"

//****************************************************************************************//时间表
struct Time
{
	float intertime;
	float givetime;

	float inouttime;

	float utime;
	float dtime;

	float opendotime;
	float checdotime;
	float clodotime;

	float backtime;
	Time();
};
//****************************************************************************************//乘客类
typedef class passanger {
private:
	int ID;
	int InFloor;
	int OutFloor;
	float GiveupTime;
	int arrow;
public:
	passanger();
	passanger(int a,float t);
	int& get_arrow() { return arrow; }
	int& get_InFloor() { return InFloor; }
	int& get_OutFloor() { return OutFloor; }
	int& get_ID(){return ID;}
	int timein_check(float t);
	friend class waitingquene;
	friend class Head;
	friend class LiftStack;
}Person;

Person* CrPerson(int i, float &t);

//****************************************************************************************//电梯类
class LiftN {
private:
	int Floor;
	int D1;
	int D2;
	int D3;
	int State;
	int Rstate;
public:
	int waitstate;
	int upfloor;
	int downfloor;
	LiftN();
	int get_Floor() { return Floor; }
	int get_state() { return State; }
	int get_Rstate() { return Rstate; }
	Status change_Rstate(int s) { Rstate = s; return OK; }
	Status change_state(int s) { State = s; return OK; }
	Status UpFloor();
	Status DownFloor(int n);
	Status Back();
	Status Waitin() { State = Idle; return OK; }
	Status Opendoor();
	Status Closedoor(); 

};

typedef struct H {
	int F;
	int arrow;
	struct H* next;
	H();
}*pHNode;

struct LiftROrder {
	pHNode head;
	LiftROrder();
	int get_arrow() { return head->next->arrow; }
	int get_Ofloor() { return head->next->F; }
	Status OrderInsert(int n,int sta);
	Status OrderDone();
	int OrderNull();
};

int CrRandom(int min, int max);