#ifndef __BALL_H
#define __BALL_H

#include "General.h"
#include "Brick.h"

#define	BALL_DEFAULT_WIDTH	2
#define	BALL_DEFAULT_HEIGHT	2

#define MAX_ANGLE (75)


class Ball :public Brick
{
public:
	Ball(void);
	~Ball(void);
	stVector   m_V_s;		// velocity
	void Bounce(char a_Direction, float a_Depth );
	void MoveBall(int a_dT_mSec);
	void SetSpeed(stVector* a_pV);
	void SetSpeed(float a_Vx, float a_Vy);

	char FindBallCollision(Brick a_Brick_arr[], char a_BrickCount);
	char Where_I_TouchStick (Brick * a_pBrick);
	void ChangeAngleBy(float a_dAngle);



};

#endif // #ifndef __BALL_H