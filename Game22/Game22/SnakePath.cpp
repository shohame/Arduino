#include "stdafx.h"
#include "General.h"

#include "SnakePath.h"



void SnakePath::Reset(void)
{ 
	m_Ps = { -1,-1 };
	m_Pe = { -1,-1 };
	m_Index = -2;
}

eDirection  SnakePath::GetDirection(stPoint a_P)
{
	if (a_P.m_X > m_Pe.m_X) return eDirR;
	if (a_P.m_X < m_Pe.m_X) return eDirL;
	if (a_P.m_Y > m_Pe.m_Y) return eDirD;
	if (a_P.m_Y < m_Pe.m_Y) return eDirU;
	return -1;
}

void SnakePath::AddPoint(stPoint a_P)
{
	eDirection NewDirection;
	if (m_Index == -2)
	{
		m_Ps = a_P;
		m_Pe = a_P;
		m_Index++;
	}

	NewDirection = GetDirection(a_P);
	
	if ( ((uint8)NewDirection != m_Path[m_Index].m_Dir) || (m_Index == -1) )
	{
		m_Index++;
		m_Path[m_Index].m_Dir = NewDirection;
		m_Path[m_Index].m_Len = 1;
	}
	else
	{
		m_Path[m_Index].m_Len++;
	}

}


void SnakePath::IterReset(void)
{
	m_IterIndex = 0; 
	m_IterPath.m_Dir = 0; 
	m_IterPath.m_Len = 0;
}

int8 SnakePath::IterGetNext(stPoint *a_pP)
{
	return 1;
}
