/**************************************************************************************************
Nom du fichier : IntDetecteurDeLigne.h
Auteur : Naomie Dion
Date de création : 27 Novembre 2024
Version 1.1    
***************************************************************************************************/

#ifndef INTDETECTEURDELIGNE_H
#define INTDETECTEURDELIGNE_H

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************


// *************************************************************************************************
//  LES PROTOTYPES DES FONCTIONS
// *************************************************************************************************
  void vInitPcfI2C(void);
  void vEcrirePcf(unsigned char ucDataPcf);
  unsigned char ucLecturePcf(void);
  void vEtatDetecteurDeLigne(unsigned char ucEtatDetecteur);

#endif
 
