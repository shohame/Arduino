#ifndef __BREAKS_H
#define __BREAKS_H


#define MAX_NUM_OF_BREAKS	((8)*4)
#define MAX_NUM_OF_BALLS		(3)
#define MAX_NUM_OF_WALLS		(15)


class Bricks
{
public:
	Bricks(void);
	~Bricks(void);

	Display	m_Disply;

	char	m_BrickCount;
	Brick	m_Brick_arr[MAX_NUM_OF_BREAKS];

	char	m_BallCount;
	Ball	m_Ball_arr[MAX_NUM_OF_BALLS];

	char	m_WallCount;
	Brick	m_Wall_arr[MAX_NUM_OF_WALLS];
	
	Stick	m_Stick;

	void AddBrick(char a_x, char a_y);
	void AddBall(char a_x, char a_y, float a_Vx, float a_Vy );
	void AddWall(char a_x, char a_y, char a_w, char a_h);

	void RemoveBrick(char a_BrickIdx);
	void RemoveBall(char a_BallIndex);
	void RemoveWall(char a_WallIndex);
	void MoveAllBalls(int a_dT_mSec);
	void MarkBricksOnMatrix();
	
	void ClearAllBricksBallsWalls();

	void InitLevel(char a_Level);


private:
	void InitLeve_Clear();
};
#endif // #ifndef __BREAKS_H
