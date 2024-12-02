#ifndef PILOTEI2C_H
#define PILOTEI2C_H

//MODULE: piloteI2C1
//DESCRIPTION: pour permettre l'emploi d'un port I2C

// 2021-07-08, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:
unsigned char piloteI2C_lisUnOctet(unsigned char Adresse);
void piloteI2C_ecrisUnOctet(unsigned char Adresse, unsigned char Octet);
unsigned int piloteI2C_lisUnEntier(unsigned char Adresse);
void piloteI2C_ecrisUnEntier(unsigned char Adresse, unsigned int Entier);
void piloteI2C_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif