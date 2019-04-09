// Breakout_32x32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "Ball.h"
#include "Stick.h"
#include "Ball.h"
#include "Price.h"
#include "Display.h"
#include "Bricks.h"
#include "UI_Input.h"
#include "Globe.h"


Bricks g_Bricks;
UI_Input g_UI_In;
int Level = 1;

void RestartGame()
{
	Level = 0;
	g_Bricks.m_Disply.ResetGame();
	g_Bricks.ClearAllBricksBallsWalls();
	LM_Clear();
	TIC_mS();
}



void setup()
{
	GET_RAMDOM_SEED();

	SERIAL_BEGIN(9600);
	DELAY(1000);
	LM_Setup();
//	Draw_Globe();
	LM_Setup();
	RestartGame();

}
int DDD=0;


void loop()
{
	unsigned long Toc = TOC_mS();

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

	LM_Clear();
	g_Bricks.MarkBricksOnMatrix();
	g_Bricks.m_Disply.MarkOnMatrix(Toc);
	LM_PC_DSP_Display_Matrix();


	
	stKeyStatus P1_s, P2_s;

	g_UI_In.GetKeyStatus(&P1_s, &P2_s);

	if ( P1_s.m_R)
		g_Bricks.m_Stick.m_Loc_s.m_X += 0.9;
	if (  P1_s.m_L)
		g_Bricks.m_Stick.m_Loc_s.m_X -= 0.9;

}
#ifdef WIN32	
int _tmain(int argc, _TCHAR* argv[])
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


