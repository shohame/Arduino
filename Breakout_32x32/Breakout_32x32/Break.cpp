#include "StdAfx.h"
#include <math.h>
#include "General.h"
#include "Break.h"
#include "Led_Matrix.h"


Break::Break()
{
	m_Loc_s.m_X = -1;
	m_Loc_s.m_Y = -1;
	m_Loc_s.m_w = BREAK_DEFAULT_WIDTH;
	m_Loc_s.m_h = BREAK_DEFAULT_HEIGHT;
}
Break::Break(char a_x, char a_y, char a_w, char a_h)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_Loc_s.m_w = a_w;
	m_Loc_s.m_h = a_h;	
}


Break::~Break(void)
{
}


 void Break::MarkBreakOnMatrix()
 {
	for(char y=0; y<(char)m_Loc_s.m_h; y++)
	{
		for(char x=0; x<(char)m_Loc_s.m_w; x++)
		{
			char yi = y + (char)floor(0.5 + m_Loc_s.m_Y);
			char xi = x + (char)floor(0.5 + m_Loc_s.m_X);
			if ( yi>=0 && yi<N_Y && xi>=0 && xi<N_X)
			{
				Matrix[ yi ][ xi ] = 1;
			}
		}
	}
 }


void Break::SetPos(char a_x, char a_y)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
}

void Break::SetLoc(char a_x, char a_y, char a_w, char a_h)
{
	m_Loc_s.m_X = a_x;
	m_Loc_s.m_Y = a_y;
	m_Loc_s.m_w = a_w;
	m_Loc_s.m_h = a_h;
}


char Break::WhereBreakTouchMe (Break * a_pBreak, float* a_pD)
{
	char TouchDir = 0;
	*a_pD = 0.0;

	stLoc	Y_Loc = a_pBreak->m_Loc_s;
	stLoc	M_Loc = m_Loc_s;

	float Y_half_w =  Y_Loc.m_w / 2.0;
	float M_half_w =  M_Loc.m_w / 2.0;
	float Y_half_h =  Y_Loc.m_h / 2.0;
	float M_half_h =  M_Loc.m_h / 2.0;

	float Y_Cx = Y_Loc.m_X + Y_half_w;
	float M_Cx = M_Loc.m_X + M_half_w;
	float Y_Cy = Y_Loc.m_Y + Y_half_h;
	float M_Cy = M_Loc.m_Y + M_half_h;

	float dX  = ( Y_half_w + M_half_w) - abs( Y_Cx - M_Cx); // if dX > 0  ==> Thay can be tuched!
	float dY  = ( Y_half_h + M_half_h) - abs( Y_Cy - M_Cy); // if dy > 0  ==> Thay can be tuched!
	
	if ( dX > 0 && dY > 0) // 
	{
		*a_pD = (dX<dY) ? dX : dY;
		TouchDir = ( (dX > dY) ? HORIZONTAL : VERTICAL ); // 1 => Tuching the horizontal eage, 2 => Vertical
	}
	return TouchDir;
}