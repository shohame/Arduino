#ifndef __BALL_H
#define __BALL_H

#include "General.h"
#include "Brick.h"

#define	BALL_DEFAULT_WIDTH	2
#define	BALL_DEFAULT_HEIGHT	2
#define	BALL_DEFAULT_ACCSELERATION	30  // mili Percent / Sec

#define MAX_ANGLE (75)


class Ball : public Brick
{
public:
	Ball(void);
	~Ball(void);
	virtual void Init();

	stVector   m_V_s;		// velocity
	int8 m_Acceleration;	// +10 percent for each 100 sec 



	void Bounce(int8 a_Direction, float32 a_Depth );
	void MoveBall(int16 a_dT_mSec);
	void SetSpeed(stVector* a_pV);
	void SetSpeed(float32 a_Vx, float32 a_Vy);

	int8 FindBallCollision(Brick a_Brick_arr[], int8 a_BrickCount);
	int8 Where_I_TouchStick (Brick * a_pBrick);
	void ChangeAngleBy(float32 a_dAngle);



};

#endif // #ifndef __BALL_H