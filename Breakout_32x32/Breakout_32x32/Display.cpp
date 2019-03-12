#include "StdAfx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "Display.h"
#include <math.h>

const   Line_Bit  Digit_arr[NUM_OF_DIG][DIG_HEIGHT]= 
	{	
		#include "Number_Bitmap.h"
	};

					
Display::Display(void)
{
}


Display::~Display(void)
{
}


void Display::ResetGame(void)
{
	m_Score = 0;
	m_LastDispScore = 0;
	m_Life = 3;
}

void Display::AddScore(int a_Value)
{
	m_Score = m_Score + a_Value;
	m_Sum_dT = 0;
}


void Display::MarkOnMatrix(int a_dT)
{
	long tScore;
	char x0, y0, Di;
	m_Sum_dT = m_Sum_dT + a_dT; 
	if(m_Sum_dT>2000)
	{
		tScore = m_Score;
		m_Sum_dT = 0;
	}
	else
	{
		int dS = exp(-(float)m_Sum_dT/50.0) * (m_Score - m_LastDispScore);
		dS = (m_Score > m_LastDispScore) ? MAX(1, dS) : 0;
		tScore = m_LastDispScore + dS;
	}

	m_LastDispScore = tScore;

	char W = 4; // Width
	char i, N_Digit = 1;
	if (tScore > 9)		N_Digit = 2;
	if (tScore > 99)		N_Digit = 3;
	if (tScore > 999)		N_Digit = 4;
	if (tScore > 9999)		N_Digit = 5;
	if (tScore > 99999)		N_Digit = 6;
	if (tScore > 999999)	tScore = 999999;
		
	y0 = 0;

	for (i =0; i<N_Digit; i++)
	{
		Di = tScore%10;
		tScore = tScore / 10;

		x0 = (6 - N_Digit) * W/2 + (N_Digit-1-i)*W;

		for(char y=0; y<DIG_HEIGHT; y++)
		{
			for(char x=0; x<DIG_WIDTH; x++)
			{
				char Line = *(char*)&Digit_arr[Di][y];
				LM_SetPoint( x0 + x, y0 + y ,(Line>>x) & 1);
			}
		}
	}
	y0 = 0;
	x0 = 27;
  Di = m_Life;
	for(char y=0; y<DIG_HEIGHT; y++)
	{
		for(char x=0; x<DIG_WIDTH; x++)
		{
				char Line =*(char*)&Digit_arr[Di][y];
				LM_SetPoint( x0 + x, y0 + y ,(Line>>x) & 1);
		}
	}

	
}
