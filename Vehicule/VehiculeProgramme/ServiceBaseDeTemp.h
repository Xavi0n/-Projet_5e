#ifndef SERVICEBASEDETEMP_H
#define SERVICEBASEDETEMP_H

//MODULE: serviceBaseDeTemps
//DESCRIPTION: pour mettre en place un service d'appels periodiques de fonctions
//pointees par un tableau de pointeurs de fonctions. Le service met en place
//une base de temps qui reposent sur l'emploi des appels que peut faire le module
//serviceTaskServer

//HISTORIQUE:
// 2021-04-07, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 2
//#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 3
//#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ (PILOTETIMER0_FREQUENCE_DES_INTERRUPTIONS_EN_HZ)
//INFORMATION PUBLIQUE:

//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void serviceBaseDeTemps_gereDansLoop(void);
void serviceBaseDeTemps_initialise(void);

//Variables publiques:
extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);
extern void (*serviceBaseDeTemps_executeDansLoop[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP])(void);

#endif
