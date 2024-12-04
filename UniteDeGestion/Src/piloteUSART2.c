//piloteUSART2:
//Historique: 
// 2018-09-30, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUSART2.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
extern UART_HandleTypeDef huart2; //defini par le hal dans main

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteUSART2_octetDisponible(void)
{
  return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE);
}

unsigned char piloteUSART2_octetTransmis(void)
{
  return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC);
}

unsigned char piloteUSART2_litUnOctetRecu(void)
{
  return huart2.Instance->DR;
}
void piloteUSART2_transmet(unsigned char Octet)
{
  huart2.Instance->DR = Octet;
}

void piloteUSART2_confirmeLaReception(void)
{
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);  
}

void piloteUSART2_confirmeLaFinDeTransmission(void)
{
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);  
}

void piloteUSART2_initialise(void)
{
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);
  __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);
}
