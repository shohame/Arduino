#include "StdAfx.h"
#include "Brick.h"
#include "Ball.h"
#include "Price.h"
#include "Stick.h"
#include "Display.h"
#include "Bricks.h"


Bricks::Bricks(void)
{
	ClearAllBricksBallsWalls();
}
Bricks::~Bricks(void)
{
}

void Bricks::MarkBricksOnMatrix()
{
	char i;

	for (i=0; i<m_BrickCount; i++)
	{
		m_Brick_arr[i].MarkBrickOnMatrix();
	}

	for (i=0; i<m_BallCount; i++)
	{
		m_Ball_arr[i].MarkBrickOnMatrix();
	}

	for (i=0; i<m_WallCount; i++)
	{
		m_Wall_arr[i].MarkBrickOnMatrix();
	}

	for (i=0; i<m_PriceCount; i++)
	{
		m_Price_arr[i].MarkBrickOnMatrix();
	}

	m_Stick.MarkBrickOnMatrix();
}


void Bricks::MoveAllBalls(int a_dT_mSec)
{
	char i, BrickID;
	Ball *pBall;

	for (i=0; i<m_BallCount; i++)
	{
		pBall = &m_Ball_arr[i];
		if (ABS(pBall->m_V_s.m_Y) < 1.5)
		{
			pBall->m_V_s.m_Y = 1.5;
		}

		pBall->MoveBall(a_dT_mSec);

		if (pBall->m_Loc_s.m_Y >= 30)
		{
			RemoveBall(i);
			i--;		// We moveed the last index to index i, so we need to go back to index i !!!
			continue;
		}

		BrickID = pBall->FindBallCollision(m_Wall_arr, m_WallCount);
		BrickID = pBall->FindBallCollision(m_Brick_arr, m_BrickCount);
		if (BrickID>=0)
		{
			if (RAND_INT(0, GIVE_PRICE_RATE) == 0)
			{
				AddPrice(m_Brick_arr[BrickID].m_Loc_s.m_X, (m_Brick_arr[BrickID].m_Loc_s.m_Y));
			}
			RemoveBrick(BrickID);	// Remove just if BrickID>=0 !
			m_Disply.AddScore(125);
		}
		pBall->Where_I_TouchStick(&m_Stick);
	}
}



void Bricks::GetThePrice(ePriceType a_eType, char a_x, char a_y)
{
	switch(a_eType)
	{
		case(eLarge):
		{
			m_Stick.m_Loc_s.m_w = STICK_DEFAULT_WIDTH + 2;
			break;
		}
		case(eSmall):
		{
			m_Stick.m_Loc_s.m_w = STICK_DEFAULT_WIDTH - 2;
			break;
		}
		case(eThree):
		{
			AddBall(a_x, a_y, 2, -4	);
			AddBall(a_x, a_y, -2, -3);
			AddBall(a_x, a_y, 0, -7	);
			break;
		}
		case(eBall):
		{
			if (m_Disply.m_Life<9)
				m_Disply.m_Life++;
			break;
		}
	}
}

void Bricks::MoveAllPrices(int a_dT_mSec)
{
	char i, Remove;
	Price *pPrice;

	for (i=0; i<m_PriceCount; i++)
	{
		pPrice = &m_Price_arr[i];
		Remove = false;
		pPrice->MoveBall(a_dT_mSec);

		if (pPrice->m_Loc_s.m_Y >= 30)
		{
			Remove = true;
		}

		if (pPrice->Where_I_TouchStick(&m_Stick))
		{	
			GetThePrice(pPrice->m_eType, pPrice->m_Loc_s.m_X, pPrice->m_Loc_s.m_Y);
			Remove = true;
		}

		if (Remove)
		{
			RemovePrice(i);
			i--;		// We moveed the last index to index i, so we need to go back to index i !!!
		}
	}


}

void Bricks::ClearAllBricksBallsWalls()
{
	m_BrickCount = 0;
	m_BallCount = 0;
	m_WallCount = 0;
	m_PriceCount = 0;
}

void Bricks::AddBrick(char a_x, char a_y)
{
	assert(m_BrickCount < MAX_NUM_OF_BREAKS);
	if ( m_BrickCount < MAX_NUM_OF_BREAKS)
	{
		m_Brick_arr[m_BrickCount].SetPos(a_x, a_y);
		m_BrickCount++;
	}
}


