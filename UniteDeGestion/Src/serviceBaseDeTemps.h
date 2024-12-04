#ifndef SERVICEBASEDETEMPS_H
#define SERVICEBASEDETEMPS_H

//MODULE: serviceBaseDeTemps
//DESCRIPTION: pour mettre en place un service d'appels periodiques de fonctions
//pointées par un tableau de pointeurs de fonctions. Le service met en place
//une base de temps qui reposent sur l'emploi d'interruptions qui sont générées
//par le compteur Timer6 du STM32F407 qui opère en mode Up

//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 3
//pas de dépendances logicielles

//INFORMATION PUBLIQUE:

//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void serviceBaseDeTemps_initialise(void);

//Variables publiques:
extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

#endif
