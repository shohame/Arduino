
#ifndef __GENERAL_H
#define __GENERAL_H

#define DO_DEBUG true

#ifdef DO_DEBUG 
	#include <assert.h>
#endif
#include <math.h>
#include <time.h>
extern unsigned long g_Tic;

#ifdef WIN32
	#include <Windows.h>
	#include <WinUser.h>
	#include <ctime>
	#define SERIAL_BEGIN(F)
	#define SERIAL_PRINT(F) 
	#define SERIAL_PRINTLN(F) 
	#define TIC_mS()   g_Tic = clock()
	#define TOC_mS()   (clock()-g_Tic)
	#define DELAY(a) Sleep(a)
	#define PROGMEM
	#define pgm_read_word_near(A) (*A)
	#define RAND_INT(F,T) (( rand() % (T-F) ) + F)
	#define GET_RAMDOM_SEED()	srand(time(NULL))

#else
  #include <Arduino.h>
  #include <avr/pgmspace.h>
	#define SERIAL_BEGIN(F) Serial.begin(F)
	#define SERIAL_PRINT(F) Serial.print(F)
	#define SERIAL_PRINTLN(F) Serial.println(F)
	#define DELAY(a) delay(a)
	#define TIC_mS()   g_Tic=millis()
	#define TOC_mS()   (millis()-g_Tic)
	#define RAND_INT(min,max) random(min, max)
	#define GET_RAMDOM_SEED()		randomSeed(analogRead(0))

#endif


#ifdef WIN32
#else
#endif





#define PI (3.14159265358979)


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

