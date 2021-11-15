#include"user.h"
#include"control.h"
#include"class.h"
#include"datatype.h"
using namespace std;

int main() {
	float time = 0;
	printf("电梯模拟系统\n请输入待运行时间：\n");
	int ID = 0;
	int MRuningtime=0;
	ConCenter Co;
	Person* p;
	cin >> MRuningtime;
	while (time < MRuningtime) {
		if (Co.Ctime.intertime == time) {
			ID++;
			p = Co.peoarrive(ID, Co.Ctime.intertime);
            Co.Inquene(Co.List[p->get_InFloor()][p->get_arrow()], p, Co.Call[p->get_InFloor()][p->get_arrow()]);
			Co.LiftH(p);
		}
		Co.LiftRun(time, 0);
		Co.LiftRun(time, 1);
		// Co.CheckOrder();
		time+=1;
	}
	cout<<"电梯模拟结束"<<endl;
	return 0;
}