
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
	int fdSocketCAN, i;
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Receive Filter Demo\r\n");

	if ((fdSocketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{
		perror("Socket");
		return -1;
	}

	if (argc == 2)
		strcpy(ifr.ifr_name, argv[1]);
	else
		strcpy(ifr.ifr_name, "vcan0");

	ioctl(fdSocketCAN, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(fdSocketCAN, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Bind");
		return -1;
	}

	/// A filter matches, when <received_can_id> & mask == can_id & mask
	struct can_filter rfilter[3]; // filtres pour 3 ID

	rfilter[0].can_id = 0x007;
	rfilter[0].can_mask = 0xFFF;
	rfilter[1].can_id = 0x010;
	rfilter[1].can_mask = 0xFFF;
	rfilter[2].can_id = 0x680;
	rfilter[2].can_mask = 0xFFF;

	while (1)
	{
		setsockopt(fdSocketCAN, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

		nbytes = read(fdSocketCAN, &frame, sizeof(struct can_frame));

		if (nbytes < 0)
		{
			perror("Read");
			return -1;
		}

		printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);

		for (i = 0; i < frame.can_dlc; i++)
			printf("%02X ", frame.data[i]);

		printf("\r\n");
	}
	if (close(fdSocketCAN) < 0)
	{
		perror("Close");
		return -1;
	}

	return 0;
}
