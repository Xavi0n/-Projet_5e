#ifndef SERVICEPROTOCOLECAN_H
#define SERVICEPROTOCOLECAN_H

//MODULE: serviceProtocoleCAN

//utilisant un pointeur de fonctions du module serviceBaseDeTemps

//HISTORIQUE:
// 2024-10-28, Felix Tremblay, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")


/******************* A MODIFIE ********************/

//#define SERVICEPROTOCOLECAN_PHASE_RECEPTION 0
//#define SERVICEPROTOCOLECAN_PHASE_TRANSMISSION 1
//#define SERVICEPROTOCOLECAN_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ 500.0
//#define SERVICEPROTOCOLECAN_NOMBRE_DE_DONNEES_MAXIMUM  8
//#define SERVICEPROTOCOLECAN_TEMPS_D_ATTENTE_MAXIMAL_EN_MS 4
//#define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ 2000.0



//INFORMATION PUBLIQUE:
//Definitions publiques:
#define SERVICEPROTOCOLECAN_PAS_D_ERREURS 0
#define SERVICEPROTOCOLECAN_ERREUR_EN_ATTENTE 1
#define SERVICEPROTOCOLECAN_ERREUR_TEMPS_DEPASSE 2



typedef struct
{
  unsigned char etatDuModuleDeReception;  
  unsigned char information;
  unsigned char octetsRecus[SERVICEPROTOCOLECAN_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char nombreATransmettre;
  unsigned char requete;
  unsigned char octetsATransmettre[SERVICEPROTOCOLECAN_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char statut;
} SERVICEPROTOCOLECAN;

//Fonctions publiques:
void serviceProtocoleCAN_initialise(void);

//Variables publiques:
extern SERVICEPROTOCOLECAN serviceProtocoleCAN;

#endif
