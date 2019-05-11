#include "stdafx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "Ball.h"
#include "Stick.h"
#include "Ball.h"
#include "BallArr.h"
#include "Fire.h"
#include "Price.h"
#include "Display.h"
#include "Bricks.h"
#include "UI_Input.h"
#include "Globe.h"

#include "BrickArrTemp.h"

Bricks g_Bricks;
UI_Input g_UI_In;
int8 Level = 1;

void RestartGame()
{
	Level = 0;
	g_Bricks.m_Disply.ResetGame();
	g_Bricks.ClearAllBricksBallsWalls();
	LM_Clear();
	TIC_mS();
}

int Arr[] = {1,2,3,4,5,6};


void setup()
{
//	BallArr MyBall_arr;
//	MyBall_arr.Add();
//	int AAA = MyBall_arr.m_Count;
	GET_RAMDOM_SEED();
	SERIAL_BEGIN(9600);
	SERIAL_PRINT(AAA);
	DELAY(1000);
	LM_Setup();
	RestartGame();
}

void loop()
{
	int16 Toc = (int16)TOC_mS();
	Toc = MIN(Toc, MAX_FRAME_TIME);
  if (g_Bricks.m_BrickCount == 0)
	{
		DELAY(500);
		Level ++;
		g_Bricks.InitLevel(Level);
	}
	if (g_Bricks.m_BallCount==0)
	{
		DELAY(500);
		if (g_Bricks.m_Disply.m_Life == 0) // Game Over
		{
			DELAY(1000);		
			RestartGame();
		}
		else
		{
			g_Bricks.m_Disply.m_Life--;
			g_Bricks.AddBall(16,28, 3, -6.0);
			g_Bricks.m_Stick.ChangeStickType(eStickRegular);
		}
 	}

	TIC_mS();
  
	g_Bricks.MoveAllBalls(Toc);
	g_Bricks.MoveAllPrices(Toc);
	g_Bricks.MoveAllFires(Toc);

	LM_Clear();
	g_Bricks.MarkBricksOnMatrix();
	g_Bricks.m_Disply.MarkOnMatrix(Toc);
	LM_PC_DSP_Display_Matrix();
	
	stKeyStatus P1_s, P2_s;

	g_UI_In.GetKeyStatus(&P1_s, &P2_s);

	if ( P1_s.m_R)
		g_Bricks.m_Stick.m_Loc_s.m_X += 0.9f;
	if (  P1_s.m_L)
		g_Bricks.m_Stick.m_Loc_s.m_X -= 0.9f;
	if (P1_s.m_U && g_Bricks.m_Stick.m_Type == eStickFire)
	{
		int8 x = ROUND_CORD_TO_U8(g_Bricks.m_Stick.m_Loc_s.m_X + ((g_Bricks.m_Stick.m_Loc_s.m_w - 1)/2));
		int8 y = ROUND_CORD_TO_U8(g_Bricks.m_Stick.m_Loc_s.m_Y - 1);
		g_Bricks.AddFire(x, y);
	}

	if (P1_s.m_U && P1_s.m_D && P1_s.m_L && P1_s.m_R)
	{
	
		resetFunc();
	}


}
#ifdef WIN32	
int32 _tmain(int32 argc, _TCHAR* argv[])
{
   HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);


	setup();
	while(1)
	{
		loop();
	}


	return 0;
}
#endif


