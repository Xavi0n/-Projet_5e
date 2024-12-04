//piloteCAN1:
//Historique: 
// 2018-11-12, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteCAN1.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Declarations de variables privees:
extern CAN_HandleTypeDef hcan1; //défini par le hal dans main

//Definitions de variables privees:
CAN_RxHeaderTypeDef piloteCAN1_reception;
CAN_TxHeaderTypeDef piloteCAN1_transmission;
CAN_FilterTypeDef piloteCAN1_filtre;
unsigned int piloteCAN1_CasierPostal;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned int piloteCAN1_messageDisponible(void)
{
  return HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_FILTER_FIFO0);  
}

unsigned int piloteCAN1_messageTransmis(void)
{
  return HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
}

unsigned char piloteCAN1_litUnMessageRecu(unsigned char *DonneesRecues)
{
  if (HAL_CAN_GetRxMessage(&hcan1, CAN_FILTER_FIFO0,
                           &piloteCAN1_reception, DonneesRecues) != HAL_OK)
  {
    return PILOTECAN1_PAS_DISPONIBLE;
  }
  return PILOTECAN1_DISPONIBLE;
}

unsigned int piloteCAN1_transmetDesDonnes(unsigned int Identification11Bits,
                                          unsigned char *Donnees,
                                          unsigned char Nombre)
{
  piloteCAN1_transmission.StdId = Identification11Bits; // << 5;
  piloteCAN1_transmission.DLC = Nombre;
  if (HAL_CAN_AddTxMessage(&hcan1, &piloteCAN1_transmission,
                           Donnees, &piloteCAN1_CasierPostal) != HAL_OK)
  {
    return PILOTECAN1_PAS_TRANSMIS;
  }
  return PILOTECAN1_TRANSMIS;
}

unsigned int piloteCAN1_initialise(void)
{
  piloteCAN1_transmission.ExtId = 0;
  piloteCAN1_transmission.IDE = CAN_ID_STD;
  piloteCAN1_transmission.RTR = CAN_RTR_DATA;
  piloteCAN1_transmission.TransmitGlobalTime = DISABLE;
  
  piloteCAN1_filtre.FilterIdHigh = PILOTECAN1_IDENTIFICATION_EN_RECEPTION ;// << 5;
  piloteCAN1_filtre.FilterIdLow = 0x0;
  piloteCAN1_filtre.FilterMaskIdHigh = PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION ;//<< 21;
  piloteCAN1_filtre.FilterMaskIdLow = 0x0;
  piloteCAN1_filtre.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  piloteCAN1_filtre.FilterBank = 13;
  piloteCAN1_filtre.FilterMode = CAN_FILTERMODE_IDMASK;
  piloteCAN1_filtre.FilterScale = CAN_FILTERSCALE_32BIT;
  piloteCAN1_filtre.FilterActivation = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan1, &piloteCAN1_filtre) != HAL_OK)
  {
    return PILOTECAN1_ERREUR;
  }
//#define TEST
//#ifdef TEST
//  piloteCAN1_filtre.FilterIdHigh = (PILOTECAN1_IDENTIFICATION_EN_RECEPTION+1) << 5;
//  piloteCAN1_filtre.FilterMaskIdHigh = (PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION+1) << 21;  
//  piloteCAN1_filtre.FilterBank = 13;
  
//  if (HAL_CAN_ConfigFilter(&hcan1, & piloteCAN1_filtre) != HAL_OK)
//  {
//    return PILOTECAN1_ERREUR;
//  }
//#endif
  
  
  if (HAL_CAN_Start(&hcan1) != HAL_OK)
  {
    return PILOTECAN1_ERREUR;
  }
  return PILOTECAN1_PAS_D_ERREUR;
}
