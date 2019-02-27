#ifndef __BALL_H
#define __BALL_H

#include "General.h"
#include "Break.h"

#define	BALL_DEFAULT_WIDTH	2
#define	BALL_DEFAULT_HEIGHT	2

#define MAX_ANGLE (75)


class Ball :public Break
{
public:
	Ball(void);
	~Ball(void);
	stVector   m_V_s;		// velocity
	void Bounce(char a_Direction, float a_Depth );
	void MoveBall(int a_dT_mSec);
	void SetSpeed(stVector* a_pV);
	void SetSpeed(float a_Vx, float a_Vy);

	char FindBallCollision(Break a_Break_arr[], char a_BreakCount);
	char Where_I_TouchStick (Break * a_pBreak);
	void ChangeAngleBy(float a_dAngle);



};

#endif // #ifndef __BALL_H