
#ifndef __LED_MATRIX_H
#define __LED_MATRIX_H



#define N_X	32
#define N_Y	32

#define N_LED	(N_X * N_Y)

extern char Matrix[N_Y][N_X];


void LM_Init();
void LM_Clear();

void LM_PC_Display();
void LM_CopyImage2LedStatus(unsigned char * a_pI);
void LM_SetPoint(char a_x, char a_y, char a_Val);


#endif //#ifndef __LED_MATRIX_H








