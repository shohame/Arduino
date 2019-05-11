#include "StdAfx.h"
#include "General.h"
#include "Brick.h"
#include "Ball.h"
#include "Price.h"
#include "Fire.h"
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
	int8 i;

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

	for (i=0; i<m_FireCount; i++)
	{
		m_Fire_arr[i].MarkBrickOnMatrix();
	}

	m_Stick.MarkBrickOnMatrix();
}


void Bricks::MoveAllBalls(int16 a_dT_mSec)
{
	int8 i, BrickID;
	Ball *pBall;

	for (i=0; i<m_BallCount; i++)
	{
		pBall = &m_Ball_arr[i];

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
				AddPrice(ROUND_CORD_TO_U8(m_Brick_arr[BrickID].m_Loc_s.m_X), ROUND_CORD_TO_U8(m_Brick_arr[BrickID].m_Loc_s.m_Y));
			}
			RemoveBrick(BrickID);	// Remove just if BrickID>=0 !
			m_Disply.AddScore(125);
		}
		pBall->Where_I_TouchStick(&m_Stick);
	}
}

void Bricks::MoveAllFires(int16 a_dT_mSec)
{
	int8 i, BrickID;
	Fire *pFire;

	for (i=0; i<m_FireCount; i++)
	{
		pFire = &m_Fire_arr[i];

		pFire->MoveBall(a_dT_mSec);

		BrickID = pFire->FindBallCollision(m_Wall_arr, m_WallCount);
		if (BrickID>=0)
			RemoveFire(i);

		BrickID = pFire->FindBallCollision(m_Brick_arr, m_BrickCount);
		if (BrickID>=0)
		{
			if (RAND_INT(0, GIVE_PRICE_RATE) == 0)
			{
				AddPrice(ROUND_CORD_TO_U8(m_Brick_arr[BrickID].m_Loc_s.m_X), ROUND_CORD_TO_U8(m_Brick_arr[BrickID].m_Loc_s.m_Y));
			}
			RemoveBrick(BrickID);	// Remove just if BrickID>=0 !
			RemoveFire(i);
			i--;
			m_Disply.AddScore(125);
		}
		
	}
}



