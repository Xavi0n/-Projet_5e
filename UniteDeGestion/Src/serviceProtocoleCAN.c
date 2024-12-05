//serviceProtocoleCAN:
//Historique: 
// 2024-10-28, Felix Tremblay, creation

//INCLUSIONS
#include "main.h"
#include "piloteCAN1.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocoleCAN.h"
#include "ProcessusPasserelle.h"


//Definitions privees
#define SERVICEPROTOCOLECAN_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION (\
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / SERVICEPROTOCOLECAN_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ )

#define SERVICEPROTOCOLECAN_TRANSMISSION_PERMISE 1
#define SERVICEPROTOCOLECAN_TRANSMISSION_RETARDEE 0

#define SERVICEPROTOCOLECAN_RECEPTION_PERMISE 1
#define SERVICEPROTOCOLECAN_RECEPTION_RETARDEE 0

#define SERVICEPROTOCOLECAN_LECTURE_PAS_DISPONIBLE 0
#define SERVICEPROTOCOLECAN_LECTURE_DISPONIBLE 1

#define SERVICEPROTOCOLECAN_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS (\
    SERVICEPROTOCOLECAN_TEMPS_D_ATTENTE_MAXIMAL_EN_MS * SERVICEPROTOCOLECAN_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ / 1000.0)

#define SERVICEPROTOCOLECAN_TEMPS_DEPASSE 1
#define SERVICEPROTOCOLECAN_TEMPS_PAS_DEPASSE 0

#define SERVICEPROTOCOLECAN_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION (\
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ /SERVICEPROTOCOLECAN_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ)


//Declarations de fonctions privees:
void serviceProtocoleCAN_attendUneRequete(void);
void serviceProtocoleCAN_transmetUnBloc(void);

unsigned char serviceProtocoleCAN_gereLaSynchronisationDesTransmissions(void);

void serviceProtocoleCAN_attendUneReception(void);
void serviceProtocoleCAN_LitUnBloc(void);

unsigned char serviceProtocoleCAN_gereLeTempsDAttente(void);
unsigned char serviceProtocoleCAN_gereLaSynchronisationDesReceptions(void);


//Definitions de variables privees:


/******************** A MODIFIE ******************/

unsigned char serviceProtocoleCAN_compteurDeSynchronisationDesTransmissions;
unsigned char serviceProtocoleCAN_compteurDeSynchronisationDesReceptions;
unsigned char serviceProtocoleCAN_compteurDeTempsDAttente;




//Definitions de fonctions privees:
void serviceProtocoleCAN_attendUneRequete(void)
{
  if (serviceProtocoleCAN.requete == REQUETE_TRAITEE)
  {
    return;
  }
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECAN_PHASE_TRANSMISSION] =  
    serviceProtocoleCAN_transmetUnBloc;
}



void serviceProtocoleCAN_transmetUnBloc(void)
{
  if (serviceProtocoleCAN_gereLaSynchronisationDesTransmissions()
      == SERVICEPROTOCOLECAN_TRANSMISSION_RETARDEE)
  {
    return;
  }
  if(piloteCAN1_messageTransmis() == PILOTECAN1_PAS_TRANSMIS)
  {
    return;
  }
  piloteCAN1_transmetDesDonnes(PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION, 
                               serviceProtocoleCAN.octetsATransmettre, 
                               serviceProtocoleCAN.nombreATransmettre);
  
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECAN_PHASE_TRANSMISSION] =  
    serviceProtocoleCAN_attendUneRequete;
  serviceProtocoleCAN.requete = REQUETE_TRAITEE;
}




unsigned char serviceProtocoleCAN_gereLaSynchronisationDesTransmissions(void)
{
  serviceProtocoleCAN_compteurDeSynchronisationDesTransmissions++;
  if (serviceProtocoleCAN_compteurDeSynchronisationDesTransmissions < SERVICEPROTOCOLECAN_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION)
  {
    return SERVICEPROTOCOLECAN_TRANSMISSION_RETARDEE;
  }
  serviceProtocoleCAN_compteurDeSynchronisationDesTransmissions = 0;
  return SERVICEPROTOCOLECAN_TRANSMISSION_PERMISE;
}



 

void serviceProtocoleCAN_attendUneReception(void)
{
  if (serviceProtocoleCAN_gereLaSynchronisationDesReceptions() == SERVICEPROTOCOLECAN_RECEPTION_RETARDEE)
  {  
    return;
  }
  
  
  /*
  if (serviceProtocoleCAN_gereLeTempsDAttente() == SERVICEPROTOCOLECAN_TEMPS_DEPASSE)
  {
    serviceProtocoleCAN.statut = SERVICEPROTOCOLECAN_TEMPS_DEPASSE;
    serviceProtocoleCAN.information = INFORMATION_DISPONIBLE;
    //serviceBaseDeTemps_execute[SERVICEPROTOCOLECAN_PHASE_RECEPTION] =
      //serviceProtocleCAN_attendUneReception;
    serviceProtocoleCAN_compteurDeTempsDAttente = 0;
    return;
  }
  */

  
  if (piloteCAN1_messageDisponible() == PILOTECAN1_PAS_DISPONIBLE)
  { 
    return;
  }
  
  piloteCAN1_litUnMessageRecu(serviceProtocoleCAN.octetsRecus);
  serviceProtocoleCAN.information = INFORMATION_DISPONIBLE;
  serviceBaseDeTemps_execute[PROCESSUSPASSERELLE_TRANSMISSION_UART] = processusPasserelle_copieDansUART;
}




unsigned char serviceProtocoleCAN_gereLaSynchronisationDesReceptions(void)
{
  serviceProtocoleCAN_compteurDeSynchronisationDesReceptions++;
  if (serviceProtocoleCAN_compteurDeSynchronisationDesReceptions <
      SERVICEPROTOCOLECAN_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION)
  {
    return SERVICEPROTOCOLECAN_RECEPTION_RETARDEE;
  }
  else 
  {
      serviceProtocoleCAN_compteurDeSynchronisationDesReceptions = 0;
      return SERVICEPROTOCOLECAN_RECEPTION_PERMISE;
  }
  
}



unsigned char serviceProtocoleCAN_gereLeTempsDAttente(void)
{
  serviceProtocoleCAN_compteurDeTempsDAttente++;
  if (serviceProtocoleCAN_compteurDeTempsDAttente <
      SERVICEPROTOCOLECAN_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS)
  {
    return SERVICEPROTOCOLECAN_TEMPS_PAS_DEPASSE; 
  }
  return SERVICEPROTOCOLECAN_TEMPS_DEPASSE;
}



//Definitions de variables publiques:
SERVICEPROTOCOLECAN serviceProtocoleCAN;

//Definitions de fonctions publiques:
void serviceProtocoleCAN_initialise(void)
{
  serviceProtocoleCAN_compteurDeSynchronisationDesTransmissions = 0;
  serviceProtocoleCAN_compteurDeSynchronisationDesReceptions = 0;
  
  serviceProtocoleCAN.information = INFORMATION_TRAITEE;
  serviceProtocoleCAN.requete = REQUETE_TRAITEE;
  serviceProtocoleCAN.statut = SERVICEPROTOCOLECAN_PAS_D_ERREURS;
  
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECAN_PHASE_TRANSMISSION] =
    serviceProtocoleCAN_attendUneRequete;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECAN_PHASE_RECEPTION] =
    serviceProtocoleCAN_attendUneReception;
  
  serviceProtocoleCAN.etatDuModuleDeReception = MODULE_EN_FONCTION;
}


