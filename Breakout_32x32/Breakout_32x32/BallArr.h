#ifndef __BALLARR_H
#define __BALLARR_H

#include "General.h"
#include "Brick.h"
#include "Ball.h"
#include "BrickArrTemp.h"


class BallArr : public BrickArrTemp<Ball, 10>
{
public:
	BallArr(void)
	{

	}
	//~BallArr(void){};



};

#endif // #ifndef __BALL_H