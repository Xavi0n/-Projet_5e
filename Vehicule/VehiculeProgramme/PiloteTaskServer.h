#ifndef PILOTETASKSERVER_H
#define PILOTETASKSERVER_H

//MODULE: PiloteTaskServer
//DESCRIPTION: pour permettre des appels périodiques de fonctions
//Ce module utilise la librairie TaskScheduler de Anatoli Arkhipenko V3.2.2
//Voir https://github.com/arkhipenko/TaskScheduler pour des informations a propos de cette librairie
//Il faut faire que l'appel de fonction serviceTaskServer_gestion.execute(); soit présent dans la boucle loop
//pour que la gestion des taches se fasse correctement.
//La definition SERVICETASKSERVER_PERIODE_EN_US permet d'indiquer combien de microsecondes doivent s'ecouler entre
//deux appels de taches. La frequence des appels est donnee par 1000000/SERVICETASKSERVER_PERIODE_EN_US
//L'instruction serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup() sert a mettre serviceTaskServer en operation
//Il faut donc mettre cette instruction a la toute fin de la fonction Setup pour eviter que le service soit en operation
//avant la fin de l'initialisation du programme.

//HISTORIQUE:
//2021-04-16, Yves Roy, creation
//2021-11-02, Yves Roy, description plus detaillee

//DEFINITIONS REQUISES PAR LE MODULE:
// ==== Uncomment desired compile options =================================
// #define _TASK_SLEEP_ON_IDLE_RUN  // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
// #define _TASK_TIMECRITICAL       // Enable monitoring scheduling overruns
// #define _TASK_STATUS_REQUEST     // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only
// #define _TASK_WDT_IDS            // Compile with support for wdt control points and task ids
// #define _TASK_LTS_POINTER        // Compile with support for local task storage pointer
// #define _TASK_PRIORITY           // Support for layered scheduling priority
#define _TASK_MICRO_RES          // Support for microsecond resolution
//#define _TASK_STD_FUNCTION       // Support for std::function (ESP8266 and ESP32 ONLY)
// #define _TASK_DEBUG              // Make all methods and variables public for debug purposes
// #define _TASK_INLINE             // Make all methods "inline" - needed to support some multi-tab, multi-file implementations
// #define _TASK_TIMEOUT            // Support for overall task timeout
// #define _TASK_OO_CALLBACKS       // Support for dynamic callback method binding
// #define _TASK_DEFINE_MILLIS      // Force forward declaration of millis() and micros() "C" style
// #define _TASK_EXPOSE_CHAIN       // Methods to access tasks in the task chain
// #define _TASK_SCHEDULING_OPTIONS // Support for multiple scheduling options
#include <TaskScheduler.h>  ////https://www.arduino.cc/reference/en/libraries/taskscheduler/

//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICETASKSERVER_PERIODE_EN_US 4000

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteTaskServer_initialise(void);
void piloteTaskServer_DemarreLesTachesALaTouteFinDeSetup(void);

//Variables publiques:
extern Scheduler piloteTaskServer_gestion;
extern Task piloteTaskServer_tache;//attention: la definition doit etre precedee de celle du Scheduler pour que ca fonctionne
extern void (*piloteTaskServer_execute)(void);

#endif