
#include "stdafx.h"
#include "General.h"
#include "LED_Matrix.h"
typedef unsigned  char    byte;

char Matrix[N_Y][N_X];

#define LC_SetPoint_on_LedStatus(A,B,C)	 Matrix[B][A] = C
#define pgm_read_word_near(A) *A




void LM_SetPoint(char a_x, char a_y, char a_Val)
{
	LC_SetPoint_on_LedStatus(a_x, a_y, a_Val);
	//lc.LC_SetPoint_on_LedStatus(a_x, a_y, a_Val); 
}

void LM_Clear()
{
	char x,y;

	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			Matrix[y][x] = 0;
		}
	}
}


void LM_Init()
{
	char x,y;

	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			Matrix[y][x] = (x+y) & 1;
		}
	}
}

void LM_CopyImage2LedStatus(unsigned char * a_pI)
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


#include <Windows.h>

void gotoxy(int x, int y)
{
	COORD pos = {x, y};
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hC, pos);
}



void LM_PC_Display()
{
	char x,y;

	gotoxy(0,0);

	for(y=0; y<N_Y; y++)
	{
		for(x=0; x<N_X; x++)
		{
			if (Matrix[y][x])
			{
				printf("#");
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}
}

