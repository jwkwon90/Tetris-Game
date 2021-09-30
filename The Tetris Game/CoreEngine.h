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
	bool m_bFInishFLag; // True : 굳히기  False: 장애물
	int m_iKeyValue;
	int m_iCurBlockType, m_iNextBlockType;		 // 블럭 7개중 1개			//블럭 정보
	int m_iCurBlockRType, m_iNextBlockRType;       // 블럭 회전 4상태중 1개		//블럭 정보
	int m_iScore;
	int m_iGameSpeed;
	bool m_bGameFinish;
	bool m_bSpaceFlag;
	int m_iCurColor,m_iNextColor;
	POINT m_pCurPosition;	 // 현재 커서 위치

private:
	void CreateBlock();				   // 엔진

public:
	Tetris(void);
	~Tetris(void);
	int CheckCollision(POINT nextpos); // 엔진
	int CheckKey();					   // 엔진
	int RotateBlock(POINT curpos);	   // 엔진
	int RecoveryBlock(POINT curpos);   // 엔진
	int RemoveBlock(POINT curpos);     // 엔진
	int CheckLine();                   // 엔진
	int CheckFinish();                 // 엔진	
	int CheckRotation(POINT nextpos);  // 엔진
	int EndGame();					   // 엔진
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






