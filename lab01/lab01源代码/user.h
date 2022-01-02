#pragma once
//状态
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//时间常量
//运行状态
#define GoingUp 0
#define GoingDown 1
#define Idle -1
#define reset -2
//待机以及上升下降状态
#define WAIT 0
#define RUN 1
#define preste 1
#define steady 0
#define goingstop  -1

#define timewide 1
#define timego 1
#define timeopen 1
#define iotime 1
#define closetime 1
#define awaittime 30
//超时
#define timein 1
#define timeout 0
//方向
#define up 0
#define down 1
//上身下降时间
#define uptime 1
#define downtime 1
#define prestetime 1

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;
typedef int Status;

inline Status printline(){//打印事件分割线
    cout<<"*********************************"<<endl;
    return OK;
}

// inline Status arrow_conculate(int in, int to){
//     if(in==to)return Idle;
//     else{
//         if(in>to)return down;
//         else return up;
//     }
// }

inline int arrow_conculate(int in, int to){
    if(in==to) return Idle;
    else {
        if(in>to) return down;
        else return up;
    }
}

inline int CrRandom(int min, int max) {//产生随机数
	int a;
	srand((unsigned)time(NULL));
	a = rand() % (max + 1) + min;
	return a;
}