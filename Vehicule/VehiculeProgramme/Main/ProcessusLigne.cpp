/**************************************************************************************************
//  Nom du fichier : ProcessusLigne.cpp
//  Auteur : Naomie Dion
//  Date de création : 27 Novembre 2024
//  Version 1.1
***************************************************************************************************/
// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************
#include "ProcessusLigne.h"
#include "IntDetecteurDeLigne.h"
#include "Main.h"
// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************


// *************************************************************************************************
//  FONCTIONS
// *************************************************************************************************
void vDisposition(void)
{
  unsigned char ucPcf = ucLecturePcf();
  switch (ucPcf)
  {
  // Ligne pleine
    case 0xFF:
   //Roues Avant
    iTabInfoRoues[0] = 0; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 0; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 0; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 0; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  // Pas de ligne
    case 0xE0:
  //Roue Avant
    iTabInfoRoues[0] = 0; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 0; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 0; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 0; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
    
  // Millieu
    case 0xE4:
//Roue Avant
    iTabInfoRoues[0] = 138; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 138; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 138; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 138; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;

  // Un peu a droite
    case 0xEC:
 //Roue Avant
    iTabInfoRoues[0] = 150; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 1; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 150; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 1; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  // A droite
    case 0xE8:
 //Roue Avant
    iTabInfoRoues[0] = 175; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 1; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 175; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 1; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  // Moyen a droite
    case 0xF8:
 //Roue Avant
    iTabInfoRoues[0] = 200; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 1; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 200; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 1; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  // Tres a droite
    case 0xF0:
 //Roue Avant
    iTabInfoRoues[0] = 255; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 1; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 255; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 1; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;

  // Un peu a gauche
    case 0xE6:
//Roue Avant
    iTabInfoRoues[0] = 1; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 150; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 1; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 150; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  // A gauche
    case 0xE2:
//Roue Avant
    iTabInfoRoues[0] = 1; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 175; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 1; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 175; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  // Moyen a gauche
    case 0xE3:
//Roue Avant
    iTabInfoRoues[0] = 1; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 200; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 1; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 200; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  // Tres a gauche
    case 0xE1:
//Roue Avant
    iTabInfoRoues[0] = 1; //GH1
    iTabInfoRoues[1] = 0; //GH2
    iTabInfoRoues[2] = 255; //DH3
    iTabInfoRoues[3] = 0; //DH4
  //Roue Arriere
    iTabInfoRoues[4] = 1; //GB3
    iTabInfoRoues[5] = 0; //GB4
    iTabInfoRoues[6] = 255; //DB1
    iTabInfoRoues[7] = 0; //DB2
    break;
  }
}
