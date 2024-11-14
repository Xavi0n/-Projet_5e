#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main(int argc, char **argv)
{
	int fdSocketCAN;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;
	unsigned char i = 0;
	char ucEnteredChar[10];
	char bFlagEnter = 0x00;

	printf("CAN Sockets Demo\r\n");

	/*
	La première étape est de créer un socket.
	Cette fonction accepte trois paramètres :
		domaine/famille de protocoles (PF_CAN),
		type de socket (raw ou datagram) et
		protocole de socket.
	la fonction retourne un descripteur de fichier.
	*/
	if ((fdSocketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{ // Création du socket CAN, de type RAW
		perror("Socket");
		return -1;
	}

	/*
	Ensuite, récupérer l'index de l'interface pour le nom de l'interface (can0, can1, vcan0, etc.)
	que nous souhaitons utiliser. Envoyer un appel de contrôle d'entrée/sortie et
	passer une structure ifreq contenant le nom de l'interface
	*/
	if (argc == 2) // si un argument est passé au programme, on l'assigne au nom da l'interface CAN à utiliser
		strcpy(ifr.ifr_name, argv[1]);
	else
		strcpy(ifr.ifr_name, "vcan0"); // par défaut l'interface can0

	ioctl(fdSocketCAN, SIOCGIFINDEX, &ifr);
	/*	Alternativement, zéro comme index d'interface, permet de récupérer les paquets de toutes les interfaces CAN.
	Avec l'index de l'interface, maintenant lier le socket à l'interface CAN
	*/

	/*

	*/
	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(fdSocketCAN, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Bind");
		return -1;
	}

	while (1)
	{
		printf("Type the data to transmit now:\r\n");
		i = 0;
		for (i = 0; i <= 7; i++)
		{
			frame.data[i] = 0x20;
		}
		for (i = 0; i <= 9; i++)
		{
			ucEnteredChar[i] = 0x20;
		}

		/*
		Envoyer une trame CAN, initialiser une structure can_frame et la remplir avec des données.
		La structure can_frame de base est définie dans include/linux/can.h
		*/
		frame.can_id = 0x543; // identifiant CAN
		frame.can_dlc = 7;	  // nombre d'octets de données
		// sprintf(frame.data, "616-TGE"); // données

		fgets(ucEnteredChar, 10, stdin);
		if (strlen(ucEnteredChar) > 0)
		{
			memcpy(frame.data, ucEnteredChar, (strlen(ucEnteredChar) - 1));
			frame.can_dlc = strlen(ucEnteredChar) - 1;
			if (write(fdSocketCAN, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
			{
				perror("Write");
				return -1;
			}
		}
	}
	if (close(fdSocketCAN) < 0)
	{
		perror("Close");
		return -1;
	}
	return 0;
}
