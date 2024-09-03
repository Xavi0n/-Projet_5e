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

int main(int argc, char *argv[]) //char **argv)
{
	int fdSocketCAN, i; 
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Receive Demo\r\n");

	/*
	La première étape est de créer un socket. 
	Cette fonction accepte trois paramètres : 
		domaine/famille de protocoles (PF_CAN), 
		type de socket (raw ou datagram) et 
		protocole de socket. 
	la fonction retourne un descripteur de fichier.
	*/
	if ((fdSocketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return -1;
	}
	
	/*
	Ensuite, récupérer l'index de l'interface pour le nom de l'interface (can0, can1, vcan0, etc.) 
	que nous souhaitons utiliser. Envoyer un appel de contrôle d'entrée/sortie et 
	passer une structure ifreq contenant le nom de l'interface 
	*/
	if(argc == 2)
		strcpy(ifr.ifr_name, argv[1]);
	else strcpy(ifr.ifr_name, "vcan0" );

	ioctl(fdSocketCAN, SIOCGIFINDEX, &ifr);
	/* 	Alternativement, zéro comme index d'interface, permet de récupérer les paquets de toutes les interfaces CAN.
	Avec l'index de l'interface, maintenant lier le socket à l'interface CAN
	*/

	/*
	
	*/
	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(fdSocketCAN, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return -1;
	}

	// appel système read(). Cela bloquera jusqu'à ce qu'une trame soit disponible
	nbytes = read(fdSocketCAN, &frame, sizeof(struct can_frame));

 	if (nbytes < 0) {
		perror("Read");
		return -1;
	}

	printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);
	for (i = 0; i < frame.can_dlc; i++)
		printf("%02X ",frame.data[i]);
	printf("\r\n");

	if (close(fdSocketCAN) < 0) {
		perror("Close");
		return -1;
	}

	return 0;
}
