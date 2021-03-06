#include"control.h"

Person* ConCenter::peoarrive(int i,float &t)
{
	Person* p=NULL;
	p = CrPerson(i, t);
	printline();
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
	if (distList_Peo(Lift[0], p) <= distList_Peo(Lift[1], p)){
		// if(p->get_InFloor()==Lift[0].get_Floor()){RunOrder[0].OrderInsert(p->get_InFloor(),Lift[0].get_Floor(),p->get_arrow());}
		// else{
			RunOrder[0].OrderInsert(p->get_InFloor(), Lift[0].get_Floor());		
			if(p->get_arrow()!=arrow_conculate(Lift[0].get_Floor(),p->get_InFloor()))
				RunOrder[0].OrderInsert(p->get_InFloor(),Lift[0].get_Floor(),p->get_arrow());
		// }
	}
	else{
		// if(p->get_InFloor()==Lift[0].get_Floor()){RunOrder[0].OrderInsert(p->get_InFloor(),Lift[0].get_Floor(),p->get_arrow());}
		// else{
			RunOrder[1].OrderInsert(p->get_InFloor(), Lift[1].get_Floor());
			if(p->get_arrow()!=arrow_conculate(Lift[1].get_Floor(),p->get_InFloor()))
				RunOrder[1].OrderInsert(p->get_InFloor(),Lift[1].get_Floor(),p->get_arrow());
		// }
	}
	return OK;
}

Status ConCenter::LiftRun(float t,int i)
{
	LiftIni();//对处于待命状态且有状态待完成的电梯初始化
	if(Lift[i].get_Ostate()==WAIT)return OK;
	if (Lift[i].get_state() == GoingUp) {//执行上升指令
		if (Lift[i].get_Rstate() == preste) {
			Ltime[i].utime = t + uptime + prestetime;
			Lift[i].change_Rstate(steady);
		}
		if (abs(Lift[i].get_Floor() - RunOrder[i].get_Ofloor()) == 1&&Lift[i].get_Rstate()==steady) {
			Ltime[i].utime += prestetime;
			Lift[i].change_Rstate(goingstop);
		}
		if (t == Ltime[i].utime) {
			Lift[i].UpFloor();
			Ltime[i].utime += uptime;
		}
		if (Lift[i].get_Floor() - RunOrder[i].get_Ofloor() == 0&&Lift[i].get_Rstate()==goingstop) {
			Lift[i].change_state(Idle);
			Lift[i].change_Rstate(preste);	
			Ltime[i].timeret();
			Lift[i].waitstate = 0;
		}
	}
	if(Lift[i].get_state() == GoingDown) {//执行下降指令
		if (Lift[i].get_Rstate() == preste) {
			Ltime[i].dtime = t + downtime + prestetime;
			Lift[i].change_Rstate(steady);
		}
		if (abs(Lift[i].get_Floor() - RunOrder[i].get_Ofloor()) == 1&&Lift[i].get_Rstate()==steady) {
			Ltime[i].dtime += prestetime;
			Lift[i].change_Rstate(goingstop);
		}
		if (t == Ltime[i].dtime) {
			Lift[i].DownFloor();
			Ltime[i].dtime += downtime;
		}
		if (Lift[i].get_Floor() - RunOrder[i].get_Ofloor() == 0&&Lift[i].get_Rstate()==goingstop) {
			Lift[i].change_state(Idle);
			Lift[i].change_Rstate(preste);
			Ltime[i].timeret();
			Lift[i].waitstate = 0;
		}
	}
	if (Lift[i].get_state() == Idle) {//执行电梯在楼层停顿及乘客进出指令
		switch (Lift[i].waitstate) {
		case 0: Lift[i].waitstate = 1; Ltime[i].opendotime = t+timeopen; Ltime[i].inouttime = t + timeopen + 1; break;
		case 1: if (t >= Ltime[i].opendotime) {
			if (!peoinout(Stack[i][Lift[i].get_Floor()], List[Lift[i].get_Floor()][RunOrder[i].get_arrow()], i, t) && (t - Ltime[i].inouttime >= 1)) {
				Lift[i].waitstate = 2;
				Ltime[i].clodotime = t + closetime;
				RunOrder[i].OrderDone();
			}
		}break;
		case 2: if (t >= Ltime[i].clodotime) {
			if (RunOrder[i].head->next == NULL) {
				Ltime[i].backtime = t + 10;
				Lift[i].waitstate = 3;
			}
			else {
				if (RunOrder[i].get_Ofloor()==Lift[i].get_Floor()){
					Lift[i].waitstate=1;Ltime[i].inouttime =t + iotime;
				}
				else{
					if (RunOrder[i].get_arrow() == up)Lift[i].change_state(GoingUp);
					if (RunOrder[i].get_arrow() == down)Lift[i].change_state(GoingDown);
				}
				break;
			}
		} break;
		case 3: if (t == Ltime[i].backtime) {
			if (Lift[i].get_Floor() == 0){Lift[i].Liftret(i);cout<<"当前时间为"<<t<<endl;}
			if (Lift[i].get_Floor() != 0) {
				Lift[i].change_state(reset);
			}
		} break;
		default:exit(ERROR);
		}
	}
	if(Lift[i].get_state() == reset) {
		if (Lift[i].get_Rstate() == preste) {
			Ltime[i].dtime = t + downtime + prestetime;
			Lift[i].change_Rstate(steady);
		}
		if (Lift[i].get_Floor() == 1&&Lift[i].get_Rstate()==steady) {
			Ltime[i].dtime += prestetime;
			Lift[i].change_Rstate(goingstop);
		}
		if (t == Ltime[i].dtime) {
			Lift[i].DownFloor();
			Ltime[i].dtime += downtime;
		}
		if (Lift[i].get_Floor() == 0&&Lift[i].get_Rstate()==goingstop) {
			Lift[i].Liftret(i);
			cout<<"当前时间为"<<t<<endl;
			Ltime[i].timeret();
		}
	}
	return OK;
}

