#ifndef __BREAK_H
#define __BREAK_H


#define HORIZONTAL 	1
#define VERTICAL	2

typedef struct stLoc_name
{
	float	m_X;
	float	m_Y;
	float	m_w;
	float	m_h;
}stLoc;


#define	BREAK_DEFAULT_WIDTH		3
#define	BREAK_DEFAULT_HEIGHT	2




class Break
{

public:

	stLoc m_Loc_s;	

	Break(void);
	Break(char a_x, char a_y, char a_w, char a_h);
	~Break(void);

	void SetPos(char a_x, char a_y);
	char WhereBreakTouchMe (Break * a_pBreak, float* a_pD);
	void SetLoc(char a_x, char a_y, char a_w, char a_h);

	void MarkBreakOnMatrix();

};



#endif	//	#ifndef __BREAK_H

