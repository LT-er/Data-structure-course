#include<iostream>
using namespace std;
int cnt = 0;
int flag[8] = { 0 };
typedef struct {
	int* base;
	int* top;
	int size;
}stack;

bool init(stack &s)
{
	s.base = (int*)malloc(10 * sizeof(int));
	if (!s.base)
		exit(-1);
	s.top = s.base;
	s.size = 10;
	return true;
}

bool stackempty(stack s)
{
	if (s.top == s.base)
		return true;
	else return false;
}

int stacklength(stack s)
{
	return s.top - s.base;
}

bool gettop(stack s,int &e)
{
	if (stackempty(s))
		return false;
	else 
		e = *(s.top - 1);
	return true;
}

bool push(stack& s, int e)
{
	if (s.top - s.base >= s.size)
	{
		s.base = (int*)realloc(s.base, (s.size + 10) * sizeof(int));
		if (!s.base)
			exit(-1);
		s.top = s.base + s.size;
		s.size += 10;
	}

	*s.top++ = e;
	return true;
}

bool pop(stack& s, int& e)
{
	if (s.top == s.base)
		return false;
	e = *(s.top - 1);
	s.top--;
	return true;
}

void showelem(stack s)
{
	int* p = s.base;
	while (p < s.top)
	{
		cout << *(p++) << " ";
	}
	cout << endl;
}

void showstack(stack s)
{
	if (stackempty(s))
		cout << "��ջ������" << stacklength(s) << endl;
	else
		cout << "�ʺ���λ�ã�",showelem(s);
	cout << endl;
}

bool available(stack s)
{
	int a = stacklength(s);//Ŀǰ������������
	int top;
	gettop(s, top);//Ŀǰ������������
	for (int i = 0; i < a - 1; i++)
	{
		if (*(s.base + i) + i + 1 == top + a//�ж��Ƿ���ͬһ���Խ���
			|| *(s.base + i) - i - 1 == top - a//�ж��Ƿ���ͬһ���Խ���
			|| *(s.base + i) == top)//�ж��Ƿ���ͬһ��
			return false;
	}
	return true;
}



void insert(stack& s, int num)
{
	int p;
	if (num == 8)
	{
		cnt++;
		showstack(s);
		return;
	}
	else
	{
		for (int j = 0; j < 8; j++)
		{
			if (flag[j] != 0)//�ñ�Ǳ���ͬ�д��� 
				continue;
			else
			{
				push(s, j + 1);
				if (available(s))
				{
					num++;
					flag[j] = 1;
					insert(s, num);
					flag[j] = 0;
					pop(s, p);
					num--;
				}
				else
					pop(s, p);
			}
		}
	}
}

int main()
{
	int num = 0;
	stack Stack;
	init(Stack);
	cout << "��ǰ�����ʾ��8�е���1����ÿ�лʺ�������" << endl<<endl;
	insert(Stack, num);
	cout << "��" << cnt << "��" << endl;
	return 0;
}
