#include "stdafx.h"

#include "Display.h"
#include "Led_Matrix.h"
#include "Price.h"


Price::Price(void)
{
	m_Loc_s.m_w = PRICE_DEFAULT_WIDTH;
	m_Loc_s.m_h = PRICE_DEFAULT_HEIGHT;
	m_V_s.m_X = 0;
	m_V_s.m_Y = PRICE_DEFAULT_SPEED;
	m_Loc_s.m_X = -1;
	m_Loc_s.m_Y = -1;
	m_Acceleration = 0;
}


Price::~Price(void)
{
}


void Price::MarkBrickOnMatrix()
{
	for(char y=0; y<DIG_HEIGHT; y++)
	{
		for(char x=0; x<DIG_WIDTH; x++)
		{
				char Line =*(char*)&Digit_arr[m_eType][y];
				LM_SetPoint( m_Loc_s.m_X + x,  m_Loc_s.m_Y + y ,(Line>>x) & 1);
		}
	}

}