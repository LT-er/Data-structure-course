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
//����һ����ͷ���ĺ���n��Ԫ�ص�˫��ѭ������
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
	printf("�����봬�ϵ�������\n");
	scanf_s("%d", &n);
	int* arr = new int[n + 1];
	arr[0] = 6;
	for (int i = 1; i <= n; i++)
		arr[i] = 0;
	printf("������������\n");
	scanf_s("%d", &m);
	printf("�����뷴����\n");
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
		printf("��%d��������������б�Ͷ���˺���\n", q->data);
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
			printf("��%d�����ڷ�������б�Ͷ���˺���\n", a->data);
			arr[a->data] = 1;
			free(a);
			i++;
		}
		else break;
	}

	printf("��");
	for (int i = 1; i <= n; i++)
	{
		if (arr[i] == 0)
			printf("%d ", i);
	}
	printf("���˻�������\n");
	delete[] arr;
}

