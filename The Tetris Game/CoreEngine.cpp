#include "stdafx.h"
#include "CoreEngine.h"
#include <math.h>


Tetris::Tetris(void)
{
	this->m_iGameSpeed = 400; // GameSpeed는 초기 디폴트값이 1000으로 고정
	this->m_iScore = 0;		   // GameScore는 초기 디폴트값이 0
	this->m_bFInishFLag = false;
	this->m_bGameFinish = false;
	this->m_bSpaceFlag = false;
	this->m_iCurColor = 0;
	this->m_iNextColor = 0;
	InitMap();				   // 맵 초기화
	InitBlock();               // 블럭 초기화	
	InitCursor();
	SetNextBlock();
	GetCurBlock();	
}

Tetris::~Tetris(void)
{
}

void Tetris::InitBlock()
{
	char temptype1[28][4][4] = 
	   {{{0, 0, 0, 0},{1, 0, 0, 0},{1, 1, 1, 0},{0, 0, 0, 0}},    // ■
	    {{0, 0, 1, 0},{0, 0, 1, 0},{0, 1, 1, 0},{0, 0, 0, 0}},    // ■ ■ ■
	    {{1, 1, 1, 0},{0, 0, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
	    {{1, 1, 0, 0},{1, 0, 0, 0},{1, 0, 0, 0},{0, 0, 0, 0}},

	    {{0, 0, 0, 0},{0, 0, 1, 0},{1, 1, 1, 0},{0, 0, 0, 0}},    //     ■
	    {{0, 1, 1, 0},{0, 0, 1, 0},{0, 0, 1, 0},{0, 0, 0, 0}},    // ■ ■ ■
	    {{1, 1, 1, 0},{1, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},   
	    {{1, 0, 0, 0},{1, 0, 0, 0},{1, 1, 0, 0},{0, 0, 0, 0}},

	    {{0, 0, 0, 0},{0, 1, 0, 0},{1, 1, 1, 0},{0, 0, 0, 0}},    //   ■
	    {{0, 0, 0, 0},{0, 1, 0, 0},{1, 1, 0, 0},{0, 1, 0, 0}},    // ■ ■ ■ 
	    {{0, 0, 0, 0},{0, 0, 0, 0},{1, 1, 1, 0},{0, 1, 0, 0}},   
	    {{0, 0, 0, 0},{0, 1, 0, 0},{0, 1, 1, 0},{0, 1, 0, 0}},

	    {{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0}},    // ■
	    {{0, 0, 0, 0},{0, 0, 0, 0},{1, 1, 1, 1},{0, 0, 0, 0}},    // ■
	    {{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0}},    // ■
	    {{0, 0, 0, 0},{0, 0, 0, 0},{1, 1, 1, 1},{0, 0, 0, 0}},    // ■

	    {{1, 1, 0, 0},{1, 1, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},    // ■ ■
	    {{1, 1, 0, 0},{1, 1, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},    // ■ ■ 
	    {{1, 1, 0, 0},{1, 1, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},   
	    {{1, 1, 0, 0},{1, 1, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},

	    {{0, 0, 0, 0},{0, 1, 1, 0},{1, 1, 0, 0},{0, 0, 0, 0}},    // ■
	    {{0, 1, 0, 0},{0, 1, 1, 0},{0, 0, 1, 0},{0, 0, 0, 0}},    // ■ ■  
	    {{0, 0, 0, 0},{0, 1, 1, 0},{1, 1, 0, 0},{0, 0, 0, 0}},    //   ■
	    {{0, 1, 0, 0},{0, 1, 1, 0},{0, 0, 1, 0},{0, 0, 0, 0}},

	    {{0, 0, 0, 0},{1, 1, 0, 0},{0, 1, 1, 0},{0, 0, 0, 0}},	  //   ■
	    {{0, 0, 1, 0},{0, 1, 1, 0},{0, 1, 0, 0},{0, 0, 0, 0}},	  // ■ ■
	    {{0, 0, 0, 0},{1, 1, 0, 0},{0, 1, 1, 0},{0, 0, 0, 0}},    // ■
	    {{0, 0, 1, 0},{0, 1, 1, 0},{0, 1, 0, 0},{0, 0, 0, 0}}};

	for(int i = 0; i < NUMBER_OF_BLOCK * NUMBER_OF_ROTATION; i++)
		for(int j = 0; j < Y_Block_SIZE; j++)
			for(int k = 0; k < X_Block_SIZE; k++)
				m_cAllBlocks[i][j][k] = temptype1[i][j][k];
}

void Tetris::InitMap()
{
	for (int i = 0; i < Y_MAP_SIZE; i++)
	{
		for (int j = 0; j < X_MAP_SIZE; j++)
		{
			if (i < Y_MAP_SIZE && j == 0) // 맵의 왼쪽 줄 1로 세팅
				this->m_cMapCopy[i][j] = this->m_cMap[i][j] = 1;

			else if(i == Y_MAP_SIZE - 1) // 맵의 가장 아래쪽 부분 1로 세팅
				this->m_cMapCopy[i][j] = this->m_cMap[i][j] = 1;

			else if (i  < Y_MAP_SIZE && j == X_MAP_SIZE -1 ) // 맵의 가장 오른쪽 줄 1로 세팅
				this->m_cMapCopy[i][j] = this->m_cMap[i][j] = 1;

			else
				this->m_cMapCopy[i][j] = this->m_cMap[i][j] = 0;
		}
	}
}

void Tetris::InitCursor()
{
	POINT initpoint;
	initpoint.x = 6;
	initpoint.y = 0;
	
	this->m_pCurPosition = initpoint;
}

void Tetris::InitGame()
{
	GetCurBlock();	
	ShowNextBlockBoard();
	ShowScore();
	ShowGameSpeed();	
	ShowNextBlock();
	InitCursor();
	if(EndGame() == FAIL)
		Ending();	
}

void Tetris::CreateBlock()
{
	int retval = 0;
	
	srand( (unsigned int)(time(NULL)) );
	retval = rand() % (NUMBER_OF_BLOCK * NUMBER_OF_ROTATION);
			
	this->m_iNextBlockType = retval / NUMBER_OF_ROTATION;
	this->m_iNextBlockRType = retval % NUMBER_OF_ROTATION;	
		
	for (int i = 0; i < Y_Block_SIZE; i++)
			for (int j = 0; j < X_Block_SIZE; j++)
				this->m_cNextBlock[i][j] = this->m_cAllBlocks[retval][i][j];
}

void Tetris::SetNextBlock()
{
	CreateBlock();
}

void Tetris::GetCurBlock()
{
	for (int i = 0; i < Y_Block_SIZE; i++)
			for (int j = 0; j < X_Block_SIZE; j++)
				this->m_cCurBlock[i][j] = this->m_cNextBlock[i][j];

	this->m_iCurBlockType = this->m_iNextBlockType;
	this->m_iCurBlockRType = this->m_iNextBlockRType;

	SetNextBlock();
}

int Tetris::CheckKey()
{
	int ret=0;
	POINT tempPosition = this->m_pCurPosition;
	m_iKeyValue = 0;

	if(_kbhit())
	{
		m_iKeyValue = _getch();

		if(m_iKeyValue == 224) // 방향키 일 경우만
		{
			m_iKeyValue = _getch();

			switch (m_iKeyValue)
			{
			case LEFT :
				tempPosition.x = tempPosition.x - 1; 

				if(CheckCollision(tempPosition) == SUCCESS)
					MoveBlock(LEFT);
				break;
			case RIGHT :
				tempPosition.x = tempPosition.x + 1;

				if(CheckCollision(tempPosition) == SUCCESS)
					MoveBlock(RIGHT);
				break;
			case DOWN :	
				tempPosition.y = tempPosition.y + 1;
				if(CheckCollision(tempPosition) == SUCCESS)
					MoveBlock(DOWN);
				else
					return FAIL;
				break;
			case UP :	
				RotateBlock(this->m_pCurPosition);
				break;
			}
		}
		else if(m_iKeyValue == SPACE)
		{
			while(1)
			{
				tempPosition.y = tempPosition.y + 1;

				if(CheckCollision(tempPosition) == SUCCESS)
					MoveBlock(DOWN);
				else
				{
					this->m_bSpaceFlag = true;
					break;
				}
			}
		}
		else
			return FAIL;
	}
	return SUCCESS;
}

int Tetris::MoveBlock(int keyvalue)
{
	switch (keyvalue)
	{
	case LEFT: 
		RemoveBlock(m_pCurPosition);

		for(int i = 0; i < Y_Block_SIZE; i++)
		{
			for(int j = 0; j < X_Block_SIZE; j++)
			{
				if(this->m_cCurBlock[i][j] == 1)
				m_cMap[m_pCurPosition.y + i ][m_pCurPosition.x + j - 1] = this->m_cCurBlock[i][j];
			}
		}

		m_pCurPosition.x--;
		break;
	case RIGHT: 
		RemoveBlock(m_pCurPosition);

		for(int i = 0; i < Y_Block_SIZE; i++)
		{
			for(int j = 0; j < X_Block_SIZE; j++)
			{
				if(this->m_cCurBlock[i][j] == 1)
				m_cMap[m_pCurPosition.y + i ][m_pCurPosition.x + j + 1] = this->m_cCurBlock[i][j];
			}
		}

		m_pCurPosition.x++;
		break;
	case DOWN: 
		RemoveBlock(m_pCurPosition);

		for(int i = 0; i < Y_Block_SIZE; i++)
		{
			for(int j = 0; j < X_Block_SIZE; j++)
			{
				if(this->m_cCurBlock[i][j] == 1)
					m_cMap[m_pCurPosition.y +i + 1][m_pCurPosition.x +j] = this->m_cCurBlock[i][j];
			}
		}
		m_pCurPosition.y++;				
		break;
	case UP:
		RotateBlock(m_pCurPosition);
		break;
	}
	return SUCCESS;
}

int Tetris::CheckCollision(POINT nextpos)
{		
	this->RemoveBlock(m_pCurPosition);

	for (int i = 0; i < Y_Block_SIZE; i++)
	{
		for (int j = 0; j < X_Block_SIZE; j++)
		{
			if(this->m_cCurBlock[i][j] == 1 && this->m_cMap[nextpos.y + i + 1][nextpos.x + j] == 1)
			{
				this->RecoveryBlock(m_pCurPosition);
				return FAIL;
			}
		}
	}

	return SUCCESS;
}

int Tetris::SetGameCycle(int cycle)
{
	if(cycle > 5000 || cycle < 0)
		return FAIL;

	this->m_iGameSpeed = cycle;

	return SUCCESS;
}

int Tetris::GetGameCycle()
{
	return this->m_iGameSpeed;
}

int Tetris::SetScore(int score)
{
	if(score > 400 || score < 0)
		return FAIL;

	this->m_iScore += score; 

	return SUCCESS;
}

int Tetris::GetScore()
{
	return this->m_iScore;
}

int Tetris::RotateBlock(POINT curpos) // 블럭 회전 
{
	int shape = 0, recoveryvalue = 0;

	recoveryvalue = m_iCurBlockRType; // 현재 로테이션 값을 임시로 저장

	if (m_iCurBlockRType >= 0 && m_iCurBlockRType < 3) // 현재 로테이션 값이 0 ~ 2일때 다음 로테이션값 증가
		m_iCurBlockRType++;
	else if (m_iCurBlockRType == 3)  // 현재 로테이션 값이 3일 때는 다음 로테이션 값을 0으로 변환 
		m_iCurBlockRType = 0;

	shape = (m_iCurBlockType * NUMBER_OF_ROTATION) + m_iCurBlockRType;

	this->RemoveBlock(m_pCurPosition);

	for (int i = 0; i < Y_Block_SIZE; i++) //임시 공간에 모양 생성
		for (int j = 0; j < X_Block_SIZE; j++) {
			m_cCurBlock[i][j] = m_cAllBlocks[shape][i][j];
		}

	if (CheckRotation(m_pCurPosition) != SUCCESS) // 충돌 O
	{
		 m_iCurBlockRType = recoveryvalue; // 다음 로테이션 값에서 이전 로테이션 값으로 복구

		 shape = (m_iCurBlockType * NUMBER_OF_ROTATION) + m_iCurBlockRType;

		 for (int i = 0; i < Y_Block_SIZE; i++)		
			 for (int j = 0; j < X_Block_SIZE; j++) 			
				 m_cCurBlock[i][j] = m_cAllBlocks[shape][i][j];
				
		 this->RecoveryBlock(m_pCurPosition);
	}
	else // 충돌 x 
	{
		this->RecoveryBlock(m_pCurPosition);
	}

	return SUCCESS;
}

int Tetris::RemoveBlock(POINT curpos)
{
	for (int i = 0; i < Y_Block_SIZE; i++)
	{
		for (int j = 0; j < X_Block_SIZE; j++)
		{
			if(m_cMap[curpos.y + i][curpos.x + j] == 1 && m_cCurBlock[i][j] == 1)
				m_cMap[curpos.y + i][curpos.x + j] = 0;
		}
	}

	return SUCCESS;
}

int Tetris::RecoveryBlock(POINT curpos)
{
	for (int i = 0; i < Y_Block_SIZE; i++)
	{
		for (int j = 0; j < X_Block_SIZE; j++)
		{
			if(m_cCurBlock[i][j] == 1)
				m_cMap[curpos.y + i][curpos.x + j] = m_cCurBlock[i][j];
		}
	}

	return SUCCESS;
}

int Tetris::CheckLine()
{
	int totalBlock = 0, cnt = 0;

	for(int i = 0; i < Y_MAP_SIZE - 1; i++)
	{
		totalBlock = 0; // 블럭 총 갯수 초기화

		for(int j = 1; j < X_MAP_SIZE - 1; j++)
		{
			if(m_cMap[i][j] == 1)
				totalBlock++;
		}

		if(totalBlock >= FULL)
		{
			this->SetScore(10);
			for(int Newi = i; Newi > 1; Newi--)
			{
				for(int Newj = 1; Newj < X_MAP_SIZE - 1; Newj ++)
					m_cMap[Newi][Newj] = m_cMap[Newi - 1][Newj];
			}
		}
	}

	return SUCCESS;
}

int Tetris::CheckFinish()
{
	if(CheckCollision(m_pCurPosition) == SUCCESS)
	{
		MoveBlock(DOWN);
		m_bFInishFLag = false;
	}

	else if(CheckCollision(m_pCurPosition) == SUCCESS && m_bFInishFLag == true)
	{
		m_bFInishFLag = false;		
	}

	else if(CheckCollision(m_pCurPosition) == FAIL && m_bFInishFLag == false)
	{
		m_bFInishFLag = true;	
	}

	else if(CheckCollision(m_pCurPosition) == FAIL && m_bFInishFLag == true)
	{
		for (int i = 0; i < Y_Block_SIZE; i++)	
			for (int j = 0; j < X_Block_SIZE; j++)
				if(m_cCurBlock[i][j] == 1)
					m_cMapCopy[m_pCurPosition.y + i][m_pCurPosition.x + j] = m_cCurBlock[i][j];

		CheckLine();
		InitGame();
		m_bFInishFLag = false;		
		return FAIL;
	}
	return SUCCESS;
}

int Tetris::CheckRotation(POINT nextpos)
{
	for (int i = 0; i < Y_Block_SIZE; i++)
	{
		for (int j = 0; j < X_Block_SIZE; j++)
		{
			if(this->m_cCurBlock[i][j] == 1 && this->m_cMap[nextpos.y + i + 1][nextpos.x + j] == 1)
			{
				return FAIL;
			}
		}
	}

	return SUCCESS;
}

int Tetris::EndGame()
{
	this->m_pCurPosition.y ++;

	if(CheckCollision(this->m_pCurPosition) == FAIL)
	{		
		return FAIL;
	}

	return SUCCESS;
}

void Tetris::ChangeNextColor()
{
	srand( (unsigned int)(time(NULL)) );

	while(1){
	this->m_iNextColor = rand() % 16;

	if( this->m_iNextColor > 8 && this->m_iNextColor <15)
		break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),this->m_iNextColor);
}

void Tetris::ChangeCurColor()
{
	m_iCurColor = m_iNextColor;
}

void Tetris::Ending()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	printf("▥▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▥\n");
	Sleep(100);
	
	for(int i = 0; i < 6; i++)
	{
		printf("▥                              ▥\n");
		Sleep(100);
	}
	
	printf("▥    수 고 하 셨 습 니 다      ▥\n");
	if(this->m_iScore == 0)
		printf("▥  최종스코어는 [%d점] 입니다   ▥\n",this->m_iScore);
	else if(this->m_iScore > 0 && this->m_iScore < 100)
		printf("▥  최종스코어는 [%d점] 입니다  ▥\n",this->m_iScore);
	else
		printf("▥ 최종스코어는 [%d점] 입니다  ▥\n",this->m_iScore);
	
	for(int i = 0; i < 6; i++)
	{
		printf("▥                              ▥\n");
		Sleep(100);
	}
	printf("▥▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▥\n");
	Sleep(100);

	Sleep(5000);
	m_bGameFinish = true;	
}

void Tetris::Opening()
{
	printf("▥▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▥\n");
	Sleep(100);
	
	for(int i = 0; i < 6; i++)
	{
		printf("▥                              ▥\n");
		Sleep(100);
	}
	
	printf("▥    T E T R I S  G A M E      ▥\n");
	printf("▥     게임을 시작하려면        ▥\n");
	printf("▥     Enter키를 누르세요       ▥\n");
	
	for(int i = 0; i < 6; i++)
	{
		printf("▥                              ▥\n");
		Sleep(100);
	}
	printf("▥▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▥\n");
	Sleep(100);

	getchar();

	system("cls");
}

void Tetris::ShowNextBlock()
{
	POINT NextBlockPos;	
	ChangeCurColor();
	ChangeNextColor();
	NextBlockPos.x = 20;
	NextBlockPos.y = 5;
	gotoxy(NextBlockPos);

	for (int i = 0; i < Y_Block_SIZE; i++)
	{
		for (int j = 0; j < X_Block_SIZE; j++)
		{ 
			if(m_cNextBlock[i][j] == 1)
				printf("■");
			else
				printf("  ");
		}		
		NextBlockPos.y++;
		gotoxy(NextBlockPos);
	}	
}

void Tetris::ShowNextBlockBoard()
{
	POINT NextBlockPos;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	NextBlockPos.x = 17;
	NextBlockPos.y = 2;
	gotoxy(NextBlockPos); printf("※ Next Block[%d]※",m_iCurBlockType);
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣▣▣▣▣▣▣▣▣");
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣              ▣");
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣              ▣");
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣              ▣");
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣              ▣");
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣              ▣");
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣              ▣");
	NextBlockPos.y++;  gotoxy(NextBlockPos);  printf("▣▣▣▣▣▣▣▣▣");
}

void Tetris::gotoxy(POINT pos)
{
	COORD CursorPos = {pos.x * 2, pos.y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CursorPos);
}

void Tetris::ShowScore()
{
	POINT pos = {18,14};	
	gotoxy(pos);
	printf("Score = %d",GetScore());
}

void Tetris::ShowGameSpeed()
{
	POINT pos = {18,16};	
	gotoxy(pos);
	printf("Game Speed = %dms",GetGameCycle());
}