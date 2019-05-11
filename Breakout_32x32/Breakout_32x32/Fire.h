#ifndef __FIRE_H
#define __FIRE_H

#include "Brick.h"
#include "Ball.h"

#define FIRE_DEFAULT_WIDTH		1
#define	FIRE_DEFAULT_HEIGHT		1
#define	FIRE_DEFAULT_SPEED		-10		// 3 Pixel / Sec


class Fire : public Ball
{
public:

	Fire(void);
	~Fire(void);
	virtual void Init();
	

};




#endif	//	#ifndef __FIRE_H


