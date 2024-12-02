//PiloteTaskServer:
//Historique: 
// 2021-04-16, Yves Roy, creation

//INCLUSIONS
#define _TASK_MICRO_RES  //requis par TaskScheduler
#include "Main.h"
#include "PiloteTaskServer.h"

//Definitions privees
//pas de definitions privees
		
//Declarations de fonctions privees:
void PiloteTaskServer_neFaitRien(void);
void PiloteTaskServer_gereLesTaches(void);

//Definitions de variables privees:
//pas de variables privees


//Definitions de fonctions privees:
void piloteTaskServer_neFaitRien(void)
{
}

void piloteTaskServer_gereLesTaches(void)
{
  piloteTaskServer_execute();
}

//Definitions de variables publiques:
Scheduler piloteTaskServer_gestion; //doit etre defini avant Task pour que ca fonctionne
Task piloteTaskServer_tache(PILOTETASKSERVER_PERIODE_EN_US, TASK_FOREVER,  
    &piloteTaskServer_gereLesTaches, &piloteTaskServer_gestion, true);//doit etre precede de Scheduler
void (*piloteTaskServer_execute)(void);

//Definitions de fonctions publiques:
void piloteTaskServer_DemarreLesTachesALaTouteFinDeSetup(void)
{
	piloteTaskServer_gestion.startNow();
//	PiloteTaskServer_gestion.enableAll();    
}

void piloteTaskServer_initialise(void)
{
  piloteTaskServer_execute = piloteTaskServer_neFaitRien;
}

