//interfaceS0008:
//Historique: 
// 2018-10-28, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"
#include "serviceinterface637.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
void interfaceS0008_recupereLesDonneesRecues(void);
unsigned char interfaceS0008_valideLaReception(void);
void interfaceS0008_prepareLaTransmission(void);
void interfaceS0008_gereLaReception(void);
void interfaceS0008_gereLaTransmission(void);

//Definitions de variables privees:
//pas de variables privees
  
//Definitions de fonctions privees:
void interfaceS0008_recupereLesDonneesRecues(void)
{
unsigned char i;
  for (i = 0; i < INTERFACES0008_NOMBRE_D_OCTETS_A_RECEVOIR; i++)
  {
    interfaceS0008.octetsRecus[i] = serviceProtocole637.octetsRecus[i];
  }
}

unsigned char interfaceS0008_valideLaReception(void)
{
unsigned char i;
  for (i = 0; i < INTERFACES0008_NOMBRE_D_OCTETS_A_RECEVOIR; i++)
  {
    if ((interfaceS0008.octetsRecus[i] & 0x01) != 0x00) //test si impair
    {
      return INTERFACES0008_ERREUR_OCTET_INVALIDE;
    }
  }
  return INTERFACES0008_PAS_D_ERREURS;
}
  
void interfaceS0008_prepareLaTransmission(void)
{
unsigned char i;
  for (i = 0; i < INTERFACES0008_NOMBRE_D_OCTETS_A_TRANSMETTRE; i++)
  {
    serviceProtocole637.octetsATransmettre[i] = interfaceS0008.octetsATransmettre[i];
  }  
  serviceProtocole637.nombreATransmettre = INTERFACES0008_NOMBRE_D_OCTETS_A_TRANSMETTRE;
}

void interfaceS0008_gereLaReception(void)
{
  if (serviceProtocole637.information == INFORMATION_TRAITEE)
  {
    return;
  }
  serviceProtocole637.information = INFORMATION_TRAITEE;
  interfaceS0008.information = INFORMATION_DISPONIBLE;
  if (serviceProtocole637.statut != SERVICEPROTOCOLE637_PAS_D_ERREURS)
  {
    interfaceS0008.statut = INTERFACES0008_ERREUR_AU_NIVEAU_DU_PILOTE;
    return;
  }
  interfaceS0008_recupereLesDonneesRecues();
  interfaceS0008.statut = interfaceS0008_valideLaReception();
}

void interfaceS0008_gereLaTransmission(void)
{
  if (serviceProtocole637.requete == REQUETE_ACTIVE)
  {
    return;
  }
  if (interfaceS0008.requete == REQUETE_TRAITEE)
  {
    return;
  }
  interfaceS0008_prepareLaTransmission();
  serviceProtocole637.requete = REQUETE_ACTIVE;
  interfaceS0008.requete = REQUETE_TRAITEE;
 }

//Definitions de variables publiques:
INTERFACES0008 interfaceS0008;

//Definitions de fonctions publiques:
void interfaceS0008_initialise(void)
{
  interfaceS0008.information = INFORMATION_TRAITEE;
  interfaceS0008.requete = REQUETE_TRAITEE;
  interfaceS0008.statut = INTERFACES0008_PAS_D_ERREURS;
  
  serviceBaseDeTemps_execute[INTERFACES0008_PHASE_RECEPTION] =
      interfaceS0008_gereLaReception;
  serviceBaseDeTemps_execute[INTERFACES0008_PHASE_TRANSMISSION] =
      interfaceS0008_gereLaTransmission;
}
