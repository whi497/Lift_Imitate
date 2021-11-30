#pragma once
#include"user.h"

//****************************************************************************************//时间表
class Time
{
public:
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
	Status timeret(){intertime=0;givetime=0;inouttime=0;utime=0;dtime=0;opendotime=0;checdotime=0;backtime=0;return OK;}
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
	// int D1;
	// int D2;
	// int D3;
	int State;
	int arState;//电梯优先运行方向
	int Rstate;//上升或下降用于判断加速减速平稳运行的状态
	int Ostate;//待机与否状态
public:
	int waitstate;//到达目的楼层运行状态
	// int upfloor;//将上行目的楼层
	// int downfloor;//将下行目的楼层
	LiftN();
	//私有成员获取与置数
	int Liftret(int i);
	int& get_Floor() { return Floor; }
	int& get_state() { return State; }
	int& get_arState() { return arState;}
	int& get_Rstate() { return Rstate; }
	int& get_Ostate() { return Ostate; }
	Status change_state(int s) { State = s; return OK; }
	Status change_arState(int s) { arState = s; return OK;}
	Status change_Rstate(int s) { Rstate = s; return OK; }
	Status change_Ostate(int s) { Ostate = s; return OK; }
	//
	Status UpFloor();
	Status DownFloor();
	Status Back();
	Status Waitin() { State = Idle; return OK; }
	Status Opendoor();
	Status Closedoor(); 
};

typedef struct H {//指令节点
	int F;
	int arrow;
	struct H* next;
	H();
}*pHNode;

struct LiftROrder {//指令链表
	pHNode head;
	LiftROrder();
	int& get_arrow() { return head->next->arrow; }
	int& get_Ofloor() { return head->next->F; }
	Status change_arrow(int ar){ head->next->arrow = ar; return OK; }
	Status OrderInsert(int n,int ar );//根据楼层方向智能插入指令链表
	Status OrderDone();
	Status OrderClear();
	int OrderNull();
};


