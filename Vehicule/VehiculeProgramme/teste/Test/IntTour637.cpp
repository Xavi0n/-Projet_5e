/**************************************************************************************************
//  Nom du fichier : IntTour637.cpp
//  Auteur : Naomie Dion
//  Date de création : 2 Decembre 2024
//  Version 1.1
***************************************************************************************************/
// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************
#include "ServiceWiFiUdp.h"
#include <WiFiUdp.h>
#include "IntTour637.h"
// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************


// *************************************************************************************************
//  FONCTIONS
// *************************************************************************************************
void vDecriptageIncomingPacket(void)
{
 unsigned char ucCommande = IncomingPacket[1];
 switch(ucCommande)
 {
  case 'A':  //Arret

  break;

  case 'D':  //Debut

  break;

  case 'R':  //Reinitialisation

  break;

  case 'E':  //Erreur

  break;

  case 'I':  //Information
   unsigned char ucCouleur = IncomingPacket[2];
   switch(ucCouleur)
   {
     case 'O':  //Orange

     break;

     case 'N':  //Noir

     break;

     case 'M':  //Metal

     break;
   }
  break;
 }
}