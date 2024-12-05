//ProcessusPasserelle:
//Historique: 
// 2024-12-03, Xavier Champoux, creation

//INCLUSIONS
#include <string.h>
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "serviceProtocoleCAN.h"
#include "ProcessusPasserelle.h"

//Definitions privees


//Declarations de fonctions privees:

//Definitions de variables privees:


//Definitions de fonctions privees:

void processusPasserelle_copieDansUART(void)
{
  memcpy(serviceProtocole637.octetsATransmettre, serviceProtocoleCAN.octetsRecus, 8);   //Copy Data from the CAN reception buffer to the UART transmission buffer
  serviceProtocole637.requete = REQUETE_ACTIVE;
}

void processusPasserelle_copieDansCAN(void)
{
  memcpy(serviceProtocoleCAN.octetsATransmettre, serviceProtocole637.octetsRecus, 8);   //Copy Data from the CAN reception buffer to the UART transmission buffer
  serviceProtocoleCAN.requete = REQUETE_ACTIVE;
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques: