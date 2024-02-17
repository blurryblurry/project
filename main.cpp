#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Console.h"

#define MAX 30
#define BACKCOLOR 15
struct ST_OBJECT
{
	int x;
	int y;
	bool bActive = FALSE;
};

ST_OBJECT g_stEnemy[MAX];
ST_OBJECT g_stPlayer;

void Spawn()
{
	for (int i = 0;i < MAX;i++)
	{

		if (!g_stEnemy[i].bActive)
		{
			g_stEnemy[i].x = (rand() % 15) * 2;
			g_stEnemy[i].y = 0;
			g_stEnemy[i].bActive = TRUE;
			break;
		}
	}

}

int EnemyProcess()
{
	int count = 0;
	for (int i = 0;i < MAX;i++)
	{

		if (g_stEnemy[i].bActive)
		{
			SetColor(BACKCOLOR, i % 15);
			count++;
			GotoXY(g_stEnemy[i].x, g_stEnemy[i].y);
			printf("★");
			g_stEnemy[i].y++;
			
			if (g_stEnemy[i].y == g_stPlayer.y)
			{
				if (g_stEnemy[i].x == g_stPlayer.x)
					g_stPlayer.bActive = FALSE;
			}

			if (g_stEnemy[i].y > g_stPlayer.y) g_stEnemy[i].bActive = FALSE;
		}
	}
	return count;
}

void InputProcess()
{
	if (GetAsyncKeyState(VK_LEFT) & 0X8000)
	{
		g_stPlayer.x-=2;
		if (g_stPlayer.x < 0) g_stPlayer.x = 0;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
	{
		g_stPlayer.x+=2;
		if (g_stPlayer.x > 28) g_stPlayer.x = 28;
	}
}

void Update() 
{	
	SetColor(BACKCOLOR, 12);
	if (g_stPlayer.bActive)
	{
		GotoXY(g_stPlayer.x, g_stPlayer.y);
		printf("▲");
	}
	else
	{
		GotoXY(g_stPlayer.x, g_stPlayer.y);
		printf("▒");
	}
	
}

void Init() 
{
	g_stPlayer.x = 14;
	g_stPlayer.y = 28;
	g_stPlayer.bActive = TRUE;

	srand(time(NULL));
	SetConsoleSize(30, 30);
	SetTitle("별피하기");
	SetColor(BACKCOLOR, 0);
}

int g_iScore = 0;
void Score()
{
	if (g_stPlayer.bActive)
	{
		g_iScore++;
	}
	
	GotoXY(0, 0);
	printf("Score: %d", g_iScore);
}

void StartMenu()
{
	while (_kbhit()) _getch();
	while (1)
	{
		Clear();
		GotoXY(10, 9);
		printf("별 피하기");
		GotoXY(10, 20);
		printf("Press any Key ...");
		if (_kbhit()) break;
		Sleep(50);
	}
}
void GameMain()
{
	g_stPlayer.x = 14;
	g_stPlayer.y = 28;
	g_stPlayer.bActive = TRUE;
	g_iScore = 0;

	int state = 0;
	while (1) {
		Clear();
		if (g_stPlayer.bActive)
		{
			Spawn();
			InputProcess();
		}

		state = EnemyProcess();

		Update();
		Score();
		Sleep(50);
		if (state == 0) break;
	}
}
bool ResultMenu()
{
	bool bRet = false;
	while (1)
	{
		Clear();
		GotoXY(10, 9);
		printf("Result Menu: ");
		GotoXY(10, 15);
		printf("SCORE: %d", g_iScore);

		GotoXY(0, 24);
		printf("continue: ...Y/N");
		if (GetAsyncKeyState('Y') & 0x8000)
		{
			bRet = FALSE;
			break;
		}

		if (GetAsyncKeyState('N') & 0x8000)
		{
			bRet = TRUE;
			break;
		}
		Sleep(50);
	}
	return bRet;
}
int main()
{
	
	Init();

	while (1)
	{
		StartMenu();
		GameMain();
		if (ResultMenu()) break;
	}
	system("pause");
	return 0;
	
}
