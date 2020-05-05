#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Node
typedef struct Node
{
	char name[21];
	char mail[21];
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

// node print
void printNode()
{
	Node* Tmp = head->next;
	int i = 1;
	while (Tmp != NULL)
	{
		printf("\n%d번째 리스트: 이름: %s mail: %s \n", i, Tmp->name, Tmp->mail);
		Tmp = Tmp->next;
		i++;
	}
	printf("finish\n\n");
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

//find prev node
Node* FindPrevNode(Node* find)
{
	Node* nowNode = head;
	while (nowNode->next != find)
	{
		nowNode = nowNode->next;
	}
	return nowNode;
}

//  self Delete
void DeleteNodeSelf(Node* self)
{
	self = FindPrevNode(self);
	DeleteNode(self);
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
	int i = 0; 
	Node* LastNode;
	Node tmp = { 0 };
	Node* src;
	char ch;
	char arr1[20] = { 0 };
	char arr2[20] = { 0 };
	//void InitList() 초기 헤드 설정
	InitList();
	LastNode = head;

	//배열 할당 for Node* InsertNode(Node* Taget, Node* aNode)
	
	while (1)
	{
		printf("주소록 설정 1:보기, 2:추가, 3:삭제, C or c:비우기, Q or q:종료\n");
		ch = _getch();
		if (ch == 'Q' || ch == 'q')
			break;
		if (ch == 'C' || ch == 'c')
			system("cls");
		switch (ch)
		{
		case '1':
			if (LastNode == head)
			{
				printf("목록이 없습니다.\n");
				break;
			}
			printNode();
			break;
		case '2':
			/*추가할 목록*/
			printf("\n추가할 이름: ");
			gets_s(tmp.name, 20);
			printf("\n추가할 mail: ");
			gets_s(tmp.mail, 20);
			LastNode = InsertNode(LastNode, &tmp);
			printf("\n추가되었습니다.\n\n");
			break;
		case '3':
			src = head->next;
			printf("\n삭제할 인덱스: ");
			scanf_s("%d", &i);
			while (--i)
				src = src->next;
			DeleteNodeSelf(src);
			printf("\n삭제되었습니다.\n\n");
			break;
		}
	}

	UninitList();
}