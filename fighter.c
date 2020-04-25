#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <Turboc.h>

#define delay(n) Sleep(n)
#define randomize() srand((unsigned int)time(NULL))
#define random(n) (rand()%(n))

#define ESC 27
#define MAXENEMY 10
#define MAXBALL 20

int fx;
int bx, by;
int Score;

typedef struct tag_Enemy
{
	BOOL exist;
	int Type;
	int x, y;
	int Delta;
	int nFrame;
	int nStay;
} type_Enemy;

type_Enemy Enemy[MAXENEMY];

typedef struct tag_Ball
{
	BOOL exist;
	int x, y;
	int nFrame;
	int nStay;
} type_Ball;

type_Ball Ball[MAXBALL];

char* arrEnemy[4] = { " ;;^;; ", " zZWZz ", " oO@Oo ", " <-=-> " };

BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

int main()
{
	int ch = 0;
	int i = 0, j = 0;
	BOOL bFound = FALSE;
	int count = 0;

	randomize();
	system("cls");
	setcursortype(NOCURSOR);
	fx = 40;
	bx = -1;
	
	for (count = 0;; count++)
	{
		//좌우이동처리
		if (count % 5 == 0)
		{
			if (IsKeyDown(VK_LEFT))
				if (fx > 6)
					fx--;
			if (IsKeyDown(VK_RIGHT))
				if (fx < 72)
					fx++;
		}
		//키 입력 처리
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 0xE0 || ch == 0)
				ch = _getch();
			else
			{
				switch (ch)
				{
				case ' ':
					if (bx == -1)
					{
						bx = fx;
						by = 23;
					}
					break;
				case ESC:
					goto END;
				}
			}
		}

		//적군 생성
		if (random(100) == 0)
		{
			for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++) { ; }
			if (i != MAXENEMY)
			{
				if (random(2) == 1)
				{
					Enemy[i].x = 5;
					Enemy[i].Delta = 1;
				}
				else
				{
					Enemy[i].x = 75;
					Enemy[i].Delta = -1;
				}

				while (1)
				{
					Enemy[i].y = random(10) + 1;
					for (bFound = FALSE, j = 0; j < MAXENEMY; j++)
					{
						if (Enemy[j].exist == TRUE && Enemy[j].y == Enemy[i].y)
						{
							bFound = TRUE;
							break;
						}
					}
					if (bFound == FALSE)
						break;
				}

				Enemy[i].nFrame = Enemy[i].nStay = random(6) + 1;
				Enemy[i].Type = random(sizeof(arrEnemy) / sizeof(arrEnemy[0]));
				Enemy[i].exist = TRUE;
			}
		}

		//아군 총알 이동 및 출력
		if (bx != -1)
		{
			gotoxy(bx, by);
			putchar(' ');
			if (by == 0)
				bx = -1;
			else
			{
				by--;
				gotoxy(bx, by);
				putchar("i");
			}

		}

		//적군과 아군 총알의 충돌 판정
		for (i = 0; i < MAXENEMY; i++)
		{
			if (Enemy[i].exist == FALSE)
				continue;
			if (Enemy[i].y == by && abs(Enemy[i].x - bx) <= 2)
			{
				gotoxy(bx, by);
				putchar(' ');
				bx = -1;
				Enemy[i].exist = FALSE;
				gotoxy(Enemy[i].x - 3, Enemy[i].y);
				puts("         ");
				Score += 7 - Enemy[i].nFrame;
				break;
			}
		}

		//적군 총알 이동 
		for (i = 0; i < MAXBALL; i++)
		{
			if (Ball[i].exist == FALSE)
				continue;
			if (--Ball[i].nStay == 0)
			{
				Ball[i].nStay = Ball[i].nFrame;
				gotoxy(Ball[i].x, Ball[i].y);
				putchar(' ');
				if (Ball[i].y >= 23)
					Ball[i].exist = FALSE;
				else
				{
					Ball[i].y++;
					gotoxy(Ball[i].x, Ball[i].y);
					putchar('*');
				}
			}
		}

		//적군과 아군의 충돌 판정
		for (i = 0; i < MAXBALL; i++)
		{
			if (Ball[i].exist == FALSE)
				continue;
			if (Ball[i].y == 23 && abs(Ball[i].x - fx) <= 2)
			{
				gotoxy(fx - 3, 21);
				puts("   .   ");
				gotoxy(fx - 3, 22);
				puts("  . . .");
				gotoxy(fx - 3, 23);
				puts("..:V:..");
				delay(2000);
				goto END;
			}
		}

		//적군 이동 및 출력 
		for (i = 0; i < MAXENEMY; i++)
		{
			if (Enemy[i].exist == FALSE)
				continue;
			if (--Enemy[i].nStay == 0)
			{
				Enemy[i].nStay = Enemy[i].nFrame;
				if (Enemy[i].x >= 76 || Enemy[i].x <= 4)
				{
					Enemy[i].exist = FALSE;
					gotoxy(Enemy[i].x - 3, Enemy[i].y);
					puts("       ");
				}
				else
				{
					Enemy[i].x += Enemy[i].Delta;
					gotoxy(Enemy[i].x - 3, Enemy[i].y);
					puts(arrEnemy[Enemy[i].Type]);

					//총알 발사 
					if (random(40) == 0)
					{
						for (j = 0; j < MAXBALL && Ball[j].exist == TRUE; j++) { ; }
						if (j != MAXBALL)
						{
							Ball[j].x = Enemy[i].x + 2;
							Ball[j].y = Enemy[i].y + 1;
							Ball[j].nFrame = Ball[j].nStay = Enemy[i].nFrame * 6;
							Ball[j].exist = TRUE;
						}
					}
				}
			}
		}

		//파이터 및 점수 출력
		gotoxy(fx - 3, 23);
		puts(" <<A>> ");
		gotoxy(0, 24);
		printf("점수 = %d", Score);

		// 초당 100 프레임
		delay(10);
	}
END:
	setcursortype(NORMALCURSOR);

}

