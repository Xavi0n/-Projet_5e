/**************************************************************************************************
//  Nom du fichier : ProcessusConduite.cpp
//  Auteur : Naomie Dion
//  Date de création : 28 Novembre 2024
//  Version 1.1
***************************************************************************************************/
// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************
#include "ProcessusConduite.h"
#include "Main.h"
#include <Arduino.h>
// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************

// *************************************************************************************************
//  FONCTIONS
// *************************************************************************************************
void vPosition(void)
{
  analogWrite(GH1, iTabInfoRoues[0]);
  analogWrite(GH2, iTabInfoRoues[1]);
  analogWrite(DH3, iTabInfoRoues[2]);
  analogWrite(DH4, iTabInfoRoues[3]);
  analogWrite(GB3, iTabInfoRoues[4]);
  analogWrite(GB4, iTabInfoRoues[5]);
  analogWrite(DB1, iTabInfoRoues[6]);
  analogWrite(DB2, iTabInfoRoues[7]);
}