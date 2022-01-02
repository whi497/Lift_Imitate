#pragma once
#include"user.h"	
#include"class.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
using namespace std;

extern int tofloor;

//****************************************************************************************//乘客队列
typedef class waitquene//节点
{
public:
	Person* Pe;
	class waitquene* next;
	waitquene();
}QNode,*Pquene;

typedef class Head{
	Pquene front;
	Pquene rear;
public:
	Head();
	int checknull() { if (front->next == NULL)return 0; else return 1; }
	Status Enquene(Person* &P);
	Person* Dequene();
	Status Giveup();
	Status timeout_check(float t);
}QueneList;


//****************************************************************************************//乘客栈
typedef class Nstack {//节点
public:
	Person* p;
	class Nstack* next;
}*NS;

class LiftStack {
public:
	NS base;
	NS top;
	int  num;
	LiftStack();
	Status Push(Person*& P);
	Status Pop();
};    



