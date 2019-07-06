
#ifndef __LED_MATRIX_H
#define __LED_MATRIX_H

#define N_X	32
#define N_Y	32


void LM_Setup();
void LM_Clear();

void LM_PC_DSP_Display_Matrix();

void LM_SetPoint(int8 a_x, int8 a_y, int8 a_Val);
int8 LM_GetPoint(int8 a_x, int8 a_y);

#endif //#ifndef __LED_MATRIX_H








