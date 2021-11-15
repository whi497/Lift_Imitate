#pragma once
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define timewide 1
#define timego 1
#define timeopen 2
#define iotime 1
#define closetime 4
#define awaittime 30
//超时
#define timein 1
#define timeout 0
#define up 0
#define down 1
//上身下降时间
#define uptime 3
#define downtime 4
#define prestetime 2
//运行状态
#define GoingUp 0
#define GoingDown 1
#define Idle -1
//待机以及上升下降状态
#define WAIT 0
#define RUN 1
#define preste 1
#define steady 0
#define stop  -1

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;
typedef int Status;

Status printlint(){
    cout<<"*********************************"<<endl;
    return OK;
}