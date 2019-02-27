
#ifndef __GENERAL_H
#define __GENERAL_H

#define DO_DEBUG true

#ifdef DO_DEBUG 
	#include <assert.h>
#endif


#include <Windows.h>
#include <math.h>
#include <WinUser.h>


#define PROGMEM
#define PI (3.14159265358979)

#define DELAY(a) Sleep(a)

#define fSIGN(a) ( (a>=0.0) ? 1.0 : -1.0 ) 
#define ABS(a) ( (a>0) ? (a) : (-a) ) 
#define POW2(a) (a*a)

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))


#define RAD2DEG(a) (((float)(a))*180.0/PI)
#define DEG2RAD(a) (((float)(a))*PI/180.0)

typedef struct stVector_name
{
	float m_X;
	float m_Y;
}stVector;





#endif // #ifndef __GENERAL_H

