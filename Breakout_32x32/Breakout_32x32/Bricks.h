#ifndef __BREAKS_H
#define __BREAKS_H


#define MAX_NUM_OF_BREAKS	((8)*4)
#define MAX_NUM_OF_BALLS		(10)
#define MAX_NUM_OF_WALLS		(10)
#define MAX_NUM_OF_PRICE		(5)
#define MAX_NUM_OF_FIRE			(5)

#define GIVE_PRICE_RATE		5  // for each 5 bricks give 1 price

class Bricks
{
public:
	Bricks(void);
	~Bricks(void);

	Display	m_Disply;

	int8	m_BrickCount;
	Brick	m_Brick_arr[MAX_NUM_OF_BREAKS];

	int8	m_BallCount;
	Ball	m_Ball_arr[MAX_NUM_OF_BALLS];

	int8	m_WallCount;
	Brick	m_Wall_arr[MAX_NUM_OF_WALLS];

	int8	m_PriceCount;
	Price	m_Price_arr[MAX_NUM_OF_PRICE];

	int8	m_FireCount;
	Fire	m_Fire_arr[MAX_NUM_OF_FIRE];

	Stick	m_Stick;

	void AddBrick(int8 a_x, int8 a_y);
	void AddBall(int8 a_x, int8 a_y, float32 a_Vx, float32 a_Vy );
	void AddWall(int8 a_x, int8 a_y, int8 a_w, int8 a_h);
	void AddPrice(int8 a_x, int8 a_y);
	void AddFire(int8 a_x, int8 a_y);

	void RemoveBrick(int8 a_BrickIdx);
	void RemoveBall (int8 a_BallIndex);
	void RemoveWall (int8 a_WallIndex);
	void RemovePrice(int8 a_PriceIndex);
	void RemoveFire (int8 a_FireIndex);
	
	void MoveAllBalls(int16 a_dT_mSec);
	void MoveAllPrices(int16 a_dT_mSec);
	void MoveAllFires(int16 a_dT_mSec);
	void GetThePrice(ePriceType a_eType, int8 a_x, int8 a_y);

	void MarkBricksOnMatrix();
	
	void ClearAllBricksBallsWalls();
	void AddLineOfBricks(int8 a_x0, int8 a_y0, int8 a_Count);
	void InitLevel(int8 a_Level);


private:
	void InitLeve_Clear();
};
#endif // #ifndef __BREAKS_H
