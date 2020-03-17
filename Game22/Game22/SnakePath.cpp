#include "stdafx.h"
#include "General.h"

#include "SnakePath.h"



void SnakePath::Reset(void)
{ 
	m_Ps = { -1,-1 };
	m_Pe = { -1,-1 };
	m_Pc = { -1,-1 };
	m_Index=-1;
}


void SnakePath::AddPoint(stPoint a_P)
{
	if (m_Index < 0)
	{
		m_Ps = a_P;
		
	}
	m_Pe = a_P;

	if (m_Index<0) //|| a_Direction != m_Path[m_Index].m_Dir)
	{
		m_Index++;
		m_Path[m_Index].m_Dir = 1;// a_Direction;
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
