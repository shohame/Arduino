#ifndef __BREAKS_H
#define __BREAKS_H


#define MAX_NUM_OF_BREAKS	((8+7)*3)
#define MAX_NUM_OF_BALLS		(50)
#define MAX_NUM_OF_WALLS		(10)


class Breaks
{
public:
	Breaks(void);
	~Breaks(void);

	Display	m_Score;

	char	m_BreakCount;
	Break	m_Break_arr[MAX_NUM_OF_BREAKS];

	char	m_BallCount;
	Ball	m_Ball_arr[MAX_NUM_OF_BALLS];

	char	m_WallCount;
	Break	m_Wall_arr[MAX_NUM_OF_WALLS];
	
	Stick	m_Stick;

	void AddBreak(char a_x, char a_y);
	void AddBall(char a_x, char a_y, float a_Vx, float a_Vy );
	void AddWall(char a_x, char a_y, char a_w, char a_h);

	void RemoveBreak(char a_BreakIdx);
	void RemoveBall(char a_BallIndex);
	void RemoveWall(char a_WallIndex);
	void MoveAllBalls(int a_dT_mSec);
	void MarkBreaksOnMatrix();

	void ClearAllBreaksBallsWalls();

	void InitLevel_1();
	void InitLevel_dummy();
};
#endif // #ifndef __BREAKS_H