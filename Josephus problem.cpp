#include<stdio.h>
#include<iostream>
#include <malloc.h>

typedef struct Node {
	int data;
	struct Node* pre;
	struct Node* next;
}Node;

typedef struct {
	Node* head;
	Node* tail;
	int len;
}*Linklist;

Linklist init(int n)
//建立一个带头结点的含有n个元素的双向循环链表
{
	Node* q;
	Node* p = (Node*)malloc(sizeof(Node));
	p->next = p;
	p->pre = p;
	p->data = 1;
	q = p;
	for (int i = 2; i <= n; i++)
	{
		Node* a = (Node*)malloc(sizeof(Node));
		a->next = q->next;
		q->next = a;
		a->pre = q;
		a->data = i;
		p->pre = a;
		q = a;
	}

	Linklist L = (Linklist)malloc(sizeof(Linklist));
	L->head = p;
	L->tail = p->pre;
	L->len = n;
	return L;
}



int main()
{
	int n, m, k = 0;
	printf("请输入船上的总人数\n");
	scanf_s("%d", &n);
	int* arr = new int[n + 1];
	arr[0] = 6;
	for (int i = 1; i <= n; i++)
		arr[i] = 0;
	printf("请输入正向报数\n");
	scanf_s("%d", &m);
	printf("请输入反向报数\n");
	scanf_s("%d", &k);
	Linklist L = init(n);
	Node* p = L->head;
	int i = 1;
	while (i <= n / 2)
	{
		Node* q;
		for (int j = 1; j < m - 1; j++)
			p = p->next;
		q = p->next;
		p->next = q->next;
		q->next->pre = p;
		p = p->next;
		printf("第%d个人在正向计数中被投入了海中\n", q->data);
		arr[q->data] = 1;
		free(q);
		i++;

		if (i < n / 2)
		{
			Node* a;
			for (int j = 1; j < k - 1; j++)
				p = p->pre;
			a = p->pre;
			p->pre = a->pre;
			a->pre->next = p;
			p = p->pre;
			printf("第%d个人在反向计数中被投入了海中\n", a->data);
			arr[a->data] = 1;
			free(a);
			i++;
		}
		else break;
	}

	printf("第");
	for (int i = 1; i <= n; i++)
	{
		if (arr[i] == 0)
			printf("%d ", i);
	}
	printf("个人活了下来\n");
	delete[] arr;
}

