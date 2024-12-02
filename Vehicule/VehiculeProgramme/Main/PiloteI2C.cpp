/**************************************************************************************************
// Nom du fichier: PiloteI2C.cpp
// Auteur: Naomie Dion
// Date de création: 21 Novembre 2024
//
// Description:
//
***************************************************************************************************/
//INCLUSIONS
#include <Wire.h>
#include "Main.h"
#include "PiloteI2C.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
unsigned char piloteI2C_lisUnOctet(unsigned char Adresse)
{
  Wire.requestFrom((uint8_t)Adresse, (uint8_t)1);
  return (unsigned char)(Wire.read()); 
}

void piloteI2C_ecrisUnOctet(unsigned char Adresse, unsigned char Octet)
{
  Wire.beginTransmission((uint8_t)Adresse);
  Wire.write((uint8_t)Octet);
  Wire.endTransmission();
}

unsigned int piloteI2C_lisUnEntier(unsigned char Adresse)
{
  Wire.requestFrom((uint8_t)Adresse, (uint8_t)2);
  return (unsigned int)(Wire.read() & 0x1F); 
}

void piloteI2C_ecrisUnEntier(unsigned char Adresse, unsigned int Entier)
{
  Wire.beginTransmission((uint8_t)Adresse);
  Wire.write((unsigned char)(Entier));
  Wire.endTransmission();  
}

void piloteI2C_initialise(void)
{
  Wire.begin();  
}

