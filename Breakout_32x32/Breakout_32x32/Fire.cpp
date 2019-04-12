#include "stdafx.h"
#include "General.h"
#include "Display.h"
#include "Led_Matrix.h"
#include "Fire.h"


Fire::Fire(void)
{
	m_Loc_s.m_w = FIRE_DEFAULT_WIDTH;
	m_Loc_s.m_h = FIRE_DEFAULT_HEIGHT;
	m_V_s.m_X = 0;
	m_V_s.m_Y = 0;
	m_Loc_s.m_X = -1;
	m_Loc_s.m_Y = -1;
	m_Acceleration = 0;
}


Fire::~Fire(void)
{
}