Status ConCenter::LiftIni(){
	if(Lift[0].get_state() ==Idle&&Lift[0].get_Ostate() ==WAIT&&(!RunOrder[0].OrderNull())){
		Lift[0].change_Ostate(RUN);
		Lift[0].change_state(RunOrder[0].get_arrow());
		RunOrder[0].change_arrow(up);
		cout<<"1号电梯启动！"<<endl;
	}
	if(Lift[1].get_state() ==Idle&&Lift[1].get_Ostate() ==WAIT&&(!RunOrder[1].OrderNull())){
		Lift[1].change_Ostate(RUN);
		Lift[1].change_state(RunOrder[1].get_arrow());
		RunOrder[1].change_arrow(up);
		cout<<"2号电梯启动！"<<endl;
	}
	return OK;
}

int ConCenter::peoinout(LiftStack& S, QueneList& L, int i, float t)
{
	int check = 0;
	if (Ltime[i].inouttime == t) {
		if (S.top != S.base) {//电梯内人出栈
			S.Pop();
			cout<<"当前时间为"<<t<<endl;
			Ltime[i].inouttime += iotime;
			check = 1;
		}
		else if (L.checknull()) {//先“出”后“进”
			Person* P=L.Dequene();
			Stack[i][P->get_OutFloor()].Push(P);
			cout<<"当前时间为"<<t<<endl;
			RunOrder[i].OrderInsert(P->get_OutFloor(), Lift[i].get_Floor(), P->get_arrow());
			Ltime[i].inouttime += iotime;
			check = 1;
		}
	}
	return check;
}

Status ConCenter::peogiveup(){ 
	
}

int distList_Peo(LiftN& L, Person* &p)
{
	int distance=0;
	if(L.get_Rstate()==reset)return 100;
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

// Status ConCenter::CheckOrder(){
// 	if(!RunOrder[0].OrderNull()){
// 		if(Lift[0].get_Floor()==RunOrder[0].get_Ofloor()&&Lift[0].get_state()==RunOrder[0].get_arrow()){
// 			RunOrder[0].OrderDone();
// 		}
// 	}
// 	if(!RunOrder[1].OrderNull()){
// 		if(Lift[1].get_Floor()==RunOrder[1].get_Ofloor()&&Lift[1].get_state()==RunOrder[1].get_arrow()){
// 			RunOrder[1].OrderDone();
// 		}
// 	}
// 	return OK;
// }

