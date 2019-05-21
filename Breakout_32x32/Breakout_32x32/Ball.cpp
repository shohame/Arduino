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
	m_MB_Type = eMB_Ball;
}

void Ball::Init(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy)
{
	Init();
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_V_s.m_X = a_Vx;
	m_V_s.m_Y = a_Vy;
}


Ball::~Ball(void)
{
	
}



int8 Ball::Where_I_TouchStick (Brick * a_pStick)
{
	stBrickTouchProp TouchProp_s;

	FindCollision(a_pStick, 1, &TouchProp_s);

	if ( TouchProp_s.m_isTouch) // 
	{
		Bounce(HORIZONTAL, TouchProp_s.m_Depth);
		ChangeAngleBy(TouchProp_s.m_dAngle);
		return 1;
	}
	return 0;
}

int8 Ball::FindBallCollision(Brick a_Brick_arr[], int8 a_BrickCount)
{

	int8 BrickIdx;
	stBrickTouchProp TouchProp_s;

	BrickIdx = FindCollision(a_Brick_arr, a_BrickCount, &TouchProp_s);

	if (BrickIdx > -1)
	{
		Bounce(TouchProp_s.m_Direction, TouchProp_s.m_Depth);
	}

	return BrickIdx;
}





