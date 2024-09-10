//interfaceBalance
//Historique: 
//2018-11-12, Yves Roy, creation


#define _GNU_SOURCE
//INCLUSIONS
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "main.h"
#include "interfaceBalance.h"

//Definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
float fConvertion = 28.34952;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
float interfaceBalance_LecturePoids(int fd)
{
    int i = 0;
    int cpt = 0;
    int bytes_read = 0;
    char bufferPoids[6];
    char read_buffer[19];
	float fPoids = 0;

    bytes_read = read(fd, &read_buffer, sizeof(read_buffer)); // Read the data 
	for(i=0; i<bytes_read; i++)	 // printing only the received characters
	{
		if((read_buffer[i] >= '0' && read_buffer[i] <= '9') || read_buffer[i] == '.')
		{
			bufferPoids[cpt] = read_buffer[i];
			cpt++;
		}
	}
	fPoids = atof(bufferPoids);
    return fPoids;
}

float interfaceBalance_ValiderValeur(float fPoids, char cUnitePoids)
{
    if(fPoids < 30 && fPoids > 100)
    {
        fPoids = -1;
    }
    else if(cUnitePoids == 'O')
    {
        fPoids = fPoids/fConvertion;
    }
    return fPoids;
}