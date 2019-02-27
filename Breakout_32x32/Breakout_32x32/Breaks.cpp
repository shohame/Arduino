#include "StdAfx.h"
#include "Break.h"
#include "Ball.h"
#include "Stick.h"
#include "Display.h"
#include "Breaks.h"


Breaks::Breaks(void)
{
	ClearAllBreaksBallsWalls();
}
Breaks::~Breaks(void)
{
}

void Breaks::MarkBreaksOnMatrix()
{
	char i;

	for (i=0; i<m_BreakCount; i++)
	{
		m_Break_arr[i].MarkBreakOnMatrix();
	}
	for (i=0; i<m_BallCount; i++)
	{
		m_Ball_arr[i].MarkBreakOnMatrix();
	}
	for (i=0; i<m_WallCount; i++)
	{
		m_Wall_arr[i].MarkBreakOnMatrix();
	}

	m_Stick.MarkBreakOnMatrix();
}





void Breaks::MoveAllBalls(int a_dT_mSec)
{
	char i,j;
	float D;
	char BreakID;
	char isTuching;
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
			pBall->SetPos(-100, -100); // -100 indicate it's need to be deleted
			continue;
		}

		BreakID = pBall->FindBallCollision(m_Wall_arr, m_WallCount);
		BreakID = pBall->FindBallCollision(m_Break_arr, m_BreakCount);
		if (BreakID>=0)
		{
			RemoveBreak(BreakID);	// Remove just if BreakID>=0 !
			m_Score.AddScore(125);
		}
		pBall->Where_I_TouchStick(&m_Stick);
	}

	for (i=0; i<m_BallCount; i++)
	{
		pBall = &m_Ball_arr[i];
		if (pBall->m_Loc_s.m_X < -99)		
		{
			RemoveBall(i);
			i--;			// To chack the index again, if we have copyed the last that need to be deleted !!!
		}
	}

}


void Breaks::ClearAllBreaksBallsWalls()
{
	m_BreakCount = 0;
	m_BallCount = 0;
	m_WallCount = 0;
}

void Breaks::AddBreak(char a_x, char a_y)
{
	assert(m_BreakCount < MAX_NUM_OF_BREAKS);
	if ( m_BreakCount < MAX_NUM_OF_BREAKS)
	{
		m_Break_arr[m_BreakCount].SetPos(a_x, a_y);
		m_BreakCount++;
	}
}


void Breaks::AddBall(char a_x, char a_y, float a_Vx, float a_Vy )
{
	assert(m_BallCount < MAX_NUM_OF_BALLS);
	if (m_BallCount < MAX_NUM_OF_BALLS)
	{
		m_Ball_arr[m_BallCount].SetPos(a_x, a_y);
		m_Ball_arr[m_BallCount].SetSpeed(a_Vx, a_Vy);
		m_BallCount++;
	}
}



void Breaks::AddWall(char a_x, char a_y, char a_w, char a_h)
{
	assert(m_WallCount < MAX_NUM_OF_WALLS);
	if (m_WallCount < MAX_NUM_OF_WALLS)
	{
		m_Wall_arr[m_WallCount].SetLoc(a_x, a_y, a_w, a_h);
		m_WallCount++;
	}
}


void Breaks::RemoveBreak(char a_BreakIdx)
{
	assert((a_BreakIdx >= 0) && (a_BreakIdx < m_BreakCount));

	if ( (a_BreakIdx >= 0) && (a_BreakIdx < m_BreakCount) )
	{
		m_Break_arr[a_BreakIdx].m_Loc_s = m_Break_arr[m_BreakCount-1].m_Loc_s;;
		m_BreakCount--;
	}
}

void Breaks::RemoveBall(char a_BallIndex)
{
	assert((a_BallIndex >= 0) && (a_BallIndex < m_BallCount));
	if (a_BallIndex<m_BallCount)
	{
		m_Ball_arr[a_BallIndex].m_Loc_s = m_Ball_arr[m_BallCount-1].m_Loc_s;
		m_Ball_arr[a_BallIndex].m_V_s = m_Ball_arr[m_BallCount-1].m_V_s;
		m_BallCount--;
	}
}

void Breaks::RemoveWall(char a_WallIndex)
{
	assert((a_WallIndex >= 0) && (a_WallIndex < m_WallCount));
	if (a_WallIndex<m_WallCount)
	{
		m_Wall_arr[a_WallIndex].m_Loc_s = m_Wall_arr[m_WallCount-1].m_Loc_s;
		m_WallCount--;
	}
}


void Breaks::InitLevel_1()
{
	char line, x;
	char Nx, X0;

	ClearAllBreaksBallsWalls();


	AddBall(16,28, 3, -6.0);
// 	AddBall(16,27, -0.0, 5.0);
// 	AddBall(16,27, -1.0, 4.0);
 //	AddBall(16,27, -2.0, 3.0);

	AddWall(32,-1, 1, 34);
	AddWall(-1,-1, 1, 34);
	AddWall(0,6,32, 1);
	AddWall(24,0,1, 6);
	AddWall(-1,32, 34,1); // need to remove this !!!

	 for (line=0; line<4; line++)
	 {
		Nx = 8 - (line & 1);	// first line (top) 8; next line 7; and so on!
		X0 = 0 + (line & 1)*2;	// first line (top) 0; next line 2; and so on! 

		for(x=0; x<Nx; x++)
		{
			AddBreak(X0 + x*(BREAK_DEFAULT_WIDTH+1), 8 + line*(BREAK_DEFAULT_HEIGHT+1));
		}
	 }
}
void Breaks::InitLevel_dummy()
{
	char line, x;
	char Nx, X0;

	ClearAllBreaksBallsWalls();


	AddBall(16,28, 3, -6.0);
// 	AddBall(16,27, -0.0, 5.0);
// 	AddBall(16,27, -1.0, 4.0);
 //	AddBall(16,27, -2.0, 3.0);

	AddWall(27,-1, 2, 34);		// Right
	AddWall(3,-1, 2, 34);		// Left
	AddWall(0,6,32, 2);			// Top
	AddWall(-1,32, 34,1); // need to remove this !!!

}