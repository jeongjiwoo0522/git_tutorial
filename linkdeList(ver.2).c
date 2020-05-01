#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Node
typedef struct Node
{
	int value;
	struct Node* next;
} Node;

Node* head;

// 연결리스트 초기화 & 헤드 할당
void InitList()
{
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
}

//Taget 다음에 노드 삽입
Node* InsertNode(Node* Taget, Node* aNode)
{
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node));
	*newNode = *aNode;

	newNode->next = Taget->next;
	Taget->next = newNode;

	return newNode;
}

//Tager 다음의 노드 삭제
int DeleteNode(Node* Taget)
{
	Node* del;
	del = Taget->next;
	if (del == NULL)
		return 0;
	Taget->next = del->next;
	free(del);
	return 1;
}

//연결리스트의 모든 노드와 헤드 삭제

void UninitList()
{
	while (DeleteNode(head)) { ; }
	free(head);
	head = NULL;
}

void main()
{
	int i;
	Node* Now;
	Node Temp;

	InitList();
	//5개의 노드 삽입
	Now = head;
	for (i = 1; i <= 5; i++)
	{
		Temp.value = i;
		Now = InsertNode(Now, &Temp);
	}

	//2번째 노드 삭제
	DeleteNode(head->next);

	//print
	Now = head->next;
	while (Now != NULL)
	{
		printf("%d\t", Now->value);
		Now = Now->next;
	}
	putchar('\n');

	UninitList();
}