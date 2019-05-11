#include "StdAfx.h"
#include <math.h>
#include "Ball.h"

Ball::Ball(void)
{
	Init();
}

void Ball::Init(void)
{
	m_Acceleration = BALL_DEFAULT_ACCSELERATION;
	m_Loc_s.m_w = BALL_DEFAULT_WIDTH;
	m_Loc_s.m_h = BALL_DEFAULT_HEIGHT;
}


Ball::~Ball(void)
{
	
}


void Ball::ChangeAngleBy(float32 a_dAngle)
{

	float32 A = sqrt(POW2(m_V_s.m_X) + POW2(m_V_s.m_Y));
	float32 ang = RAD2DEG(atan2(m_V_s.m_Y, m_V_s.m_X));

	ang += a_dAngle;

	ang = MIN(-90 + MAX_ANGLE, ang);
	ang = MAX(-90 - MAX_ANGLE, ang);

	m_V_s.m_X = A * (float32)cos(  DEG2RAD(ang) );
	m_V_s.m_Y = A * (float32)sin(  DEG2RAD(ang) );

}


int8 Ball::Where_I_TouchStick (Brick * a_pStick)
{
	stLoc	Y_Loc = a_pStick->m_Loc_s;
	stLoc	M_Loc = m_Loc_s;

	float32 Y_half_w =  (float32)Y_Loc.m_w / 2.0f;
	float32 M_half_w =  (float32)M_Loc.m_w / 2.0f;
	float32 Y_half_h =  (float32)Y_Loc.m_h / 2.0f;
	float32 M_half_h =  (float32)M_Loc.m_h / 2.0f;

	float32 Y_Cx = Y_Loc.m_X + Y_half_w;
	float32 M_Cx = M_Loc.m_X + M_half_w;
	float32 Y_Cy = Y_Loc.m_Y + Y_half_h;
	float32 M_Cy = M_Loc.m_Y + M_half_h;

	float32 dX  = ( Y_half_w + M_half_w) - abs( Y_Cx - M_Cx); // if dX > 0  ==> Thay can be tuched!
	float32 dY  = ( Y_half_h + M_half_h) - abs( Y_Cy - M_Cy); // if dy > 0  ==> Thay can be tuched!

	if ( dX > 0 && dY > 0) // 
	{
		if (m_V_s.m_Y<0)
			m_V_s.m_Y = m_V_s.m_Y;

		Bounce(HORIZONTAL, dY);

		float32 dAngle = 45 * (M_Cx - Y_Cx) / Y_half_w;
		ChangeAngleBy(dAngle);
		return 1;
	}
	return 0;
}

int8 Ball::FindBallCollision(Brick a_Brick_arr[], int8 a_BrickCount)
{
	int8 i = -1;
	int8 isTuching;
	float32 D;
	for (i=0; i<a_BrickCount; i++)
	{
		isTuching = WhereBrickTouchMe(&a_Brick_arr[i], &D);
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

void Ball::SetSpeed(float32 a_Vx, float32 a_Vy)
{
	m_V_s.m_X = a_Vx;
	m_V_s.m_Y = a_Vy;
}

void Ball::MoveBall(int16 a_dT_mSec)
{
	m_Loc_s.m_X +=  m_V_s.m_X * (float32)a_dT_mSec / 1000.0f;
	m_Loc_s.m_Y +=  m_V_s.m_Y * (float32)a_dT_mSec / 1000.0f;

	float32 SpeedFactor = 1.0f + ((float32)m_Acceleration) * (float32)a_dT_mSec / 1000.0f / 1000.0f;

	m_V_s.m_X *= SpeedFactor;
	m_V_s.m_Y *= SpeedFactor;
}


void Ball::Bounce(int8 a_Direction, float32 a_Depth = 0)
{
	if (a_Direction == HORIZONTAL)
	{
		m_Loc_s.m_Y -= fSIGN( m_V_s.m_Y ) * 2.0f * a_Depth; 		
		m_V_s.m_Y = -m_V_s.m_Y;

	}

	if (a_Direction == VERTICAL)
	{
		float32 BBB = fSIGN( m_V_s.m_X );
		float32 AAA = BBB * a_Depth;

		m_Loc_s.m_X -= fSIGN( m_V_s.m_X ) * a_Depth; 		
		m_V_s.m_X = -m_V_s.m_X;
	}
}


