#ifndef PILOTEUSART2_H
#define PILOTEUSART2_H

//MODULE: piloteUSART2
//DESCRIPTION: pour utiliser le USART2
//HISTORIQUE:
// 2018-09-30, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielle
//pas de dépendances matérielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PILOTEUSART2_DISPONIBLE  1
#define PILOTEUSART2_PAS_DISPONIBLE 0
#define PILOTEUSART2_TRANSMIS 0
#define PILOTEUSART2_PAS_TRANSMIS 1

//Fonctions publiques:
void piloteUSART2_initialise(void);
unsigned char piloteUSART2_octetDisponible(void);
unsigned char piloteUSART2_octetTransmis(void);
unsigned char piloteUSART2_litUnOctetRecu(void);
void piloteUSART2_confirmeLaReception(void);
void piloteUSART2_confirmeLaFinDeTransmission(void);
void piloteUSART2_transmet(unsigned char Octet);

//Variables publiques:
//pas de variables publiques

#endif
