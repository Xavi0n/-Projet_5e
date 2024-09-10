#include <stdio.h>
#include <fcntl.h>   // File Control Definitions
#include <termios.h> // POSIX Terminal Control Definitions
#include <unistd.h>  // UNIX Standard Definitions
#include <errno.h>   
#include <sys/types.h> // Pour pid_t
#include <sys/wait.h> // Pour wait()
#include <stdlib.h>   // Pour exit()

// Device port série à utiliser 
const char *portTTY = "/dev/ttyUSB0"; 

void configure_serial(int fd) 
{
    struct termios SerialPortSettings; // Create the structure 
    tcgetattr(fd, &SerialPortSettings); // Get the current attributes of the Serial port

    // Setting the Baud rate
    cfsetispeed(&SerialPortSettings, B9600); // Set Read Speed   
    cfsetospeed(&SerialPortSettings, B9600); // Set Write Speed  
 
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

/*void write_to_serial(int fd, int write_pipe)
 {
    char write_buffer[] = "ABCDE12345"; // Buffer containing characters to write into port
    int bytes_written = write(fd, write_buffer, sizeof(write_buffer)); // Write data to serial port 

    printf("\nEcriture de %d octets : %s ecrit sur le port %s\n", bytes_written, write_buffer, portTTY);
    
    // Communicate with the other process through the pipe
    write(write_pipe, write_buffer, bytes_written);

    close(fd); // Close the Serial port
}
*/

void read_from_serial(int fd, int read_pipe)
 {
    //tcflush(fd, TCIFLUSH);  // Discards old data in the rx buffer
    char read_buffer[19];   // Buffer to store the data received 
    int bytes_read = 0;
    int cpt = 0;
    int i = 0;
	char bufferGrammes[6];
	float fGrammes = 0;
	float fOnces = 0;
	float fConvertion = 28.34952;
    
    bytes_read = read(fd, &read_buffer, sizeof(read_buffer)); // Read the data 
   // printf(" Bytes Recus : %d --> ", bytes_read); // Print the number of bytes read
	for(i=0; i<bytes_read; i++)	 // printing only the received characters
	{
		if((read_buffer[i] >= '0' && read_buffer[i] <= '9') || read_buffer[i] == '.')
		{
			//printf("%c", read_buffer[i]);
			bufferGrammes[cpt] = read_buffer[i];
			cpt++;
		}
	}
	fGrammes = atof(bufferGrammes);
	fOnces = (fGrammes/fConvertion);
	//printf(" g ou %f oz\n",fOnces);
    if(fGrammes > 30 && fGrammes < 100)
        printf("%2.2f g ou %2.2f oz\n",fGrammes, fOnces);

   // close(fd); // Close the serial port
}

int main(void) 
{
    int fd_portUART;
    //int pipe_write[2]; // "Pipe" pour l'écriture
    int pipe_read[2];  // "Pipe" pour la lecture

    // Création des pipes
    if (/*pipe(pipe_write) == -1 || */pipe(pipe_read) == -1) 
    {
        perror("Erreur lors de la création des pipes");
        return EXIT_FAILURE;
    }

    // Ouverture du port série 
    fd_portUART = open(portTTY, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd_portUART == -1)
    {
        perror("Erreur! Ouverture de port");
        return EXIT_FAILURE;
    }
    
    configure_serial(fd_portUART);
    while (1)
    {
        /*pid_t pid_write = fork();
    if (pid_write < 0)
    {
        perror("Fork for writing failed");
        return EXIT_FAILURE;
    }*/

        /*if (pid_write == 0)
    {
        // Child process for writing
        write_to_serial(fd_portUART, pipe_write[1]);
        exit(EXIT_SUCCESS);
    }*/

        pid_t pid_read = fork();
        if (pid_read < 0)
        {
            perror("Fork for reading failed");
            return EXIT_FAILURE;
        }

        if (pid_read == 0) 
        {
            //Child process for reading
            //fd_portUART = open(portTTY, O_RDWR | O_NOCTTY | O_NDELAY);
            if (fd_portUART == -1)
            {
                perror("Erreur! ouverture de port pour lecture");
                exit(EXIT_FAILURE);
            }
            configure_serial(fd_portUART);
            read_from_serial(fd_portUART, pipe_read[0]);
            exit(EXIT_SUCCESS);
        }

        // Main process
        int n = 1; 
        while (n < 5)
         {
           //printf("%u faire quelques trucs...\n",n);
           n++;
           sleep(1);
        }
        printf(" attendre la fin de l'enfant 1 \n");
        wait(NULL); // attendre la fin de l'enfant 1
        /* printf(" attendre la fin de l'enfant 2 \n");
        wait(NULL); // attendre la fin de l'enfant 2*/
        printf("enfant fini\n");

        //close(fd_portUART); // Fermer le port série 
        /*close(pipe_write[0]); // Close unused read end of pipe_write
        close(pipe_write[1]); // Close unused write end of pipe_write*/
        close(pipe_read[0]);  // Close unused read end of pipe_read
        close(pipe_read[1]);  // Close unused write end of pipe_read    
    }
        printf("Fin du processus Principal\n");

        return EXIT_SUCCESS;
    
}