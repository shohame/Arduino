// Breakout_32x32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "General.h"
#include "Led_Matrix.h"
#include "Ball.h"
#include "Stick.h"
#include "Ball.h"
#include "Display.h"
#include "Breaks.h"
#include "UI_Input.h"



Breaks g_Breaks;
UI_Input g_UI_In;

void setup()
{
	SERIAL_BEGIN(9600);
	DELAY(1000);
	LM_Setup();
	g_Breaks.InitLevel_1();
	g_Breaks.m_Score.ResetGame();
	LM_Clear();
	g_Breaks.MarkBreaksOnMatrix();
	g_Breaks.m_Score.MarkOnMatrix(0);
	LM_PC_DSP_Display_Matrix();
 TICmS();
}
int DDD=0;
void loop()
{
  unsigned long Toc = TOCmS();
  TICmS();
 //Serial.println(TOCmS());
  
  
	g_Breaks.MoveAllBalls(Toc);

  LM_Clear();
	g_Breaks.MarkBreaksOnMatrix();
	g_Breaks.m_Score.MarkOnMatrix(Toc);
	LM_PC_DSP_Display_Matrix();

	if (g_Breaks.m_BallCount==0)
	{
      g_Breaks.AddBall(16,28, 3, -6.0);

      g_Breaks.AddBall(16,28, 4, -5.0);

      g_Breaks.AddBall(16,28, -3, -6.0);


	}
	
	stKeyStatus P1_s, P2_s;

	g_UI_In.GetKeyStatus(&P1_s, &P2_s);

	if ( P1_s.m_R)
		g_Breaks.m_Stick.m_Loc_s.m_X += 1;
	if (  P1_s.m_L)
		g_Breaks.m_Stick.m_Loc_s.m_X -= 1;

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


