// The Tetris Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InterFace.h"

ui *UIClass = new ui();

int InitMap();
int Init();
int CheckPosition(POINT pos);
int Update();
int UpdateMap();
void SetGameSpeed();
void textcolor(int color_number);
void gotoxy(POINT dir);

int _tmain(int argc, _TCHAR* argv[])
{
	UIClass->Engine->Opening();
	Init();
	UpdateMap();	
	UIClass->Engine->ShowNextBlock(); //���� �� ����
	gotoxy(UIClass->Engine->m_pCurPosition);

	while(1)
	{
		for(int i =0; i < 4; i++)
		{
			UIClass->Engine->CheckKey();	

			if(UIClass->Engine->m_bSpaceFlag == true)
			{
				UIClass->Engine->m_bSpaceFlag = false;
				break;
			}
		}

		//if(UIClass->Engine->CheckKey() == SUCCESS)			
			UpdateMap();	
			
		Sleep(UIClass->Engine->GetGameCycle());	

		if(UIClass->Engine->CheckFinish() == FAIL)
		{
			gotoxy(UIClass->Engine->m_pCurPosition); //Ŀ�� �ʱ�ȭ
			SetGameSpeed();	
			textcolor(UIClass->Engine->m_iCurColor);
		}

		if(UIClass->Engine->m_bGameFinish == true)
			break;
	}
	return 0;
}

int Init()
{
	InitMap();
	UIClass->Engine->InitGame();
	gotoxy(UIClass->Engine->m_pCurPosition);	
	return SUCCESS;
}

int UpdateMap()
{
	POINT dir;
	for (int i = 0; i < Y_MAP_SIZE; i++)
	{
		for (int j = 0; j < X_MAP_SIZE; j++)
		{
			if(UIClass->Engine->m_cMap[i][j] != UIClass->Engine-> m_cMapCopy[i][j])
			{
				
				dir.y = i; dir.x = j;
				gotoxy(dir);

				if(UIClass->Engine->m_cMap[i][j] != 0)		
				{
					printf("��");
				}
				else
					printf("  ");
			}
		}			
	}

	for (int i = 0; i < Y_MAP_SIZE; i++)
		for (int j = 0; j < X_MAP_SIZE; j++)
			UIClass->Engine-> m_cMapCopy[i][j] = UIClass->Engine->m_cMap[i][j];

	return SUCCESS;
}

int InitMap()
{
	for(int i = 0; i < Y_MAP_SIZE+1;i++)
	{
		for(int j = 0; j < X_MAP_SIZE;j++)
		{
			if(UIClass->Engine->m_cMap[i][j] != 0)		
			{				
				printf("��");
			}
			else
				printf("  ");
		}
		if( i == 24)
			break;
		else
			printf("\n");
	}
	return SUCCESS;
}

void gotoxy(POINT dir)
{
	COORD CursorPos = {dir.x * 2, dir.y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CursorPos);
}

void SetGameSpeed()
{
	if(UIClass->Engine->GetScore() > 200)
		UIClass->Engine->SetGameCycle(100);
	else if(UIClass->Engine->GetScore() > 100)
		UIClass->Engine->SetGameCycle(200);
	else if(UIClass->Engine->GetScore() > 50)
		UIClass->Engine->SetGameCycle(300);
}

void textcolor(int color_number)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
	/*0 - ������
	1 - �Ķ���
	2 - �ʷϻ�
	3 - ����
	4 - ������
	5 - ���ֻ�
	6 - �����
	7 - ���
	8 - ȸ��
	9 - ���� �Ķ���
	A - ���� �ʷϻ�
	B - ���� ����
	C - ���� ������
	D - ���� ���ֻ�
	E - ���� �����
	F - ���� ���*/
}
