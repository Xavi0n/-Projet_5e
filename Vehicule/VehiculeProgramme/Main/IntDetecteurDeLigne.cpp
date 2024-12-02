/**************************************************************************************************
Nom du fichier : IntDetecteurDeLigne.cpp
//  Auteur : Naomie Dion
//  Date de création : 27 Novembre 2024
Version 1.1
***************************************************************************************************/
// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************
#include "IntDetecteurDeLigne.h"
#include "PiloteI2C.h"
#include "Main.h"
// *************************************************************************************************
//  CONSTRUCTEUR
// *************************************************************************************************
void vInitPcfI2C(void) 
{
    piloteI2C_initialise();
}
// *************************************************************************************************
//  Nom de la fonction: vEcrirePcf
//  Auteur : Naomie Dion
//  Date de création : 27 Novembre 2024
//  Description : Écrit un octet sur le PCF8574 via I2C
//  Paramètres d'entrées : ucDataPcf - L'octet à écrire
//  Paramètres de sortie : Aucun
// *************************************************************************************************
void vEcrirePcf(unsigned char ucDataPcf) 
{
  piloteI2C_ecrisUnOctet(0x3A, ucDataPcf);
}
// *************************************************************************************************
//  Nom de la fonction: ucLecturePcf
//  Auteur : Naomie Dion
//  Date de création : 27 Novembre 2024
//  Description : Lit un octet du PCF8574 via I2C
//  Paramètres d'entrées : Aucun
//  Paramètres de sortie : L'octet lu
// *************************************************************************************************
unsigned char ucLecturePcf(void) 
{
    return piloteI2C_lisUnOctet(0x3A);
}
// *************************************************************************************************
//  Nom de la fonction: EtatDetecteurDeLigne
//  Auteur : Naomie Dion
//  Date de création : 27 Novembre 2024
//  Description : Sert a activer ou desactiver le suiveur de ligne
//  Paramètres d'entrées : Aucun
//  Paramètres de sortie : ucEtatDetecteur
// *************************************************************************************************
void vEtatDetecteurDeLigne(unsigned char ucEtatDetecteur) 
{
    switch(ucEtatDetecteur)
    {
      case 'ON':
      piloteI2C_ecrisUnOctet(0x3A, 0xFF);
      break;
      
      case 'OFF':
      piloteI2C_ecrisUnOctet(0x3A, 0x1F);
      break;
    }
}

