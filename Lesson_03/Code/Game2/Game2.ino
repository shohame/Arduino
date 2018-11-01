int Player_1_V = 0;
int Player_2_V = 0;
int Led_Color = 0;
int Stop = 0;

int GREEN = 1;
int RED = 2;
int No_One_Touched_A_Target;
int LedPin_Color_1 = 8;
int LedPin_Color_2 = 9;
int LedPin_Player_1 = 6;
int LedPin_Player_2 = 7;

void setup()
{
  randomSeed(analogRead(0)+analogRead(5));
  pinMode(LedPin_Color_1, OUTPUT);
  pinMode(LedPin_Color_2, OUTPUT);
  pinMode(LedPin_Player_1, OUTPUT);
  pinMode(LedPin_Player_2, OUTPUT);
  Serial.begin(9600);     // Begin the serial communication, to be able printing who's winning to the terminal
}

void Someone_Won(int PlayerNumber)
{
  if (PlayerNumber == 1)
  {
      Serial.println("********* Player ---- 1 ---- WON *********");
      digitalWrite(LedPin_Player_1, HIGH); 
  }
  if (PlayerNumber == 2)
  {
      Serial.println("********* Player ---- 2 ---- WON *********");
      digitalWrite(LedPin_Player_2, HIGH); 
 }
}

void loop()
{
  digitalWrite(LedPin_Color_1, HIGH);  // Turning off RGB led
  digitalWrite(LedPin_Color_2, HIGH);  // Turning off RGB led
  digitalWrite(LedPin_Player_1, LOW); 
  digitalWrite(LedPin_Player_2, LOW);  
  
  delay(1000);      // Wait for 1000 millisecond(s)
  
  Led_Color = random(1, 2 + 1); // Choose a random number (1 or 2) represent the RGB color
  
  if (Led_Color == 1)   // Turn on the right color  
  {
    digitalWrite(LedPin_Color_1, LOW);
  } 
  else 
  {
    digitalWrite(LedPin_Color_2, LOW);
  }
  
  No_One_Touched_A_Target = 1;
  
  while (No_One_Touched_A_Target)   // Wait for a player to touch a target  
  {
    Player_1_V = analogRead(A1);
    Player_2_V = analogRead(A2);
    
    Serial.print("Player 1 V = ");
    Serial.print(Player_1_V);
    Serial.print("; \t Player 2 V = ");
    Serial.println(Player_2_V);
    
// Testing Player 1 if he is touching and if he is correct:   
    
    if (Player_1_V < 400) 
    {
      if (Led_Color == GREEN) 
      {
        Someone_Won(1);
      } 
      else 
      {
        Someone_Won(2);
      }
      No_One_Touched_A_Target = 0;
    }
    if (Player_1_V > 600) 
    {
      if (Led_Color == RED) 
      {
        Someone_Won(1);
      } 
      else 
      {
        Someone_Won(2);
      }
      No_One_Touched_A_Target = 0;
    }
    
// Testing Player 2 if he is touching and if he is correct:   
    
    if (Player_2_V < 400) 
    {
      if (Led_Color == GREEN) 
      {
        Someone_Won(2);
      } 
      else 
      {
        Someone_Won(1);
      }
      No_One_Touched_A_Target = 0;
    }
    if (Player_2_V > 600) 
    {
      if (Led_Color == RED) 
      {
        Someone_Won(2);
      } 
      else 
      {
        Someone_Won(1);
      }
      No_One_Touched_A_Target = 0;
    }
  }
  delay(2000); // Wait for 1000 millisecond(s)
}

