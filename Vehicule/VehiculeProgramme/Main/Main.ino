/**************************************************************************************************
// Nom du fichier:  Main.ino
// Auteur: Naomie Dion
// Date de création: 21 Novembre 2024
//
// Description:
//
***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include "Main.h"
#include "PiloteI2C.h"
#include "IntDetecteurDeLigne.h"
#include "ProcessusLigne.h"
#include "ProcessusConduite.h"
#include <Arduino.h>
// *************************************************************************************************
//  DEFINES
// *************************************************************************************************

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************

// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************


// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************
int iTabInfoRoues[8];// {GH1, GH2, DH3, DH4, GB3, GB4, DB1, DB2}

int GH1 = 13; //GH1
int GH2 = 12; //GH2
int DH3 = 27; //DH3
int DH4 = 33; //DH4
int GB3 = 25; //GB3
int GB4 = 26; //GB4
int DB1 = 21; //DB1
int DB2 = 4;  //DB2 				
// *************************************************************************************************
void setup() 
{
  vInitPcfI2C();
  pinMode(GH1, OUTPUT);
  pinMode(GH2, OUTPUT);
  pinMode(DH3, OUTPUT);
  pinMode(DH4, OUTPUT);
  pinMode(GB3, OUTPUT);
  pinMode(GB4, OUTPUT);
  pinMode(DB1, OUTPUT);
  pinMode(DB2, OUTPUT);
  piloteI2C_ecrisUnOctet(0x3A, 0xFF);  //pour mettre a on le suiveur de ligne
  //Serial.begin(19200);
}

void loop() 
{

  /*Serial.println(iTabInfoRoues[0]);
  Serial.println(iTabInfoRoues[1]);
  Serial.println(iTabInfoRoues[2]);
  Serial.println(iTabInfoRoues[3]);
  Serial.println(iTabInfoRoues[4]);
  Serial.println(iTabInfoRoues[5]);
  Serial.println(iTabInfoRoues[6]);
  Serial.println(iTabInfoRoues[7]);
   delay(2000);*/
  vDisposition();
  vPosition();
}
