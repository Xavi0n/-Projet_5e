/****************************************************************************************
//  Nom du fichier : Main.h 
//  Auteur : Naomie Dion                 
//  Date de création : 21 Novembre 2024
//
// Description:
//
//  Version 3.0  
****************************************************************************************/
#ifndef MAIN_H
#define MAIN_H

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************
#include "IntDetecteurDeLigne.h"
// *************************************************************************************************
//  CONSTANTS
// *************************************************************************************************
//Dépendances matérielles:

//Dépendances logicielles:
#define PILOTETASKSERVER_PERIODE_EN_US (4000L)
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ ((1000000L)/PILOTETASKSERVER_PERIODE_EN_US)

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 2

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1 


//Definitions publiques:

// *************************************************************************************************
//  PROTOTYPE DE FONCTIONS
// *************************************************************************************************

#endif 
