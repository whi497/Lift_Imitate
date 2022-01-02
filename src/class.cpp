#include"class.h"

passanger::passanger()
{
	ID = 0;
	InFloor = 0;
	OutFloor = 0;
	GiveupTime = 0;
	arrow = 0;
}

passanger::passanger(int a,float t)
{
	ID = a;
	// InFloor=0;    //调试使用
	// OutFloor = 3;
	InFloor = CrRandom(0,tofloor-1);
	do 
		OutFloor = CrRandom(0, tofloor-1);
    while (OutFloor == InFloor);//防止目的楼层与进入楼层相同
	GiveupTime = t + CrRandom(8, 20) * timewide;
	if (OutFloor > InFloor)arrow = up;
	else arrow = down;
}



int passanger::timein_check(float t)
{
	if (t >= GiveupTime)
		return timeout;
	else return timeout;
}

Person* CrPerson(int i,float &t)
{
	Person* per = new Person(i, t);
	if (!per)exit(OVERFLOW);
	t += CrRandom(10, 15) * timewide;
	// t+= 11;调试使用
	return per;
}

LiftN::LiftN()
{
	Floor = 0;
	// D1 = 0;
	// D2 = 0;
	// D3 = 0;
	State = Idle;
	arState= up;
	Rstate = preste;
	Ostate = WAIT;
	waitstate = 0;
	// upfloor = 0;
	// downfloor = 0;
}

int LiftN::Liftret(int i){ 
	Floor = 0;
	// D1 = 0;
	// D2 = 0;
	// D3 = 0;
	State = Idle;
	arState= up;
	Rstate = preste;
	Ostate = WAIT;
	waitstate = 0;
	// upfloor = 0;
	// downfloor = 0;
	cout<<i+1<<"号电梯复位！"<<endl;
	return 0;
}

H::H()
{
	F = -1;
	arrow = 0;
	next = NULL;
}

LiftROrder::LiftROrder()
{
	head = new H;
	if (!head)exit(OVERFLOW);
}


Status LiftROrder::OrderInsert(int n,int ar)
{
	pHNode pfind=head;
	if(!pfind)exit(OVERFLOW);
	// if(ar==-2)ar=arrow_conculate(L,n);
	if (!pfind->next) {
		pHNode p = new H;
		p->F = n;
		p->next = pfind->next;
		pfind->next = p;
		p->arrow = ar;
		return OK;
	}
	if (pfind->next->arrow == up) {
		while (pfind) {
			if(!pfind->next){
				pHNode p = new H;
				p->F = n;
				p->arrow=ar;
				p->next = NULL;
				pfind->next = p;
				break;
			}
			else{ 
				if(n==pfind->next->F)return OK;
				if(n<pfind->next->F) {
					pHNode p = new H;
					if(!p)exit(OVERFLOW);
					p->F = n;
					p->arrow=ar;
					p->next = pfind->next;
					pfind->next = p;
				}
				else pfind = pfind->next;
			}
		}
	}
	else {
		while (pfind) {
			if(!pfind->next){
				pHNode p = new H;
				p->F = n;
				p->arrow=ar;
				p->next = NULL;
				pfind->next = p;
				break;
			}
			else{ 
				if(n==pfind->next->F)return OK;
				if(n>pfind->next->F) {
					pHNode p = new H;
					if(!p)exit(OVERFLOW);
					p->F = n;
					p->arrow=ar;
					p->next = pfind->next;
					pfind->next = p;
					break;
				}
				else pfind = pfind->next;
			}
		}
	}
	// while (pfind->next->arrow != ar ){
	// 	pfind = pfind->next;
	// 	if(!pfind->next)break;
	// }
	// if(!pfind->next){
	// 	pHNode p = new H;
	// 	p->F = n;
	// 	p->arrow=ar;
	// 	p->next = NULL;
	// 	pfind->next = p;
	// }
	// else{ 
	// 	if (pfind->next->arrow == up) {
	// 		while (pfind) {
	// 			if(!pfind->next){
	// 				pHNode p = new H;
	// 				p->F = n;
	// 				p->arrow=ar;
	// 				p->next = NULL;
	// 				pfind->next = p;
	// 			}
	// 			else{ 
	// 				if(n==pfind->next->F)return OK;
	// 				if(n<pfind->next->F) {
	// 					pHNode p = new H;
	// 					if(!p)exit(OVERFLOW);
	// 					p->F = n;
	// 					p->arrow=ar;
	// 					p->next = pfind->next;
	// 					pfind->next = p;
	// 				}
	// 				else pfind = pfind->next;
	// 			}
	// 		}
	// 	}
	// 	if (pfind->next->arrow == down) {
	// 		while (pfind) {
	// 			if(!pfind->next){
	// 				pHNode p = new H;
	// 				p->F = n;
	// 				p->arrow=ar;
	// 				p->next = NULL;
	// 				pfind->next = p;
	// 			}
	// 			else{ 
	// 				if(n==pfind->next->F)return OK;
	// 				if(n>pfind->next->F) {
	// 					pHNode p = new H;
	// 					if(!p)exit(OVERFLOW);
	// 					p->F = n;
	// 					p->arrow=ar;
	// 					p->next = pfind->next;
	// 					pfind->next = p;
	// 				}
	// 				else pfind = pfind->next;
	// 			}
	// 		}
	// 	}
	// }
	return OK;
}

Status LiftROrder::OrderDone()
{
	pHNode p = head->next;
	head->next = p->next;
	delete p;
	return OK;
}

int LiftROrder::OrderNull(){
	if(head->next)return 0;
	else return 1;
}

Status LiftROrder::OrderClear(){
	if(!OrderNull())OrderDone();
	return OK;
}

Time::Time()
{
	intertime = givetime = utime = dtime = 0;
	opendotime = checdotime = clodotime = backtime = 0;
	inouttime = 0;
}

