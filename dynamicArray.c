#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//dynamicArray.c

#define TYPE int

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

void Insert(int idx, int value)
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
	free(arr);
}

void DumpArray(char* sMark)
{
	unsigned i;
	printf("%16s => 크기 = %02d, 개수=%02d : ", sMark, size, num);
	for (i = 0; i < num; i++)
		printf("%02d ", arr[i]);
	printf("\n");
}

void main()
{
	InitArray(10, 5);
	DumpArray("최초");

	for (int i = 1; i <= 8; i++)
		Append(i);
	DumpArray("8개 추가");

	Insert(3, 10);
	DumpArray("10 삽입");

	Insert(3, 11);
	DumpArray("11 삽입");

	Insert(3, 12);
	DumpArray("12 삽입");

	Delete(7);
	DumpArray("7 요소 삭제");
	UninitArray();
}




































