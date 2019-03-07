

int pin_L1 = 2;
int pin_R1 = 3;
int pin_L2 = 5;
int pin_R2 = 4;

int Nx = 32;
int Ny = 32;


struct typedef sPoint
{
	int m_X;
	int m_Y;
}stPoint;


stPoint P1 = {10, 23};
stPoint P2 = {21, 23};

int Di1 = 0;  // direction of 1	
int Di2 = 0;  // direction of 1	

#define MAX_P_IN_ARR 1000

stPoint P1_arr[MAX_P_IN_ARR];
stPoint P2_arr[MAX_P_IN_ARR];
int P12idx = 0;

int GameOver = 0;
int T_Delay = 200;


stPoint Dir_arr[4] = {{0,-1}, {1,0}, {0,1}, {-1,0}}; // Up, Right, Down, Left


void Reset_Game()
{
	P1 = {10, 22};
	P2 = {21, 22};

	Di1 = 0;  // direction of 1	
	Di2 = 0;  // direction of 2	
	
	P12idx = 0;
	GameOver = 0;
	T_Delay = 200;
	
	Led_Clear_All();
	
}


void setup()
{
	Serial.begin(9600);
	pinMode(pin_L1, INPUT_PULLUP );
	pinMode(pin_R1, INPUT_PULLUP );
	pinMode(pin_L2, INPUT_PULLUP );
	pinMode(pin_R2, INPUT_PULLUP );
}

void delay_and_change_direction_goto_next_step(int D)
{
	int dDi1 = 0;
	int dDi2 = 0;
	TIC();
	while(TOC()<D)
	{
		if (!digitalRead(pin_L1))
		{
			dDi1 = 1;
		}
		else if (!digitalRead(pin_R1))
		{
			dDi1 = -1;
		}
		if (!digitalRead(pin_L2))
		{
			dDi2 = 1;
		}
		else if (!digitalRead(pin_R2))
		{
			dDi2 = -1;
		}
		
	}
	
	Di1 = (Di1 + 4 + dDi1)%4; // updateing direction of 1
	Di2 = (Di2 + 4 + dDi2)%4; // updateing direction of 2

	P1+=Dir_arr[Di1];
	P2+=Dir_arr[Di2];

}
int Test_if_Free_and_Set(stPoint& pP)
{
	if (Get_Led_Status(pP->m_X, pP->m_Y))
	{
		return 0;
	}
	else
	{
		Set_Led_Status(pP->m_X, pP->m_Y);
		return 1;
	}
	
}

void DoGameOver(int isFree_1, int isFree_2)
{
	for(int i=0; i<P12idx; i++)
	{
		if (isFree_1==0)
		{
			Set_Led_Status(P1_arr[i].m_X, P1_arr[i].m_Y, 0);
		}
		if (isFree_2==0)
		{
			Set_Led_Status(P2_arr[i].m_X, P2_arr[i].m_Y, 0);
		}
		Led_Update()
		delay(50);
	}
}


void loop()
{
	int isFree_1;
	int isFree_2;
	
	Reset_Game();
	
	while (GameOver == 0)
	{
		P1_arr[P12idx] = P1;
		P2_arr[P12idx] = P2;
		if ( (MAX_P_IN_ARR-1) > P12idx) 
			P12idx++;
		
		Led_Update();
		delay_and_change_dir_goto_next_step(T_Delay);
		isFree_1 = Test_if_Free_and_Set(&P1);
		isFree_2 = Test_if_Free_and_Set(&P2);
		
		if (isFree_1 == 0 || isFree_2 == 0)
		{
			GameOver = 1;
			
		}
		else
		{
			Led_Update();
		}
	}
	
	DoGameOver(isFree_1, isFree_2);
}

