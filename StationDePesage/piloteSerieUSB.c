//piloteSerieUSB
//Historique: 
//2018-11-12, Yves Roy, creation


#define _GNU_SOURCE
//INCLUSIONS
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "main.h"
#include "piloteSerieUSB.h"

//Definitions privees
#define PILOTESERIEUSB_TTY "/dev/ttyACM0"

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
int piloteSerieUSB_fichier;
struct termios piloteSerieUSB_configuration;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
int piloteSerieUSB_initialise(void)
{
  memset(&piloteSerieUSB_configuration,0,sizeof(piloteSerieUSB_configuration));
  piloteSerieUSB_configuration.c_iflag=0;
  piloteSerieUSB_configuration.c_oflag=0;
  piloteSerieUSB_configuration.c_cflag=0; //CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
  piloteSerieUSB_configuration.c_lflag=0;
  piloteSerieUSB_configuration.c_cc[VMIN]= 0; //1;
  piloteSerieUSB_configuration.c_cc[VTIME]=0; //5;

  piloteSerieUSB_fichier=open(PILOTESERIEUSB_TTY, O_RDWR | O_NONBLOCK);
  
  if (piloteSerieUSB_fichier == -1)
  {
    printf("erreur d'ouverture\n");
    return 1;
  }
  
  if(tcgetattr(piloteSerieUSB_fichier, &piloteSerieUSB_configuration) < 0)
  {
    printf("erreur de lecture d'attributs\n");
    return 1;
  }

  //configuration en entree
  piloteSerieUSB_configuration.c_iflag &= ~IGNBRK; //pas de "break" en entrée
  piloteSerieUSB_configuration.c_iflag &= ~BRKINT; //pas d'interruptions en entrée
  piloteSerieUSB_configuration.c_iflag &= ~ICRNL;  //pas de conversion \n en entrée
  piloteSerieUSB_configuration.c_iflag &= ~INLCR;  //pas de conversion \r en entrée
  piloteSerieUSB_configuration.c_iflag &= ~PARMRK; //pas d'erreur de parité en entrée
  piloteSerieUSB_configuration.c_iflag &= ~INPCK;  //pas de vérification de la parité en entrée
  piloteSerieUSB_configuration.c_iflag &= ~ISTRIP; //pas de retrait de la bit de poids fort en entrée
  piloteSerieUSB_configuration.c_iflag &= ~IXON;   //pas de XON/XOFF en entrée

  //configuration en sortie
  piloteSerieUSB_configuration.c_oflag &= ~OCRNL;  //pas de conversion \r en \n en sortie
  piloteSerieUSB_configuration.c_oflag &= ~ONLCR;  //pas de conversion \n en \r en sortie
  piloteSerieUSB_configuration.c_oflag &= ~ONLRET; //pas de conversion \n en ret en sortie
  piloteSerieUSB_configuration.c_oflag &= ~ONOCR;  //pas de suppression de colonne 0 en sortie
  piloteSerieUSB_configuration.c_oflag &= ~OFILL;  //pas de remplissage par des caracteres en sortie
  piloteSerieUSB_configuration.c_oflag &= ~OLCUC;  //pas de conversion des minuscules en majuscules
  piloteSerieUSB_configuration.c_oflag &= ~OPOST;  //pas de traitement local en sortie
  //ONOEOT cause erreur

  //configuration pour les lignes
  piloteSerieUSB_configuration.c_lflag &= ~ECHO;   //pas d'echo
//  piloteSerieUSB_configuration.c_lflag &= ~ECHONL; //pas d'echo pour les changements de ligne
  piloteSerieUSB_configuration.c_lflag |= ECHONL; //echo pour les changements de ligne
  piloteSerieUSB_configuration.c_lflag &= ~IEXTEN; //pas de traitement des entrees "extended"
  piloteSerieUSB_configuration.c_lflag &= ~ISIG ;  //pas de signalisation de caracteres
  piloteSerieUSB_configuration.c_lflag &= ~ECHOE;  //pas d'echo...
//  piloteSerieUSB_configuration.c_lflag |= ICANON;  //mode canonique pour fonctionner par ligne
  piloteSerieUSB_configuration.c_lflag &= ~ICANON;  //mode canonique pour ne pas fonctionner par ligne
  
//configuration materielle
  piloteSerieUSB_configuration.c_cflag &= ~CSIZE; //efface la configuration actuelle du nombre de bits
  piloteSerieUSB_configuration.c_cflag &= ~PARENB; //pas de parite 
  piloteSerieUSB_configuration.c_cflag |= CS8; // 8 bits
  
  piloteSerieUSB_configuration.c_cflag &= ~CRTSCTS;  //pas de traitement local en sortie  
  

  //configuration des lectures si en mode "raw"
  piloteSerieUSB_configuration.c_cc[VMIN]  = 0;  
  piloteSerieUSB_configuration.c_cc[VTIME] = 20;  
//  piloteSerieUSB_configuration.c_cc[VMIN]  = 1;  //au moins un octet a la fois
//  piloteSerieUSB_configuration.c_cc[VTIME] = 0;  //pas de "timeout"  

  if (cfsetispeed(&piloteSerieUSB_configuration, PILOTESERIEUSB_BAUDRATE_AVEC_B_AU_DEBUT) < 0)
  {
    return -1;
  }
  if (cfsetospeed(&piloteSerieUSB_configuration, PILOTESERIEUSB_BAUDRATE_AVEC_B_AU_DEBUT) < 0)
  {
    return -1;
  }

  if(tcsetattr(piloteSerieUSB_fichier, TCSAFLUSH, &piloteSerieUSB_configuration) < 0)  
  
  {
    return -1;
  }
  
  tcflush(piloteSerieUSB_fichier, TCIOFLUSH);
  return 0;
}

int piloteSerieUSB_termine(void)
{
  
  tcflush(piloteSerieUSB_fichier, TCIOFLUSH);   
  close(piloteSerieUSB_fichier);
  return 0;
}



int piloteSerieUSB_ecrit(char *Source, unsigned char NombreATransmettre)
{
  tcflush(piloteSerieUSB_fichier, TCOFLUSH);  
  return (int)write(piloteSerieUSB_fichier,Source, NombreATransmettre);
}

int piloteSerieUSB_attendLaFinDeLEcriture(void)
{
  return (int)tcdrain(piloteSerieUSB_fichier);
}

int piloteSerieUSB_lit(char *Destination, unsigned char NombreMaximalDeLectures)
{
int retour = read(piloteSerieUSB_fichier, Destination, NombreMaximalDeLectures);  
  tcflush(piloteSerieUSB_fichier, TCIFLUSH);  
  return retour;
}