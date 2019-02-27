#include "StdAfx.h"
#include <math.h>
#include "Ball.h"


Ball::Ball(void)
{
	m_Loc_s.m_w = BALL_DEFAULT_WIDTH;
	m_Loc_s.m_h = BALL_DEFAULT_HEIGHT;
}


Ball::~Ball(void)
{
	
}


void Ball::ChangeAngleBy(float a_dAngle)
{

	float A = sqrt(POW2(m_V_s.m_X) + POW2(m_V_s.m_Y));
	float ang = RAD2DEG(atan2(m_V_s.m_Y, m_V_s.m_X));
	if (ang>(-90 + MAX_ANGLE) || ang<(-90 - MAX_ANGLE) )
	{
		int stop=1;
	}
	ang += a_dAngle;

	ang = MIN(-90 + MAX_ANGLE, ang);
	ang = MAX(-90 - MAX_ANGLE, ang);

	m_V_s.m_X = A * cos(  DEG2RAD(ang) );
	m_V_s.m_Y = A * sin(  DEG2RAD(ang) );

}


char Ball::Where_I_TouchStick (Break * a_pStick)
{
	stLoc	Y_Loc = a_pStick->m_Loc_s;
	stLoc	M_Loc = m_Loc_s;

	float Y_half_w =  Y_Loc.m_w / 2.0;
	float M_half_w =  M_Loc.m_w / 2.0;
	float Y_half_h =  Y_Loc.m_h / 2.0;
	float M_half_h =  M_Loc.m_h / 2.0;

	float Y_Cx = Y_Loc.m_X + Y_half_w;
	float M_Cx = M_Loc.m_X + M_half_w;
	float Y_Cy = Y_Loc.m_Y + Y_half_h;
	float M_Cy = M_Loc.m_Y + M_half_h;

	float dX  = ( Y_half_w + M_half_w) - abs( Y_Cx - M_Cx); // if dX > 0  ==> Thay can be tuched!
	float dY  = ( Y_half_h + M_half_h) - abs( Y_Cy - M_Cy); // if dy > 0  ==> Thay can be tuched!

	if ( dX > 0 && dY > 0) // 
	{
		if (m_V_s.m_Y<0)
			m_V_s.m_Y = m_V_s.m_Y;

		Bounce(HORIZONTAL, dY);

		float dAngle = 45 * (M_Cx - Y_Cx) / Y_half_w;
		ChangeAngleBy(dAngle);
	}
	return -1;
}

char Ball::FindBallCollision(Break a_Break_arr[], char a_BreakCount)
{
	char i = -1;
	char isTuching;
	float D;
	for (i=0; i<a_BreakCount; i++)
	{
		isTuching = WhereBreakTouchMe(&a_Break_arr[i], &D);
		if (isTuching > 0)
		{
			Bounce(isTuching, D);
			return i;
		}
	}
	return -1;
}


void Ball::SetSpeed(stVector* a_pV)
{
	m_V_s.m_X = a_pV->m_X;
	m_V_s.m_Y = a_pV->m_Y;
}

void Ball::SetSpeed(float a_Vx, float a_Vy)
{
	m_V_s.m_X = a_Vx;
	m_V_s.m_Y = a_Vy;
}

void Ball::MoveBall(int a_dT_mSec)
{
	m_Loc_s.m_X +=  m_V_s.m_X * a_dT_mSec / 1000.0;
	m_Loc_s.m_Y +=  m_V_s.m_Y * a_dT_mSec / 1000.0;
}

void Ball::Bounce(char a_Direction, float a_Depth = 0)
{
	if (a_Direction == HORIZONTAL)
	{
		m_Loc_s.m_Y -= fSIGN( m_V_s.m_Y ) * 2 * a_Depth; 		
		m_V_s.m_Y = -m_V_s.m_Y;

	}

	if (a_Direction == VERTICAL)
	{
		float BBB = fSIGN( m_V_s.m_X );
		float AAA = BBB * a_Depth;

		m_Loc_s.m_X -= fSIGN( m_V_s.m_X ) * a_Depth; 		
		m_V_s.m_X = -m_V_s.m_X;
	}
}


