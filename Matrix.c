#include <Turboc.h>

#define MAX 1024
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

typedef struct Signal
{
	BOOL exist;
	char prn;
	int x, y;
	int distance;
	int nFrame;
	int nStay;
} Signal;

Signal S[MAX];

int main()
{
	int i = 0;
	char ch = 0;
	int freq = 15;
	//int frame = 200;

	clrscr();
	gotoxy(0, 23);
	//printf("메트릭스 흉내내기, 상하:속도 증감, 좌우:빈도 증감, ESC:종료");
	randomize();
	while (TRUE)
	{
		//gotoxy(60, 23);
		//printf("속도:%d, 빈도:%d  ", frame, freq);

		//키 입력처리
		if (_kbhit())
		{
				ch = _getch();
				/*switch(ch)
				{
				case UP:
					frame = min(frame + 10, 1000);
					break;
				case DOWN:
					frame = max(frame - 10, 10);
					break;
				case RIGHT:
					freq = max(freq - 1, 1);
					break;
				case LEFT:
					freq = min(freq + 1, 30);
					break;
				}*/
				
				if (ch == ESC)
					return 0;			
		}

		//새로운 신호 생성
		if (random(freq) == 0)
		{
			for (i = 0; i < MAX; i++)
			{
				if (S[i].exist == FALSE)
				{
					S[i].exist = TRUE;
					S[i].prn = random('Z' - 'A' + 1) + 'A';
					S[i].x = random(80);
					S[i].y = 0;
					S[i].distance = 23;//random(14) + 9;
					S[i].nFrame = S[i].nStay = 20;//random(15) + 5;
					break;
				}
			}
		}

		for (i = 0; i < MAX; i++)
		{
			if (S[i].exist == FALSE)
				continue;
			S[i].nStay--;
			if (S[i].nStay == 0)
			{
				S[i].nStay = S[i].nFrame;
				gotoxy(S[i].x, S[i].y);
				_putch(' ');
				S[i].y++;
				if (S[i].y < S[i].distance)
				{
					gotoxy(S[i].x, S[i].y);
					_putch(S[i].prn);
				}
				else
					S[i].exist = FALSE;
			}
		}

		delay(100);
	}
}