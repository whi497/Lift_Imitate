#include"user.h"
#include"control.h"
#include"class.h"
#include"datatype.h"
using namespace std;
int tofloor = 0;

int main() {
	float time = 0;
	// for(int i = 0; i <10;i++){
	// 	time=CrRandom(10,15)*timewide;
	// 	cout<<time<<endl;
	// }
	int ID = 0;
	int MRuningtime=0;
	printf("电梯模拟系统\n请输入待运行时间：\n");
	cin>>MRuningtime;
	cout<<"请输入要模拟的楼层数："<<endl;
	cin>>tofloor;
	ConCenter Co;
	// time==Co.Lift[0].get_Floor();
	for(int j=0;j<2; j++){
		for(int i=0;i < 5; i++)
			Co.Call[i][j]=0;
	}
	Person* p;
	while (time < MRuningtime) {
		if (Co.Ctime.intertime == time) {
			ID++;
			p = Co.peoarrive(ID, Co.Ctime.intertime);
            Co.Inquene(Co.List[p->get_InFloor()][p->get_arrow()], p, Co.Call[p->get_InFloor()][p->get_arrow()]);
		}
		Co.LiftH();
		Co.LiftRun(time, 0);
		Co.LiftRun(time, 1);
		Co.peplgiveup_check(time);
		// Co.CheckOrder();
		time+=1;
	}
	cout<<"电梯模拟结束"<<endl;
	return 0;
}