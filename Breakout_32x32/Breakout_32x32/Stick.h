#ifndef __STICK_H
#define __STICK_H

#include "General.h"
#include "Break.h"

#define	STICK_DEFAULT_WIDTH		7
#define	STICK_DEFAULT_HEIGHT	1
#define	STICK_DEFAULT_X			13
#define	STICK_DEFAULT_Y			31




class Stick :public Break
{
public:
	Stick(void);
	~Stick(void);

};


#endif	//	#ifndef __STICK_H

