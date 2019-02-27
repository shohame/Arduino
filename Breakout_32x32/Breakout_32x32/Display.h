#ifndef __SCORE_H
#define __SCORE_H



#define NUM_OF_DIG	10
#define DIG_WIDTH	3
#define DIG_HEIGHT	5



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




