#pragma once
#include <Windows.h>
#include <windef.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <time.h>

using namespace std;

#define X_MOVING_SIZE 2
#define Y_MOVING_SIZE 1

#define X_MAP_SIZE 15
#define Y_MAP_SIZE 25

#define X_Block_SIZE 4
#define Y_Block_SIZE 4

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

#define FULL 13

#define NUMBER_OF_BLOCK 7
#define NUMBER_OF_ROTATION 4
#define SUCCESS 0
#define FAIL 1

class Tetris
{

public:
	void InitBlock();
	void InitMap();
	void InitCursor();
	void InitGame();

public:
	char m_cMap[Y_MAP_SIZE][X_MAP_SIZE];
	char m_cMapCopy[Y_MAP_SIZE][X_MAP_SIZE];
	char m_cAllBlocks[NUMBER_OF_BLOCK * NUMBER_OF_ROTATION][Y_Block_SIZE][X_Block_SIZE];
	char m_cCurBlock[Y_Block_SIZE][X_Block_SIZE];
	char m_cNextBlock[Y_Block_SIZE][X_Block_SIZE];
	short m_sCurBlockPosition;
	bool m_bFInishFLag; // True : ������  False: ��ֹ�
	int m_iKeyValue;
	int m_iCurBlockType, m_iNextBlockType;		 // �� 7���� 1��			//�� ����
	int m_iCurBlockRType, m_iNextBlockRType;       // �� ȸ�� 4������ 1��		//�� ����
	int m_iScore;
	int m_iGameSpeed;
	bool m_bGameFinish;
	bool m_bSpaceFlag;
	int m_iCurColor,m_iNextColor;
	POINT m_pCurPosition;	 // ���� Ŀ�� ��ġ

private:
	void CreateBlock();				   // ����

public:
	Tetris(void);
	~Tetris(void);
	int CheckCollision(POINT nextpos); // ����
	int CheckKey();					   // ����
	int RotateBlock(POINT curpos);	   // ����
	int RecoveryBlock(POINT curpos);   // ����
	int RemoveBlock(POINT curpos);     // ����
	int CheckLine();                   // ����
	int CheckFinish();                 // ����	
	int CheckRotation(POINT nextpos);  // ����
	int EndGame();					   // ����
	void Ending();
	void Opening();
	void ChangeNextColor();
	void ChangeCurColor();
	void ShowNextBlock();
	void gotoxy(POINT pos);
	void ShowScore();
	void ShowGameSpeed();
	void ShowNextBlockBoard();
	
public:
	int MoveBlock(int direction);	   // Ui
	int SetGameCycle(int cycle);	   // Ui
	int GetGameCycle();			       // Ui
	int SetScore(int score);		   // Ui
	int GetScore();					   // Ui
	void GetCurBlock();				   // Ui
	void SetNextBlock();			   // Ui
};






