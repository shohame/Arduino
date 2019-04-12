#ifndef __BREAK_H
#define __BREAK_H


#define HORIZONTAL 	1
#define VERTICAL	2

typedef struct stLoc_name
{
	float32	m_X;
	float32	m_Y;
	int8	m_w;
	int8	m_h;
}stLoc;


#define	BREAK_DEFAULT_WIDTH		3
#define	BREAK_DEFAULT_HEIGHT	2


class Brick
{

public:

	stLoc m_Loc_s;	

	Brick(void);
	Brick(int8 a_x, int8 a_y, int8 a_w, int8 a_h);
	~Brick(void);

	void SetPos(int8 a_x, int8 a_y);
	int8 WhereBrickTouchMe (Brick * a_pBrick, float32* a_pD);
	void SetLoc(int8 a_x, int8 a_y, int8 a_w, int8 a_h);

	void MarkBrickOnMatrix();

};



#endif	//	#ifndef __BREAK_H

