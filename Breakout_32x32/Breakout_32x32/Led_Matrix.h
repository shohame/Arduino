
#ifndef __LED_MATRIX_H
#define __LED_MATRIX_H



#define N_X	32
#define N_Y	32

#define N_LED	(N_X * N_Y)

extern char Matrix[N_Y][N_X/8];

void LM_Setup();
void LM_Clear();

void LM_PC_DSP_Display_Matrix();
void LM_CopyImage2Matrix(unsigned char * a_pI);
void LM_SetPoint(char a_x, char a_y, char a_Val);
char LM_GetPoint(char a_x, char a_y);

#endif //#ifndef __LED_MATRIX_H








