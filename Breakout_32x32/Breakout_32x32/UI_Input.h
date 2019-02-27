#ifndef __UI_INPUT_H
#define __UI_INPUT_H


#define PIN_KEY_L	2
#define PIN_KEY_R	3
#define PIN_KEY_U	4
#define PIN_KEY_D	5


#define PIN_PLAYER_1	16
#define PIN_PLAYER_2	17


typedef struct stKeyStatus_name
{
	char m_L;	
	char m_R;
	char m_U;
	char m_D;
}stKeyStatus;

class UI_Input
{
public:
	UI_Input(void);
	~UI_Input(void);

	void GetKeyStatus(stKeyStatus* a_pKS_Player1, stKeyStatus* a_pKS_Player2);
};




#endif	//	#ifndef __UI_INPUT_H
