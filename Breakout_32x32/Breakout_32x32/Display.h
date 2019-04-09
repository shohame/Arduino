#ifndef __SCORE_H
#define __SCORE_H


#define NUM_OF_PRICE 5
#define NUM_OF_DIG	(10 + NUM_OF_PRICE)
#define DIG_WIDTH	3
#define DIG_HEIGHT	5

typedef struct Line_Bit
{
	char b0:1;
	char b1:1;
	char b2:1;
	char b3:1;
	char b4:1;
	char b5:1;
	char b6:1;
	char b7:1;

}Line_Bit;

extern const  Line_Bit  Digit_arr[NUM_OF_DIG][DIG_HEIGHT] ;

class Display
{
public:
	Display(void);
	~Display(void);

	long m_Score;
	long m_LastDispScore;
	int  m_Sum_dT;

	int m_Life;

	void AddScore(int a_Value);
	void ResetGame(void);
	void MarkOnMatrix(int a_dT);

};






#endif // #ifndef __SCORE_H




