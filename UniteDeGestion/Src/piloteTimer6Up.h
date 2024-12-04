#ifndef PILOTETIMER6UP_H
#define PILOTETIMER6UP_H

//MODULE: piloteTimer6Up
//DESCRIPTION: pour permettre des interruptions périodiques par Timer6
//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances matérielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTETIMER6UP_COMPTE_MAX  (\
//  (unsigned int)((FREQUENCE_D_OSCILLATEUR_EN_KHZ \
//  /FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ * 1000.0)-1.0)

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
void piloteTimer6Up_initialise(void);
void piloteTimer6Up_permetLesInterruptions(void);

//Variables publiques:
extern void (*piloteTimer6Up_execute)(void);

#endif
