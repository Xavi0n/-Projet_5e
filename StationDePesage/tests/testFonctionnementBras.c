#define _GNU_SOURCE
//INCLUSIONS
#include <stdio.h>
#include <fcntl.h>   // File Control Definitions
#include <termios.h> // POSIX Terminal Control Definitions
#include <unistd.h>  // UNIX Standard Definitions
#include <errno.h>   
#include <sys/types.h> // Pour pid_t
#include <sys/wait.h> // Pour wait()
#include <stdlib.h>   // Pour exit()

const char *portTTY = "/dev/ttyACM0"; 
int fd_portUART;
int retour = 0;
    char TestCondition[] = "G2202 F1000\n";
    char Move[] = "#10 G0 X340 Y0 Z0 F8000\n";
    char Move2[] ="#11 G0 X300 Y70 Z70 F5000\n";
    char Buzzer[] = "#12 M2210 F1000 T2000\n";
    char PumpOn[] = "#13 M2231 V1\n";
    char PumpOff[] = "#14 M2231 V0\n";
    char ObtenirPosition[] = "#15 P2220\n";
    char ObtenirPosition2[] = "#16 P2220\n";
    char cLecture[25];
    char cLecture2[25];

void PumpActif(void);
void PumpInactif(void);
void Move1(void);
void Move3(void);

void configure_serial(int fd) 
{
    struct termios SerialPortSettings; // Create the structure 
    tcgetattr(fd, &SerialPortSettings); // Get the current attributes of the Serial port

    // Setting the Baud rate
    cfsetispeed(&SerialPortSettings, B115200); // Set Read Speed   
    cfsetospeed(&SerialPortSettings, B115200); // Set Write Speed  
 
    //8N1
    SerialPortSettings.c_cflag &= ~PARENB; // No Parity
    SerialPortSettings.c_cflag &= ~CSTOPB; // 1 Stop bit
    SerialPortSettings.c_cflag &= ~CSIZE;  // Clears the mask for setting the data size
    SerialPortSettings.c_cflag |= CS8;      // Set the data bits = 8
    SerialPortSettings.c_cflag &= ~CRTSCTS; // No Hardware flow Control
    SerialPortSettings.c_cflag |= CREAD | CLOCAL; // Enable receiver, Ignore Modem Control lines

    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable XON/XOFF flow control

    SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //  Non Cannonical mode, Disable echo, Disable signal  
    SerialPortSettings.c_oflag &= ~OPOST; // No Output Processing

    // Setting Time outs 
    SerialPortSettings.c_cc[VMIN] = 19; // Read at least 0 character(s) 
    SerialPortSettings.c_cc[VTIME] = 0; // Wait 10 sec (0 for indefinitely) 

    // Set the attributes to the termios structure
    if (tcsetattr(fd, TCSANOW, &SerialPortSettings) != 0) 
    {
        perror("Erreur! configuration des attributs du port serie");
        exit(EXIT_FAILURE);
    }
}

int main(void) 
{
    

    // Ouverture du port série 
    fd_portUART = open(portTTY, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd_portUART == -1)
    {
        perror("Erreur! Ouverture de port");
        return EXIT_FAILURE;
    }
    configure_serial(fd_portUART);

    Move1();

    PumpActif();

    Move3();

    PumpInactif();

    close(fd_portUART);
    
    printf("retour = %i\n", retour);

}

void Move1(void)
{
    tcflush(fd_portUART, TCOFLUSH);  
    sleep(1);
    retour =write(fd_portUART, Move, (sizeof(Move)-1));
    sleep(10);

    read(fd_portUART, cLecture, 29);  
    printf("\nLecture 1 :\n");
    printf(cLecture);
    printf("\n..\n");
    tcflush(fd_portUART, TCIFLUSH);         

    tcflush(fd_portUART, TCOFLUSH);  
    write(fd_portUART, ObtenirPosition, (sizeof(ObtenirPosition)-1));

    while(cLecture[0] != '$' && cLecture[1] != '1' && cLecture[2] != '5')
    {
        
        read(fd_portUART, cLecture, (sizeof(cLecture)-1));  
       // printf(".");
    }
    printf("\nLecture 1 :\n");
    printf(cLecture);
    printf("\n..\n");
    tcflush(fd_portUART, TCIFLUSH);  
}

void Move3(void)
{
        sleep(5);
    tcflush(fd_portUART, TCOFLUSH);  
    sleep(1);
    retour =write(fd_portUART, Move2, (sizeof(Move2)-1));
    sleep(15);  
 
    write(fd_portUART, ObtenirPosition2, (sizeof(ObtenirPosition2)-1));
    sleep(5);
   /* while(cLecture[0] != '$' && cLecture[1] != '1' && cLecture[2] != '1')
    {*/
        read(fd_portUART, cLecture2, (sizeof(cLecture2)-1));  
        /*printf(".");
    }*/
    printf("\nLecture 2 :\n");
    printf(cLecture2);
    printf("\n..\n");
    tcflush(fd_portUART, TCIFLUSH);  
    sleep(1);
}

void PumpActif(void)
{
    sleep(5);
    tcflush(fd_portUART, TCOFLUSH);  
    sleep(1);
    retour =write(fd_portUART, PumpOn, (sizeof(PumpOn)-1));
    sleep(15);  
    tcflush(fd_portUART, TCIFLUSH);  
    sleep(1);
}

void PumpInactif(void)
{
    sleep(5);
    tcflush(fd_portUART, TCOFLUSH);  
    sleep(1);
    retour =write(fd_portUART, PumpOff, (sizeof(PumpOff)-1));
    sleep(15);  
    tcflush(fd_portUART, TCIFLUSH);  
    sleep(1);
}