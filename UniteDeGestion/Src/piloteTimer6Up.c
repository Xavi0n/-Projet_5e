//piloteTimer6Up:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteTimer6Up.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

//Definitions de variables privees:
extern TIM_HandleTypeDef htim6; //definie par le hal et declare ici


//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
void (*piloteTimer6Up_execute)(void);

//Definitions de fonctions publiques:
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim6)
  {
    piloteTimer6Up_execute();
  }
}

void piloteTimer6Up_permetLesInterruptions(void)
{
  HAL_TIM_Base_Start_IT(&htim6);  
}

void piloteTimer6Up_initialise(void)
{  
  piloteTimer6Up_execute = neFaitRien;  
}




