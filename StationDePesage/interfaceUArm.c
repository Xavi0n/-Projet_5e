//interfaceUArm
//Historique: 
//2018-11-12, Yves Roy, creation
//18/11/2024, Josée Girard, Modification pour adapter d'un interfaceMalyan vers un interfaceUArm

//INCLUSIONS
#include "main.h"
#include "piloteSerieUSB.h"
#include "interfaceUArm.h"

//Definitions privees
#define INTERFACEUARM_LONGUEUR_MAXIMALE_DES_COMMANDES 64
#define INTERFACEUARM_LONGUEUR_MAXIMALE_DES_REPONSES 64

//Declarations de fonctions privees:
int interfaceUArm_ecritUneCommande(char *cCommande, unsigned char ucLongueur);
int interfaceUArm_recoitUneReponse(char *cReponse, unsigned char ucLongueurMaximale);

//Definitions de variables privees
unsigned char interfaceUArm_commande[INTERFACEUARM_LONGUEUR_MAXIMALE_DES_COMMANDES];
unsigned char interfaceUArm_reponse[INTERFACEUARM_LONGUEUR_MAXIMALE_DES_REPONSES];

//Definitions de fonctions privees:
int interfaceUArm_ecritUneCommande(char *Commande, unsigned char Longueur)
{
    int retour;
    retour = piloteSerieUSB_ecrit(Commande, Longueur);
    if (retour != (int)Longueur)
    {
        return -1;
    }
    piloteSerieUSB_attendLaFinDeLEcriture();
    return retour;
}

int interfaceUArm_recoitUneReponse(char *cReponse, unsigned char ucLongueurMaximale)
{
    return piloteSerieUSB_lit(cReponse, ucLongueurMaximale);  
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
int interfaceUArm_initialise(void)
{
  return 0;
}

int interfaceUArm_termine(void)
{
  return 0;
}

int interfaceUArm_demarreVentouse(void)
{
  return interfaceUArm_ecritUneCommande("M2231 V1\n", 9);  
}

int interfaceUArm_arreteVentouse(void)
{
  return interfaceUArm_ecritUneCommande("M2231 V1\n", 9);
}

int interfaceUArm_BougePosition(int iX, int iY, int iZ)
{
    unsigned char ucPosition[64];
    sprintf(ucPosition, "G0 X%d Y%d Z%d F8000\n", iX, iY, iZ); 
    return interfaceUArm_ecritUneCommande(ucPosition, 24);
}