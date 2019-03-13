#ifndef __BREAK_H
#define __BREAK_H


#define HORIZONTAL 	1
#define VERTICAL	2

typedef struct stLoc_name
{
	float	m_X;
	float	m_Y;
	char	m_w;
	char	m_h;
}stLoc;


#define	BREAK_DEFAULT_WIDTH		3
#define	BREAK_DEFAULT_HEIGHT	2


class Brick
{

public:

	stLoc m_Loc_s;	

	Brick(void);
	Brick(char a_x, char a_y, char a_w, char a_h);
	~Brick(void);

	void SetPos(char a_x, char a_y);
	char WhereBrickTouchMe (Brick * a_pBrick, float* a_pD);
	void SetLoc(char a_x, char a_y, char a_w, char a_h);

	void MarkBrickOnMatrix();

};



#endif	//	#ifndef __BREAK_H

