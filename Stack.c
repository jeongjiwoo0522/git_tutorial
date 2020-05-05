#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

int* Stack;
int Size;
int Top;

void InitStack(int aSize)
{
	Size = aSize;
	Stack = (int*)malloc(Size * sizeof(int));
	Top = -1;
}

void FreeStack()
{
	free(Stack);
}

BOOL Push(int data)
{
	if (Top < Size - 1)
	{
		Top++;
		Stack[Top] = data;
		return TRUE;
	}
	else
		return FALSE;
}

int Pop()
{
	if (Top >= 0)
		return Stack[Top--];
	else
		return -1;
}

int main()
{
	InitStack(256);
	Push(7);
	Push(0);
	printf("%d\n", Pop());
	Push(5);
	printf("%d\n", Pop());
	Push(123);
	printf("%d\n", Pop());
	printf("%d\n", Pop());
	FreeStack();
}