#include "StdAfx.h"
#include "Stick.h"
#include "LED_Matrix.h"


Stick::Stick(void)
{
	m_Loc_s.m_w = STICK_DEFAULT_WIDTH;
	m_Loc_s.m_h = STICK_DEFAULT_HEIGHT;
	m_Loc_s.m_X = STICK_DEFAULT_X + 0;
	m_Loc_s.m_Y = STICK_DEFAULT_Y;
}

Stick::~Stick(void)
{
}


void Stick::ChangeStickType(eStickType a_StickType)
{
	m_Type = a_StickType;
	char w = m_Loc_s.m_w;

	switch (m_Type)
	{
		case(eStickRegular):
		{
			m_Loc_s.m_w = STICK_DEFAULT_WIDTH;
			break;
		}
		case(eStickLarge):
		{
			m_Loc_s.m_w = STICK_DEFAULT_WIDTH + 2;
			break;
		}
		case(eStickSmall):
		{
			m_Loc_s.m_w = STICK_DEFAULT_WIDTH - 2;
			break;
		}
		default:
			{}
	}

	m_Loc_s.m_X -= (m_Loc_s.m_w - w)/2;


}


void Stick::MarkBrickOnMatrix(void)
{
	if (m_Type==eStickFire)
	{
		char x = (char)floor(0.5 + m_Loc_s.m_X + (m_Loc_s.m_w - 1)/2);
		char y = m_Loc_s.m_Y - 1;
		LM_SetPoint(x, y, 1);
	}
	Brick::MarkBrickOnMatrix();
}




