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

int fdSocketCAN;            //File descriptor for the CAN socket
struct sockaddr_can addr;	//Structure to store the CAN socket address
struct ifreq ifr;			//Structure to store information about the CAN interface
struct can_frame frame;		//CAN frame for message data
unsigned char i = 0;		//Variable for temporary use
int nbytes;					//Number of bytes either send or received from the CAN interface

int InitCan (int argc, char *argv[])//char **argv
{
	printf("Projet de 5e session, station Poste de Contôle\r\n");	//Displays the start message on a terminal

	if ((fdSocketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)		//Can socket creation. It takes in 3 parameters:
	{																//Domain: PF_CAN, the protocol family for CAN
		perror("Socket");											//Type: SOCK_RAW, allowing the use of raw CAN frames
		return -1;													//Protocol: CAN_RAW, specifying the use of the raw CAN protocol
	}																//If socket creation fails, display the error and return -1

	if (argc == 2)							//Checks if an interface name has been specified a san argument
		strcpy(ifr.ifr_name, argv[1]);		//If so, uses the given name
	else									//Otherwise, uses the interface CAN0 by default
		strcpy(ifr.ifr_name, "can0");

	ioctl(fdSocketCAN, SIOCGIFINDEX, &ifr);		//Retrieves the index of the CAN interface and stores it in ifr.ifindex

	memset(&addr, 0, sizeof(addr));			//addr is reset to 0
	addr.can_family = AF_CAN;				//addr is set up with AF_CAN, which is the address family for CAN
	addr.can_ifindex = ifr.ifr_ifindex;		//addr is set up with the interface index retrieved above

	if (bind(fdSocketCAN, (struct sockaddr *)&addr, sizeof(addr)) < 0)	//If memory binding fails, display the error and return -1
	{																	
		perror("Bind");
		return -1;
	}
}

int CloseCan()
{
	if (close(fdSocketCAN) < 0)
	{
		perror("Close");
		return -1;
	}
	return 0;
}

int InitUART()
{}

int CloseUART()
{}

int ReceiveCAN()
{}

int TransmitCAN()
{}

int ReceiveUART()
{}

int TransmitUART()
{}


/* void vCanTransmit(int argc, char *argv[])//char **argv
{
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

		
		//Envoyer une trame CAN, initialiser une structure can_frame et la remplir avec des données.
		//La structure can_frame de base est définie dans include/linux/can.h
	
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

void vCanReceive(int argc, char *argv[])//char **argv
{
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
} */
