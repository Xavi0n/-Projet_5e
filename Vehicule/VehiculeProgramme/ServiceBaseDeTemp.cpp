//serviceBaseDeTemps:
//Historique: 
// 2021-04-04, Yves Roy, creation

//INCLUSIONS
#include "Main.h"
#include "PiloteTaskServer.h"
#include "ServiceBaseDeTemp.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void serviceBaseDeTemps_neFaitRien(void);
void serviceBaseDeTemps_gere(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void serviceBaseDeTemps_neFaitRien(void)
{
}

void serviceBaseDeTemps_gere(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i]();
  }
}
    
//Definitions de variables publiques:
void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);
void (*serviceBaseDeTemps_executeDansLoop[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP])(void);

//Definitions de fonctions publiques:
void serviceBaseDeTemps_gereDansLoop(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP; i++)
  {
    serviceBaseDeTemps_executeDansLoop[i]();
  }
}
void serviceBaseDeTemps_initialise(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i] = serviceBaseDeTemps_neFaitRien;
  }
  piloteTaskServer_execute = serviceBaseDeTemps_gere;

  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP; i++)
  {
    serviceBaseDeTemps_executeDansLoop[i] = serviceBaseDeTemps_neFaitRien;
  }
}
