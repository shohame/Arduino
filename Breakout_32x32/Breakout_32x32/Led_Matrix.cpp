
#include "stdafx.h"
#include "General.h"
#include "LED_Matrix.h"


#ifdef WIN32
	typedef unsigned  char    byte;
  #define pgm_read_word_near(A) *A

#else
	#include "LedControl_HW.h"
	#include "SPI.h"
	LedControl_HW lc=LedControl_HW(10,16);
#endif


char Matrix[N_Y][N_X/8];


void LM_Setup()
{
#ifdef WIN32
#else
	for(int M = 0; M < N_Y*N_X; M++)
	{
		lc.shutdown(M,false);
		lc.setIntensity(M,4);
		lc.clearDisplay(M);
	}
#endif

}


void LM_SetPoint(char a_x, char a_y, char a_Val)
{
	char Xi, Xb;

	Xi = a_x/8;
	Xb = a_x%8;

	if (a_Val==0)
	{
		Matrix[a_y][Xi] &= ((1<<Xb)^0xff);
	}
	else
	{
		Matrix[a_y][Xi] |= (1<<Xb);
	}
}

char LM_GetPoint(char a_x, char a_y)
{
	char Xi, Xb;
	Xi = a_x/8;
	Xb = a_x%8;

	return((Matrix[a_y][Xi]>>Xb)&1);
}



void LM_Clear()
{
	char x,y;

	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			LM_SetPoint(x, y, 0);
		}
	}
}


void LM_CopyImage2Matrix(unsigned char * a_pI)
{
  for(byte My = 0; My<4; My++)
  {
    for(byte L=0; L<8; L++)
    {
      for(byte Mx = 0; Mx<4; Mx++)
      {
        int Line = pgm_read_word_near(&a_pI[Mx+L*4+My*4*8]);
        for(byte P=0; P<8; P++)
        {  
			if ( (Line & (1<<P))  > 0)   
			{
				LM_SetPoint(Mx*8 + P, My*8 + L, 1 );      
				}
			else
			{
				LM_SetPoint(Mx*8 + P, My*8 + L, 0 );     
			}
        }
      }
    }
  }
}

#ifdef WIN32

void gotoxy(int x, int y)
{
	COORD pos = {x, y};
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hC, pos);
}



#include <iostream>

void LM_PC_DSP_Display_Matrix()
{
	char x,y;
	HANDLE hSTD = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(0,0);

	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			if (LM_GetPoint(x, y))
			{
				SetConsoleTextAttribute(hSTD,(8<<4)+4);
				std::cout << "@";
				//printf("@");
			}
			else
			{
				SetConsoleTextAttribute(hSTD,(8<<4)+7);
				std::cout << "@"; 
				// printf("@");
			}
		}
		printf("\n");
	}
}
#else
void LM_PC_DSP_Display_Matrix()
{
	char x,y;

	
	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			lc.LC_SetPoint_on_LedStatus(x, y, LM_GetPoint(x,y) );
		}
	}
	lc.LC_UpdateLeds();
}
#endif
