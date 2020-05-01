#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//dynamicArray.c


typedef struct NameCard
{
	char name[10];
	char tel[15];
	char addr[32];
} NameCard;

#define TYPE NameCard*

TYPE* arr;
unsigned size;
unsigned num;
unsigned growby;

void InitArray(unsigned asize, unsigned agrowby)
{
	size = asize;
	growby = agrowby;
	num = 0;
	arr = (TYPE*)calloc(size, sizeof(TYPE));
}

void Insert(int idx, TYPE value)
{
	unsigned need;
	need = num + 1;
	if (need > size)
	{
		size = need + growby;
		arr = (TYPE*)realloc(arr, sizeof(TYPE) * size);
	}
	memmove(arr + idx + 1, arr + idx, (num-idx)*sizeof(TYPE));
	arr[idx] = value;
	num++;
}

void Delete(int idx)
{
	memmove(arr + idx, arr + idx + 1, (num - idx - 1) *sizeof(TYPE));
	num--;
}

void Append(TYPE value)
{
	Insert(num, value);
}

void UninitArray(void)
{
	for (int i = 0; i < size; i++)
		free(arr[i]);
	free(arr);
}

//void DumpArray(char* sMark)
//{
//	unsigned i;
//	printf("%16s => 크기 = %02d, 개수=%02d : ", sMark, size, num);
//	for (i = 0; i < num; i++)
//		printf("%02d ", arr[i]);
//	printf("\n");
//}

void main()
{
	char ch;
	unsigned i;
	NameCard* Temp = (TYPE)malloc(sizeof(NameCard*));

	InitArray(10, 5);
	while (1)
	{
		printf("명령을 입력하세요(1:보기, 2:추가, 3삭제, Q:종료) > ");
		ch = _getch();
		printf("\n");
		if (ch == 'Q' || ch == 'q')
			break;
		switch (ch)
		{
		case '1':
			if (num == 0)
				printf("등록된 내용이 없습니다.\n");
			else
			{
				for (i = 0; i < num; i++)
					printf("%d, 이름:%s, 전화:%s, 주소:%s\n"\
, i, arr[i]->name, arr[i]->tel, arr[i]->addr);
			}
			break;
		case '2':
			printf("이름을 입력하세요(9자): ");
			gets(Temp->name);
			printf("전화전호를 입력하세요(14자)");
			gets(Temp->tel);
			printf("주소를 입력하세요(31)");
			gets(Temp->addr);
			Append(Temp);
			break;
		case '3':
			printf("삭제할 번호를 입력하세요 : ");
			scanf_s("%d", &i);
			if (i < num)
				Delete(i);
			else
				printf("등록되지 않은 번호입니다.\n");
			break;
		}
	}
	UninitArray();
	free(Temp);
}


















