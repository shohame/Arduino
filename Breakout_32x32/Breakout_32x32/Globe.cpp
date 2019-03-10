#include "stdafx.h"

#include "General.h"
#include "Led_Matrix.h"
#include "Globe.h"



//unsigned char g_LedStatus[50][16 * 8] PROGMEM = 
//												#include "Globe_Data.h"


void Draw_Globe()
{
	int i;
	LM_PC_DSP_Display_Matrix();


	DELAY(1000);
	while(1)
	for (i=0; i<50; i++)
	{
//		LM_CopyImage2Matrix(g_LedStatus[i]);
		LM_PC_DSP_Display_Matrix();
		DELAY(200);
	}
}





