#include"user.h"
#include"control.h"
#include"class.h"
#include"datatype.h"
using namespace std;

int main() {
	float time = 0;
	printf("电梯模拟系统\npress any key to start\n");
	getchar();
	int i = 0;
	int MRuningtime=0;
	ConCenter Co;
	Person* p;
	cin >> MRuningtime;
	while (time < MRuningtime && (++i+1)) {
		if (Co.Ltime.intertime == time) {
			p = Co.peoarrive(i, Co.Ltime.intertime);
            Co.Inquene(Co.List[p->get_InFloor()][p->get_arrow()], p, Co.Call[p->get_InFloor()][p->get_arrow()]);
			Co.LiftH(p);
		}
		Co.LiftRun(time);
		Co.CheckOrder();
		time++;
	}
	cout<<"电梯模拟结束"<<endl;
	return 0;
}