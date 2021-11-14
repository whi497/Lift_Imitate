#include"control.h"

Person* ConCenter::peoarrive(int i,float &t)
{
	Person* p=NULL;
	p = CrPerson(i, t);
	cout<<"第"<<p->get_ID()<<"号乘客将在第"
	    <<p->get_InFloor()<<"层排队等待乘坐电梯，准备前往第"
		<<p->get_OutFloor()<<"层楼"<<endl;
	cout<<"下一位乘客将在"<<t<<"时前来"<<endl;
	return p;
}

Status ConCenter::Inquene(QueneList& L, Person*& p ,int& call)
{
	L.Enquene(p);
	if (!call)call = 1;
	return OK;
}

Status ConCenter::LiftH(Person* &p)
{
	if (distList_Peo(Lift[0], p) <= distList_Peo(Lift[1], p))
		RunOrder[0].OrderInsert(p->get_InFloor(), p->get_arrow());
	else
		RunOrder[1].OrderInsert(p->get_InFloor(), p->get_arrow());
	return OK;
}

Status ConCenter::LiftRun(float t)
{
	if (RunOrder[0].head->next && RunOrder[1].head->next)return OK;
	if (Lift[0].get_state() == GoingUp) {
		if (Lift[0].get_Rstate() == preste) {
			Ltime.utime = t + uptime + prestetime;
			Lift[0].change_Rstate(steady);
		}
		if (abs(Lift[0].get_Floor() - RunOrder[0].get_Ofloor()) == 1) {
			Ltime.utime += prestetime;
		}
		if (Lift[0].get_Floor() - RunOrder[0].get_Ofloor() == 0) {
			Lift[0].change_state(Idle);
			Lift[0].waitstate = 0;
		}
		if (t == Ltime.utime) {
			Lift[0].UpFloor();
			Ltime.utime += uptime;
		}
	}
	if (Lift[0].get_state() == Idle) {
		switch (Lift[0].waitstate) {
		case 0: Lift[0].waitstate = 1; Ltime.opendotime = timeopen; Ltime.inouttime = t + 1; break;
		case 1: if (t == Ltime.opendotime) {
			if (peoinout(Stack[0][Lift[0].get_Floor()], List[Lift[0].get_Floor()][RunOrder[0].get_arrow()], t, 0) & (t - Ltime.inouttime > 30)) {
				Lift->waitstate = 2;
				Ltime.clodotime = t + closetime;
			}
		}break;
		case 2: if (t == Ltime.clodotime) {
			if (RunOrder[0].head->next == NULL) {
				Ltime.backtime = t + 30;
				Lift->waitstate = 3;
			}
			else {
				if (RunOrder[0].get_arrow() == up)Lift[0].change_state(GoingUp);
				if (RunOrder[0].get_arrow() == down)Lift[0].change_state(GoingDown);
				Lift[0].change_Rstate(preste);
			}
		}
		case 3: if (t == Ltime.backtime) {
			if (Lift[0].get_Floor() == 0);
			if (Lift[0].get_Floor() != 0) {
				Lift[0].change_state(GoingDown);
			}
		} break;
		default:exit(ERROR);
		}
		RunOrder[0].OrderDone();
	}
	return OK;
}


int ConCenter::peoinout(LiftStack& S, QueneList& L, int num, float t)
{
	int check = 0;
	if (Ltime.inouttime == t) {
		if (S.top != S.base) {
			S.Pop();
			Ltime.inouttime = iotime;
			check = 1;
		}
		else if (L.checknull()) {
			Person* P=L.Dequene();
			Stack[num][P->get_OutFloor()].Push(P);
			Ltime.inouttime = iotime;
			check = 1;
		}
	}
	return check;
}

int distList_Peo(LiftN& L, Person* &p)
{
	int distance=0;
	if (L.get_state() != p->get_arrow())
		distance = L.get_Floor() + p->get_InFloor();
	if (L.get_state() == p->get_arrow()) {
		if ((p->get_InFloor()+1 - L.get_Floor()) * p->get_arrow())
			distance = (p->get_InFloor() - L.get_Floor()) * p->get_arrow();
		else
			distance = 8 + (p->get_InFloor() - L.get_Floor()) * p->get_arrow();
	}
	return distance;
}

Status ConCenter::CheckOrder(){
	if(!RunOrder[0].OrderNull()){
		if(Lift[0].get_Floor()==RunOrder[0].get_Ofloor()&&Lift[0].get_state()==RunOrder[0].get_arrow()){
			RunOrder[0].OrderDone();
		}
	}
	if(!RunOrder[1].OrderNull()){
		if(Lift[1].get_Floor()==RunOrder[1].get_Ofloor()&&Lift[1].get_state()==RunOrder[1].get_arrow()){
			RunOrder[1].OrderDone();
		}
	}
}