#include"control.h"

Person* ConCenter::peoarrive(int i,float &t)
{
	Person* p=NULL;
	p = CrPerson(i, t);
	Call[p->get_InFloor()][p->get_arrow()]=1;
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

Status ConCenter::LiftH()
{
	int ar=-1;
	int u=FindCalluphighest(Lift[0].get_Floor());
	int d=FindCalldownlowest(Lift[0].get_Floor());
	int u1=-1, d1=-1;
	if(Lift[0].get_arState()==up){
		u1=FindCalluphighest(Lift[1].get_Floor(),0,Lift[0].get_Floor()-1);
		d1=FindCalldownlowest(Lift[1].get_Floor(),0,Lift[1].get_Floor()-1);
	}
	else{
		u1=FindCalluphighest(Lift[1].get_Floor(),Lift[0].get_Floor()+1,4);
		d1=FindCalldownlowest(Lift[1].get_Floor(),Lift[0].get_Floor()+1,4);
	}
	if(Lift[0].get_state()!=reset){
		if(u==-1&&d==-1)return OK;
		// if(RunOrder[0].OrderNull()&&u==-1&&d==-1&&Lift[0].waitstate){
		// 	Lift[0].change_state(reset);
		// 	return OK;
		// }
		if(Lift[0].get_Ostate()==WAIT){
			Lift[0].change_Ostate(RUN);
			if(u!=-1){
				ar=arrow_conculate(0,u);
				RunOrder[0].OrderInsert(u,ar);
				Lift[0].change_state(arrow_conculate(0,u));
				Lift[0].change_arState(up);
			}
			cout<<"一号电梯启动！"<<endl;
		}
		else{
			if(Lift[0].get_arState()==up){
				if(RunOrder[0].OrderNull()){
					if(u == -1 || u == Lift[0].get_Floor()){
						Lift[0].change_arState(down);
						if(u == Lift[0].get_Floor()){
						RunOrder[0].OrderInsert(Lift[0].get_Floor(),down);
						}
					}
					else RunOrder[0].OrderInsert(u,up);
				}
			}
			else {
				if(RunOrder[0].OrderNull()){
					if((d == -1) || (d == Lift[0].get_Floor())){
						Lift[0].change_arState(up);
						if(d == Lift[0].get_Floor()){
						RunOrder[0].OrderInsert(Lift[0].get_Floor(),up);
						}
					}
					else RunOrder[0].OrderInsert(d,down);
				}
			}
		}
	}
	if(Lift[1].get_state()==reset)return OK;
	else{
		if(u1==-1&&d1==-1)return OK;
		if(Lift[1].get_Ostate()==WAIT){
			Lift[1].change_Ostate(RUN);
			if(u!=-1){
				ar=arrow_conculate(0,u1);
				RunOrder[1].OrderInsert(u1,ar);
				Lift[1].change_state(arrow_conculate(0,u1));
				Lift[1].change_arState(up);
			}
			cout<<"二号电梯启动！"<<endl;
		}
		else{
			if(Lift[1].get_arState()==up){
				if(RunOrder[1].OrderNull()){
					if(u1 == -1 || u1 == Lift[1].get_Floor()){
						Lift[1].change_arState(down);
						if(u1 == Lift[1].get_Floor()){
						RunOrder[1].OrderInsert(Lift[1].get_Floor(),down);
						}
					}
					else RunOrder[1].OrderInsert(u1,up);
				}
			}
			else {
				if(RunOrder[1].OrderNull()){
					if(d1 == -1 || d1 == Lift[1].get_Floor()){
						Lift[1].change_arState(up);
						if(d1 == Lift[1].get_Floor()){
						RunOrder[1].OrderInsert(Lift[1].get_Floor(),up);
						}
					}
					else RunOrder[1].OrderInsert(d1,down);
				}
			}
		}
	}
	
	// int u=FindFirCallup();
	// int d=FindFirCalldown();
	// if (distList_Peo(Lift[0], p) <= distList_Peo(Lift[1], p)){
	// 	// if(p->get_InFloor()==Lift[0].get_Floor()){RunOrder[0].OrderInsert(p->get_InFloor(),Lift[0].get_Floor(),p->get_arrow());}
	// 	// else{
	// 		// RunOrder[0].OrderInsert(p->get_InFloor(), Lift[0].get_Floor());		
	// 		// if(p->get_arrow()!=arrow_conculate(Lift[0].get_Floor(),p->get_InFloor()))
	// 		// 	RunOrder[0].OrderInsert(p->get_InFloor(),Lift[0].get_Floor(),p->get_arrow());
	// 	// }
	// 	if(RunOrder[0].OrderNull()){
	// 		if(Lift[0].get_arState()==up){
	// 			if(u!=-1&&u>Lift[0].get_Floor()){RunOrder[0].OrderInsert(u,up);}
	// 			else {
	// 				if(u!=-1&&u<Lift[0].get_Floor()){
	// 					if(d!=-1)
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// else{
	// 	// if(p->get_InFloor()==Lift[0].get_Floor()){RunOrder[0].OrderInsert(p->get_InFloor(),Lift[0].get_Floor(),p->get_arrow());}
	// 	// else{
	// 	// RunOrder[1].OrderInsert(p->get_InFloor(), Lift[1].get_Floor());
	// 	// if(p->get_arrow()!=arrow_conculate(Lift[1].get_Floor(),p->get_InFloor()))
	// 	// 	RunOrder[1].OrderInsert(p->get_InFloor(),Lift[1].get_Floor(),p->get_arrow());
	// 	// }
	// }
	// LiftIni();//对处于待命状态且有状态待完成的电梯初始化
	return OK;
}

Status ConCenter::LiftRun(float t,int i)
{
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
		else{
			if(Call[Lift[i].get_Floor()][Lift[i].get_arState()]==1){
				Lift[i].change_state(Idle);
				Lift[i].change_Rstate(preste);	
				Ltime[i].timeret();
				Lift[i].waitstate = 0;
			}
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
		else{
			if(Call[Lift[i].get_Floor()][Lift[i].get_arState()]==1){
				Lift[i].change_state(Idle);
				Lift[i].change_Rstate(preste);	
				Ltime[i].timeret();
				Lift[i].waitstate = 0;
			}
		}
	}
	if (Lift[i].get_state() == Idle) {//执行电梯在楼层停顿及乘客进出指令
		switch (Lift[i].waitstate) {
		case 0: Lift[i].waitstate = 1; Ltime[i].opendotime = t+timeopen; Ltime[i].inouttime = t + timeopen + 1;
				Call[Lift[i].get_Floor()][Lift[i].get_arState()]=0; break;
		case 1: if (t >= Ltime[i].opendotime) {
			if (!peoinout(Stack[i][Lift[i].get_Floor()], List[Lift[i].get_Floor()][Lift[i].get_arState()], i, t) && (t - Ltime[i].inouttime >= 1)) {
				Lift[i].waitstate = 2;
				Ltime[i].clodotime = t + closetime;
				if(Lift[i].get_Floor()==RunOrder[i].get_Ofloor())RunOrder[i].OrderDone();
			}
		}break;
		case 2: if (t >= Ltime[i].clodotime) {
			if (RunOrder[i].OrderNull()) {
				Ltime[i].backtime = t + 5;
				Lift[i].waitstate = 3;
			}
			else {
				if (RunOrder[i].get_Ofloor()==Lift[i].get_Floor()){
					Lift[i].waitstate=1;Ltime[i].inouttime =t + iotime;
					Call[Lift[i].get_Floor()][Lift[i].get_arState()]=0;
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
			RunOrder[i].OrderInsert(P->get_OutFloor(), P->get_arrow());
			Ltime[i].inouttime += iotime;
			check = 1;
		}
	}
	return check;
}

// int distList_Peo(LiftN& L, Person* &p)
// {
// 	int distance=0;
// 	if (L.get_state() != p->get_arrow())
// 		distance = L.get_Floor() + p->get_InFloor();
// 	if (L.get_state() == p->get_arrow()) {
// 		if ((p->get_InFloor()+1 - L.get_Floor()) * p->get_arrow())
// 			distance = (p->get_InFloor() - L.get_Floor()) * p->get_arrow();
// 		else
// 			distance = 8 + (p->get_InFloor() - L.get_Floor()) * p->get_arrow();
// 	}
// 	return distance;
// }

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

int ConCenter::CheckCall(){ 
	for(int j = 0; j < 2; j++){
		for(int i = 0; i< 5; i++) {
			if(Call[i][j]==1)return 1;
		}
	}
	return 0;
}

int ConCenter::FindCalluphighest(int h,int low,int high){ //找到最高请求楼层
	int temp= -1;
	int htemp= -1;
	if(low>high)return temp;
	if(h>=low)htemp=h;
	else htemp=low;
	for(int i = htemp ; i < high+1; i++){
		for(int j = 0;j<2; j++){
			if(Call[i][j]==1){ 
				if(i>temp)temp=i;
			}
		}
	}
	return temp;
}

int ConCenter::FindCalldownlowest(int h,int low,int high){ //找到最低请求楼层
	int temp= -1;
	int htemp= -1;
	if(low>high)return temp;
	if(h<=high)htemp=h;
	else htemp=high;
	for(int i = htemp ; i >low-1; i--){
		for(int j = 0;j<2; j++){
			if(Call[i][j]==1){ 
				temp=h;
				if(i<temp)temp=i;
			}
		}
	}
	return temp;
}

Status ConCenter::peplgiveup_check(float& t){ 
	for(int i = 0; i <2;i++){
		for(int j = 0;j<5; j++){
			if(Call[i][j]==1){
				List[i][j].timeout_check(t);
			}
		}
	}
	return OK;
}