void Bricks::GetThePrice(ePriceType a_eType, int8 a_x, int8 a_y)
{
	switch(a_eType)
	{
		case(eLarge):
		{
			m_Stick.ChangeStickType(eStickLarge);
			break;
		}
		case(eSmall):
		{
			m_Stick.ChangeStickType(eStickSmall);
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
		case(eFire):
		{
			m_Stick.ChangeStickType(eStickFire);
			break;
		}
	}
}

void Bricks::MoveAllPrices(int16 a_dT_mSec)
{
	int8 i, Remove;
	Price *pPrice;

	for (i=0; i<m_PriceCount; i++)
	{
		pPrice = &m_Price_arr[i];
		Remove = false;
		pPrice->MoveBall(a_dT_mSec);

		if (pPrice->Where_I_TouchStick(&m_Stick))
		{	
			GetThePrice(pPrice->m_eType, ROUND_CORD_TO_U8(pPrice->m_Loc_s.m_X), ROUND_CORD_TO_U8(pPrice->m_Loc_s.m_Y));
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
  m_FireCount = 0;
}

void Bricks::AddBrick(int8 a_x, int8 a_y)
{
	assert(m_BrickCount < MAX_NUM_OF_BREAKS);
	if ( m_BrickCount < MAX_NUM_OF_BREAKS)
	{
		m_Brick_arr[m_BrickCount].SetPos(a_x, a_y);
		m_BrickCount++;
	}
}


void Bricks::AddBall(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy )
{
	assert(m_BallCount < MAX_NUM_OF_BALLS);
	if (m_BallCount < MAX_NUM_OF_BALLS)
	{
		m_Ball_arr[m_BallCount].SetPos(a_x, a_y);
		m_Ball_arr[m_BallCount].SetSpeed(a_Vx, a_Vy);
		m_BallCount++;
	}
}



void Bricks::AddWall(int8 a_x, int8 a_y, int8 a_w, int8 a_h)
{
	assert(m_WallCount < MAX_NUM_OF_WALLS);
	if (m_WallCount < MAX_NUM_OF_WALLS)
	{
		m_Wall_arr[m_WallCount].SetLoc(a_x, a_y, a_w, a_h);
		m_WallCount++;
	}
}

void Bricks::AddPrice(int8 a_x, int8 a_y)
{
	Price* pPrice;
//	assert(m_PriceCount < MAX_NUM_OF_PRICE);
	if (m_PriceCount < MAX_NUM_OF_PRICE)
	{
		pPrice = &m_Price_arr[m_PriceCount];
		pPrice->SetPos(a_x, a_y);
		pPrice->m_V_s.m_X = 0;
		pPrice->m_V_s.m_Y = PRICE_DEFAULT_SPEED;
		pPrice->m_eType = (ePriceType) ((int8)eLarge +(int8)RAND_INT(0, PRICE_TYPE_COUNT));
		m_PriceCount++;
	}
}

void Bricks::AddFire(int8 a_x, int8 a_y)
{
	Fire* pFire;
	if (m_FireCount < MAX_NUM_OF_FIRE)
	{
		pFire = &m_Fire_arr[m_FireCount];
		pFire->SetPos(a_x, a_y);
		pFire->m_V_s.m_X = 0;
		pFire->m_V_s.m_Y = FIRE_DEFAULT_SPEED;
		m_FireCount++;
	}
}


void Bricks::RemoveBrick(int8 a_BrickIdx)
{
	assert((a_BrickIdx >= 0) && (a_BrickIdx < m_BrickCount));

	if ( (a_BrickIdx >= 0) && (a_BrickIdx < m_BrickCount) )
	{
		m_Brick_arr[a_BrickIdx] = m_Brick_arr[m_BrickCount-1];
		m_BrickCount--;
	}
}

void Bricks::RemoveBall(int8 a_BallIndex)
{
	assert((a_BallIndex >= 0) && (a_BallIndex < m_BallCount));
	if (a_BallIndex<m_BallCount)
	{
		m_Ball_arr[a_BallIndex] = m_Ball_arr[m_BallCount-1];
		m_BallCount--;
	}
}

void Bricks::RemoveWall(int8 a_WallIndex)
{
	assert((a_WallIndex >= 0) && (a_WallIndex < m_WallCount));
	if (a_WallIndex<m_WallCount)
	{
		m_Wall_arr[a_WallIndex].m_Loc_s = m_Wall_arr[m_WallCount-1].m_Loc_s;
		m_WallCount--;
	}
}

void Bricks::RemovePrice(int8 a_PriceIndex)
{
	assert((a_PriceIndex >= 0) && (a_PriceIndex < m_PriceCount));
	if (a_PriceIndex<m_PriceCount)
	{
		m_Price_arr[a_PriceIndex] = m_Price_arr[m_PriceCount-1];
		m_PriceCount--;
	}
}

void Bricks::RemoveFire(int8 a_FireIndex)
{
	assert((a_FireIndex >= 0) && (a_FireIndex < m_FireCount));
	if (a_FireIndex<m_FireCount)
	{
		m_Fire_arr[a_FireIndex] = m_Fire_arr[m_FireCount-1];
		m_FireCount--;
	}
}

void Bricks::InitLeve_Clear()
{
	ClearAllBricksBallsWalls();

	m_Stick.ChangeStickType(eStickRegular);

	AddWall(32,-1, 1, 34);	// Right wall
	AddWall(-1,-1, 1, 34);	// Left wall
	AddWall(0,6,32, 1);		// Top wall
	AddWall(24,0,1, 6);		// Score / Life divader 
}

void Bricks::AddLineOfBricks(int8 a_x0, int8 a_y0, int8 a_Count)
{
	for(int8 x=0; x<a_Count; x++)
	{
		AddBrick(a_x0 + x*(BREAK_DEFAULT_WIDTH+1), a_y0);
	}
}


void Bricks::InitLevel(int8 a_Level)
{
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
		AddLineOfBricks(2, 15, 7);

		AddWall(0, 12, 11, 1);	
		AddWall(21 ,12,11 , 1);	
		break;

	case 4:
		AddLineOfBricks(0, 8,  8);
		AddLineOfBricks(2, 11, 7);

		AddWall(0, 16, 17, 1);	
		AddWall(22 ,16,6 , 1);	
		AddWall(0, 23, 9, 1);	
		AddWall(15, 23, 13, 1);	
		break;
	case 5:
		AddLineOfBricks(0, 8,  8);

		AddBrick(3, 21);
		AddBrick(26, 21);

		AddWall(0, 13, 12, 1);	
		AddWall(17, 13, 7, 1);	
		AddWall(11, 17, 6, 1);	
		AddWall(0, 21, 3, 2);	
		AddWall(6, 21, 20, 2);	
		AddWall(29, 21, 3, 2);	


		break;

	}

	AddBall(16,28, 3, -6.0);

}

