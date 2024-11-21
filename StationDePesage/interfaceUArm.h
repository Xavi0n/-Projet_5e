#ifndef INTERFACEUARM_H
#define INTERFACEUARM_H

//HISTORIQUE:
// 2018-10-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
int interfaceUArm_initialise(void);
int interfaceUArm_termine(void);
int interfaceUArm_demarreVentouse(void);
int interfaceUArm_arreteVentouse(void);
int interfaceUArm_recoitUneReponse(char *cReponse, unsigned char ucLongueurMaximale);
int interfaceUArm_BougePosition(int iX, int iY, int iZ);

//Variables publiques:
//pas de variables publiques

#endif