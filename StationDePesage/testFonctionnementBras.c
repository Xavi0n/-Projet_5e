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
    int fd_portUART;
    int retour = 0;
    char TestCondition[] = "G2202 F1000\n";
    char Move[] = "G0 X340 Y0 Z0 F5000\n";
    char Move2[] ="G0 X100 Y100 Z100 F2000\n";
    char Buzzer[] = "M2210 F1000 T2000\n";
    char PumpOn[] = "M2231 V1\n";
    char PumpOff[] = "M2231 V0\n";
    char Delay1000ms[] = "G2004 P1000\n";
    unsigned char NombreATransmettre;

    // Ouverture du port série 
    fd_portUART = open(portTTY, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd_portUART == -1)
    {
        perror("Erreur! Ouverture de port");
        return EXIT_FAILURE;
    }
    configure_serial(fd_portUART);

    //Source = "G0 X100 Y100 Z100 F1000\n";
    NombreATransmettre = 24;

    tcflush(fd_portUART, TCOFLUSH);  
    //retour = (int)write(fd_portUART, TestCondition, sizeof(TestCondition));
    sleep(1);
    //retour =write(fd_portUART, PumpOn, sizeof(PumpOn));
    sleep(1);
    tcflush(fd_portUART, TCOFLUSH);  
    sleep(1);
    retour =write(fd_portUART, Move, sizeof(Move));
    sleep(1);
    tcflush(fd_portUART, TCOFLUSH);  
    sleep(1);
    retour =write(fd_portUART, Move2, sizeof(Move2));
    //retour = (int)tcdrain(fd_portUART);
    sleep(1);
    tcflush(fd_portUART, TCIOFLUSH);   
    sleep(1);
    close(fd_portUART);
    
    printf("retour = %i\n", retour);

}