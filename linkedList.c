#include <stdio.h>

int main()
{
	typedef struct _USERDATA
	{
		int number;
		char name[16];
		struct _USERDATA* pNext;
	} USERDATA;

	USERDATA user[3] = {
		{1, "YangJI", NULL},
		{2, "JungJW", NULL},
		{3, "ChoiHS", NULL} };
	USERDATA* pTmp = NULL;

	pTmp = &user[0];
	user[0].pNext = &user[1];
	user[1].pNext = &user[2];
	user[2].pNext = NULL;

	while (pTmp != NULL)
	{
		printf("%d¹ø %s\n", pTmp->number, pTmp->name);
		pTmp = pTmp->pNext;
	}

}