void Bricks::AddBall(char a_x, char a_y, float a_Vx, float a_Vy )
{
	assert(m_BallCount < MAX_NUM_OF_BALLS);
	if (m_BallCount < MAX_NUM_OF_BALLS)
	{
		m_Ball_arr[m_BallCount].SetPos(a_x, a_y);
		m_Ball_arr[m_BallCount].SetSpeed(a_Vx, a_Vy);
		m_BallCount++;
	}
}



void Bricks::AddWall(char a_x, char a_y, char a_w, char a_h)
{
	assert(m_WallCount < MAX_NUM_OF_WALLS);
	if (m_WallCount < MAX_NUM_OF_WALLS)
	{
		m_Wall_arr[m_WallCount].SetLoc(a_x, a_y, a_w, a_h);
		m_WallCount++;
	}
}

void Bricks::AddPrice(char a_x, char a_y)
{
	Price* pPrice;
//	assert(m_PriceCount < MAX_NUM_OF_PRICE);
	if (m_PriceCount < MAX_NUM_OF_PRICE)
	{
		pPrice = &m_Price_arr[m_PriceCount];
		pPrice->SetPos(a_x, a_y);
		pPrice->m_V_s.m_X = 0;
		pPrice->m_V_s.m_Y = PRICE_DEFAULT_SPEED;
		pPrice->m_eType =(ePriceType) ( (int)eLarge + RAND_INT(0, PRICE_TYPE_COUNT));
		m_PriceCount++;
	}
}


void Bricks::RemoveBrick(char a_BrickIdx)
{
	assert((a_BrickIdx >= 0) && (a_BrickIdx < m_BrickCount));

	if ( (a_BrickIdx >= 0) && (a_BrickIdx < m_BrickCount) )
	{
		m_Brick_arr[a_BrickIdx] = m_Brick_arr[m_BrickCount-1];
		m_BrickCount--;
	}
}

void Bricks::RemoveBall(char a_BallIndex)
{
	assert((a_BallIndex >= 0) && (a_BallIndex < m_BallCount));
	if (a_BallIndex<m_BallCount)
	{
		m_Ball_arr[a_BallIndex] = m_Ball_arr[m_BallCount-1];
		m_BallCount--;
	}
}

void Bricks::RemoveWall(char a_WallIndex)
{
	assert((a_WallIndex >= 0) && (a_WallIndex < m_WallCount));
	if (a_WallIndex<m_WallCount)
	{
		m_Wall_arr[a_WallIndex].m_Loc_s = m_Wall_arr[m_WallCount-1].m_Loc_s;
		m_WallCount--;
	}
}

void Bricks::RemovePrice(char a_PriceIndex)
{
	assert((a_PriceIndex >= 0) && (a_PriceIndex < m_PriceCount));
	if (a_PriceIndex<m_PriceCount)
	{
		m_Price_arr[a_PriceIndex] = m_Price_arr[m_PriceCount-1];
		m_PriceCount--;
	}
}

void Bricks::InitLeve_Clear()
{
	ClearAllBricksBallsWalls();
	m_Stick.m_Loc_s.m_w = STICK_DEFAULT_WIDTH;

	AddWall(32,-1, 1, 34);	// Right wall
	AddWall(-1,-1, 1, 34);	// Left wall
	AddWall(0,6,32, 1);		// Top wall
	AddWall(24,0,1, 6);		// Score / Life divader 
}

void Bricks::AddLineOfBricks(char a_x0, char a_y0, char a_Count)
{
	for(char x=0; x<a_Count; x++)
	{
		AddBrick(a_x0 + x*(BREAK_DEFAULT_WIDTH+1), a_y0);
	}
}


void Bricks::InitLevel(char a_Level)
{
	char line, x;
	char Nx, X0;

	InitLeve_Clear();
	switch(a_Level)
	{
	case 1:
		AddLineOfBricks(0, 8,  8);
		AddLineOfBricks(2, 11, 7);
		break;	
	case 2:
		AddLineOfBricks(0, 8,  8);
		AddLineOfBricks(2, 11, 7);
		AddLineOfBricks(0, 14,  8);
		AddLineOfBricks(2, 17,  7);
		break;
	case 3:
		AddLineOfBricks(0, 8,  8);
		AddLineOfBricks(2, 11, 7);

		AddWall(0, 16, 17, 1);	
		AddWall(22 ,16,6 , 1);	
		AddWall(0, 23, 9, 1);	
		AddWall(15, 23, 13, 1);	
	}

	AddBall(16,28, 3, -6.0);

}

