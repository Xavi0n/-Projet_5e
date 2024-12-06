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
  if (serviceProtocoleCAN.information == INFORMATION_DISPONIBLE)
  {
    memset (serviceProtocole637.octetsATransmettre, 0, sizeof(serviceProtocole637.octetsATransmettre));
    memcpy(serviceProtocole637.octetsATransmettre, serviceProtocoleCAN.octetsRecus, 8);   //Copy Data from the CAN reception buffer to the UART transmission buffer
    serviceProtocole637.nombreATransmettre = 8;
    serviceProtocole637.requete = REQUETE_ACTIVE;
    memset (serviceProtocoleCAN.octetsRecus, 0, sizeof(serviceProtocoleCAN.octetsRecus));
    serviceProtocoleCAN.information = INFORMATION_TRAITEE;
  }
}

void processusPasserelle_copieDansCAN(void)
{
  if (serviceProtocole637.information == INFORMATION_DISPONIBLE)
  {
    memset (serviceProtocoleCAN.octetsATransmettre, 0, sizeof(serviceProtocoleCAN.octetsATransmettre));
    memcpy(serviceProtocoleCAN.octetsATransmettre, serviceProtocole637.octetsRecus, 8);   //Copy Data from the CAN reception buffer to the UART transmission buffer
    serviceProtocoleCAN.nombreATransmettre = 8;
    serviceProtocoleCAN.requete = REQUETE_ACTIVE;
    memset (serviceProtocole637.octetsRecus, 0, sizeof(serviceProtocole637.octetsRecus));
    serviceProtocole637.information = INFORMATION_TRAITEE;
  }
}

void InitProcessusPasserelle(void)
{
  serviceBaseDeTemps_execute[PROCESSUSPASSERELLE_TRANSMISSION_CAN] = processusPasserelle_copieDansCAN;
  serviceBaseDeTemps_execute[PROCESSUSPASSERELLE_TRANSMISSION_UART] = processusPasserelle_copieDansUART;
}
//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques: