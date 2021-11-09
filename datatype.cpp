#include "datatype.h"

Head::Head()
{
	front = rear = new QNode;
	if (!front)exit(OVERFLOW);
	front->next = NULL;
}

Status Head::Enquene(Person* &P)
{
	Pquene Ptemp = new waitquene;
	if (!Ptemp)exit(OVERFLOW);
	Ptemp->Pe = P;
	rear->next = Ptemp;
	rear = Ptemp;
	if(front->next==NULL){
		front->next = Ptemp;
	}
	return OK;
}

Person* Head::Dequene()
{
	if (front == rear)exit(ERROR);
	Pquene p;
	Person* P;
	p = front->next;
	front->next = p->next;
	P = p->Pe;
	return P;
}

Status Head::Giveup()
{
	printf("第%d号乘客已放弃\n", front->next->Pe->ID);
	Pquene p = front->next;
	front->next = p->next;
	delete p;
	return OK;
}

waitquene::waitquene()
{
	Pe = NULL;
	next = NULL;
}


LiftStack::LiftStack()
{
	base = new NS[11];
	if (!base)exit(INFEASIBLE);
	top = base;
	num = 0;
}

Status LiftStack::Push(Person*& P)
{
	(*(top++))->p = P;
	num += 1;
	printf("第%d号乘客进入电梯\n", P->ID);
	return OK;
}

Status LiftStack::Pop()
{
	if (base == top)return ERROR;
	--top;
	printf("第%d号乘客离开电梯\n", (*top)->p->ID);
	return OK;
}

