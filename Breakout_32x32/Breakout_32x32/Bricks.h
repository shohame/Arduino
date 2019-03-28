#ifndef __BREAKS_H
#define __BREAKS_H


#define MAX_NUM_OF_BREAKS	((8)*4)
#define MAX_NUM_OF_BALLS		(20)
#define MAX_NUM_OF_WALLS		(15)
#define MAX_NUM_OF_PRICE		(5)


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

	char	m_PriceCount;
	Price	m_Price_arr[MAX_NUM_OF_PRICE];
	
	Stick	m_Stick;

	void AddBrick(char a_x, char a_y);
	void AddBall(char a_x, char a_y, float a_Vx, float a_Vy );
	void AddWall(char a_x, char a_y, char a_w, char a_h);
	void AddPrice(char a_x, char a_y);

	void RemoveBrick(char a_BrickIdx);
	void RemoveBall(char a_BallIndex);
	void RemoveWall(char a_WallIndex);
	void RemovePrice(char a_PriceIndex);
	void MoveAllBalls(int a_dT_mSec);
	void MoveAllPrices(int a_dT_mSec);
	
	void MarkBricksOnMatrix();
	
	void ClearAllBricksBallsWalls();
	void AddLineOfBricks(char a_x0, char a_y0, char a_Count);
	void InitLevel(char a_Level);


private:
	void InitLeve_Clear();
};
#endif // #ifndef __BREAKS_H
