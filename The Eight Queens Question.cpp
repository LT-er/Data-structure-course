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
		cout << "空栈，长度" << stacklength(s) << endl;
	else
		cout << "皇后列位置：",showelem(s);
	cout << endl;
}

bool available(stack s)
{
	int a = stacklength(s);//目前插入所在行数
	int top;
	gettop(s, top);//目前插入所在列数
	for (int i = 0; i < a - 1; i++)
	{
		if (*(s.base + i) + i + 1 == top + a//判断是否在同一主对角线
			|| *(s.base + i) - i - 1 == top - a//判断是否在同一副对角线
			|| *(s.base + i) == top)//判断是否在同一列
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
			if (flag[j] != 0)//用标记避免同列错误 
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
	cout << "从前往后表示第8行到第1行中每行皇后所在列" << endl<<endl;
	insert(Stack, num);
	cout << "共" << cnt << "种" << endl;
	return 0;
}
