#ifndef INTERFACES0008_H
#define INTERFACES0008_H

//MODULE: interfaceS0008
//DESCRIPTION: implemente le protocole qui permet d'interagir avec un ensemble
//de developpement Dallas programme avec le logiciel 247-637 S-0008

//HISTORIQUE:
// 2018-10-28, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACES0008_PHASE_RECEPTION 0
//#define INTERFACES0008_PHASE_TRANSMISSION 1


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INTERFACES0008_RELACHE  0x00
#define INTERFACES0008_APPUYE  0xFF
#define INTERFACES0008_NOMBRE_D_OCTETS_A_TRANSMETTRE 4
#define INTERFACES0008_NOMBRE_D_OCTETS_A_RECEVOIR INTERFACES0008_NOMBRE_D_OCTETS_A_TRANSMETTRE
#define INTERFACES0008_PAS_D_ERREURS 0
#define INTERFACES0008_ERREUR_AU_NIVEAU_DU_PILOTE 1
#define INTERFACES0008_ERREUR_OCTET_INVALIDE 2

typedef struct
{
  unsigned char information;  
  unsigned char statut;
  unsigned char octetsRecus[INTERFACES0008_NOMBRE_D_OCTETS_A_RECEVOIR];
    unsigned char requete;
  unsigned char octetsATransmettre[INTERFACES0008_NOMBRE_D_OCTETS_A_TRANSMETTRE];
} INTERFACES0008;

//Fonctions publiques:
void interfaceS0008_initialise(void);

//Variables publiques:
extern INTERFACES0008 interfaceS0008;

#endif
