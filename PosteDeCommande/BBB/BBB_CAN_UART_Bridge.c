#define _DEFAULT_SOURCE

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <fcntl.h>
#include <termios.h>

#define UART_PORT "/dev/ttyS1" // Define UART port (e.g., /dev/ttyS1 for UART1)
#define BAUD_RATE B19200	   // Set baud rate to 19200

#define CAN_BUFFER_SIZE 8
#define UART_BUFFER_SIZE 10

int fdSocketCAN;				// File descriptor for the CAN socket
struct sockaddr_can addr;		// Structure to store the CAN socket address
struct ifreq ifr;				// Structure to store information about the CAN interface
struct can_frame frame;			// CAN frame for message data
unsigned char UARTFrameIn[10];	// Frame for data incoming from PC app
unsigned char UARTFrameOut[10]; // Frame for data going to PC app
unsigned char i = 0;			// Variable for temporary use
int nbytes;						// Number of bytes either sent or received from the CAN interface
unsigned char ucCheckSum = 0; 	// Temporary variable to be used to calculate checksum


int uart_fd = -1; // File descriptor for UART communication

/////////////////////////////////
// MAIN
/////////////////////////////////
void main(void)
{
}

/////////////////////////////////
// Fonctions appelees dans MAIN
/////////////////////////////////
int InitCan(int argc, char *argv[]) // char **argv
{
	printf("Projet de 5e session, station Poste de Contôle\r\n"); // Displays the start message on a terminal

	if ((fdSocketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) // Can socket creation. It takes in 3 parameters:
	{														   // Domain: PF_CAN, the protocol family for CAN
		perror("Socket");									   // Type: SOCK_RAW, allowing the use of raw CAN frames
		return -1;											   // Protocol: CAN_RAW, specifying the use of the raw CAN protocol
	} // If socket creation fails, display the error and return -1

	if (argc == 2)					   // Checks if an interface name has been specified a san argument
		strcpy(ifr.ifr_name, argv[1]); // If so, uses the given name
	else							   // Otherwise, uses the interface CAN0 by default
		strcpy(ifr.ifr_name, "can0");

	ioctl(fdSocketCAN, SIOCGIFINDEX, &ifr); // Retrieves the index of the CAN interface and stores it in ifr.ifindex

	memset(&addr, 0, sizeof(addr));		// addr is reset to 0
	addr.can_family = AF_CAN;			// addr is set up with AF_CAN, which is the address family for CAN
	addr.can_ifindex = ifr.ifr_ifindex; // addr is set up with the interface index retrieved above

	if (bind(fdSocketCAN, (struct sockaddr *)&addr, sizeof(addr)) < 0) // If memory binding fails, display the error and return -1
	{
		perror("Bind");
		return -1;
	}
	return 0;
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
{
	struct termios options; // Structure to store the terminal (UART) configuration settings

	uart_fd = open(UART_PORT, O_RDWR | O_NOCTTY | O_NDELAY); // Opens UART port
	if (uart_fd == -1)
	{								   // If opening UART port failed, return -1
		perror("Failed to open UART"); // and display  error message
		return -1;
	}

	tcgetattr(uart_fd, &options); // Get current UART settings

	cfsetispeed(&options, BAUD_RATE); // Set baud rate to 19200 for UART input speed
	cfsetospeed(&options, BAUD_RATE); // Set baud rate to 19200 for UART output speed

	// Set data bits (8 bits), no parity, 1 stop bit
	options.c_cflag = (options.c_cflag & ~CSIZE) | CS8;
	options.c_cflag &= ~PARENB;			   // No parity
	options.c_cflag &= ~CSTOPB;			   // 1 stop bit
	options.c_cflag &= ~CRTSCTS;		   // No hardware flow control
	options.c_cflag |= CREAD | CLOCAL;	   // Enable receiver, local mode
	tcsetattr(uart_fd, TCSANOW, &options); // Applies previously declared settings to the UART port

	// Do not close the UART here, leave it open for further communication
	printf("UART initialized successfully\n");

	return 0; // Success
}

int CloseUART()
{
	if (uart_fd != -1)
	{
		if (close(uart_fd) < 0)
		{
			perror("Failed to close UART");
			return -1;
		}
		uart_fd = -1; // Reset UART file descriptor
		printf("UART closed successfully\n");
	}
	return 0;
}

int ReceiveCAN()
{
	nbytes = read(fdSocketCAN, &frame, sizeof(struct can_frame)); // Blocks and scans the CAN bus. When data is received,
																  // store it in the CAN frame's data
	if (nbytes < 0)
	{
		perror("Read"); // If received data is negative amount of bytes
		return -1;		// Return wit hvalue -1 and displays reading error
	}
	for (i = 0; i < CAN_BUFFER_SIZE; i++)		 //
	{											 //
		ucCheckSum = ucCheckSum + frame.data[i]; // Calcul du CheckSum
	} //

	if (ucCheckSum == frame.data[CAN_BUFFER_SIZE]) // Vérifie si le checksum calcule est egal a celui envoyé
	{
		for (i = 0; i < CAN_BUFFER_SIZE; i++)	   //
		{										   //
			UARTFrameOut[(i + 2)] = frame.data[i]; // Copie de la trame recue dans un tableau
			printf("%02X", UARTFrameOut[i]);	   // Printf des valeurs pour dégogage
		} //
		printf("\n"); //
	}
}

int TransmitCAN()
{
	i = 0;
	for (i = 0; i < CAN_BUFFER_SIZE; i++) // Reset frame data
	{
		frame.data[i] = 0x00;
	}
	frame.can_id = 0x100;			 // identifiant CAN du poste de controle
	frame.can_dlc = CAN_BUFFER_SIZE; // nombre d'octets de données

	memcpy(frame.data, (UARTFrameIn + 2), CAN_BUFFER_SIZE); // Copy UART received data to CAN frame

	printf("Sending CAN frame:\n");									   // Outputs what has been sent
	printf("ID: 0x%03X, DLC: %d, Data:", frame.can_id, frame.can_dlc); // to VsCode's debug window
	for (i = 0; i < frame.can_dlc; i++)								   //
	{																   //
		printf(" 0x%02X", frame.data[i]);							   //
	} //
	printf("\n"); // Skips a line

	if (write(fdSocketCAN, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) // Write data in fdSocketCan to the CAN bus
	{
		perror("Write"); // Error management
		return -1;		 // If error, return with error code -1
	}
}

void ReceiveUART(int signo)
{
    int bytes_available = 0;

    // Check how many bytes are available in the UART receive buffer
    if (ioctl(uart_fd, FIONREAD, &bytes_available) < 0)
    {
        perror("Failed to check bytes available");
        return;
    }

    // If exactly 10 bytes are available, read them into UARTFrameIn
    if (bytes_available >= UART_BUFFER_SIZE)
    {
        int bytes_read = read(uart_fd, UARTFrameIn, UART_BUFFER_SIZE);

        if (bytes_read == UART_BUFFER_SIZE)
        {
            printf("10 bytes received from UART: ");
            for (i = 0; i < UART_BUFFER_SIZE; i++)
            {
                printf("0x%02X ", UARTFrameIn[i]);
            }
            printf("\n");

            // Verify checksum
            for (i = 2; i < UART_BUFFER_SIZE - 1; i++) // Sum bytes 2 to 8
            {
                ucCheckSum += UARTFrameIn[i];
            }

            if (ucCheckSum == UARTFrameIn[UART_BUFFER_SIZE - 1]) // Compare with last byte (checksum byte)
            {
                printf("Checksum verified successfully!\n");

                // Process the valid frame (copy to UARTFrameOut, send to CAN, etc.)
                memcpy(UARTFrameOut, UARTFrameIn, UART_BUFFER_SIZE); // Example of copying valid data
            }
            else
            {
                printf("Checksum mismatch! Calculated: 0x%02X, Received: 0x%02X\n",
                       ucCheckSum, UARTFrameIn[UART_BUFFER_SIZE - 1]);
            }
        }
        else
        {
            printf("Error reading data: expected %d bytes, got %d bytes\n", UART_BUFFER_SIZE, bytes_read);
        }

        // Clear any extra bytes in the buffer
        if (bytes_available > UART_BUFFER_SIZE)
        {
            char temp[256];
            read(uart_fd, temp, bytes_available - UART_BUFFER_SIZE);
        }
    }
    else
    {
        printf("Not enough data yet: %d bytes available\n", bytes_available);
    }
}

int enable_uart_interrupt(int uart_fd)
{
	// Set up the signal handler
	struct sigaction saio;
	saio.sa_handler = ReceiveUART;
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;
	if (sigaction(SIGIO, &saio, NULL) < 0)
	{
		perror("Failed to set SIGIO handler");
		return -1;
	}
	// Allow the process to receive SIGIO
	if (fcntl(uart_fd, F_SETOWN, getpid()) < 0)
	{
		perror("Failed to set process owner for SIGIO");
		return -1;
	}
	// Enable asynchronous notifications
	if (fcntl(uart_fd, F_SETFL, FASYNC) < 0)
	{
		perror("Failed to enable FASYNC");
		return -1;
	}
	return 0; // Success
}

int TransmitUART()
{
	UARTFrameOut[0] = 0x24;													// Start Condition de la trame UART ('$' en hexadecimal)
	UARTFrameOut[1] = 0x08;													// Nombre d'octets de data a transmettre (exclus: '$', nb d'octets à transmettre et checksum)
	ssize_t bytes_written = write(uart_fd, UARTFrameOut, UART_BUFFER_SIZE); // Writes data to UART port

	printf("Sending CAN frame:\n");									   // Outputs what has been sent
	printf("ID: 0x%03X, DLC: %d, Data:", frame.can_id, frame.can_dlc); // to VsCode's debug window
	for (i = 0; i < frame.can_dlc; i++)								   //
	{																   //
		printf(" 0x%02X", frame.data[i]);							   //
	} //
	printf("\n");

	for (i = 0; i < UART_BUFFER_SIZE; i++) // Reset value for UARTFrameOut
	{
		UARTFrameOut[i] = 0x00;
	}
}
