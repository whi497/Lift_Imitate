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
	InFloor = CrRandom(0,4);
	do 
		OutFloor = CrRandom(0, 4);
    while (OutFloor == InFloor);
	GiveupTime = t + CrRandom(300, 500) * timewide;
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
	t = CrRandom(50, 600) * timewide;
	return per;
}



LiftN::LiftN()
{
	Floor = 0;
	D1 = 0;
	D2 = 0;
	D3 = 0;
	State = Idle;
	Rstate = -1;
	Ostate = WAIT;
	waitstate = 0;
	upfloor = 0;
	downfloor = 0;
}

Status LiftN::UpFloor()
{
	Floor++;
	return OK;
}

Status LiftN::DownFloor()
{
	Floor--;
	return OK;
}

Status LiftN::Back()
{
	Floor = 0;
	State = Idle;
	return OK;
}

Status LiftN::Opendoor()
{
	return OK;
}

Status LiftN::Closedoor(){
	return OK;
}

int CrRandom(int min, int max) {
	int a;
	srand((unsigned)time(NULL));
	a = rand() % (max + 1) + min;
	return a;
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
	if (!pfind)exit(OVERFLOW);
	if (!pfind->next) {
		pHNode p = new H;
		p->F = n;
		p->next = pfind->next;
		pfind->next = p;
		p->arrow = ar;
		return OK;
	}
	while (pfind->next->arrow != ar)pfind = pfind->next;
	if (pfind->next->arrow == 1) {
		while (pfind) {
			if (pfind->next->F == ar)return OK;
			if (pfind->F<n && pfind->next->F>n) {
				pHNode p = new H;
				p->F = n;
				pfind->arrow=ar;
				p->next = pfind->next;
				pfind->next = p;
			}
			else pfind = pfind->next;
		}
	}
	if (pfind->arrow == -1) {
		while (pfind) {
			if (pfind->next->F == ar)return OK;
			if (pfind->F>n && pfind->next->F<n) {
				pHNode p = new H;
				if (!p)exit(OVERFLOW);
				p->F = n;
				p->next = pfind->next;
				pfind->next = p;
			}
			else pfind = pfind->next;
		}
	}
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

Time::Time()
{
	intertime = givetime = utime = dtime = 0;
	opendotime = checdotime = clodotime = backtime = 0;
	inouttime = 0;
}
