/*
 *    Description:  Check that ioctl can not send more than 2^14B (16384).
 *    		    Demonstrate that size limit detailed from
 *    		    https://lwn.net/Articles/48354/ is not valid anymore.
 *        Created:  09/10/2018
 *         Author:  Yohan Pipereau
*/


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FNAME "/dev/ioc"
#define MSGSIZE 200000// > 2^14
#define TEST_NUM 0x04 //unique magic number to generate IOC sequence number
#define IOC_TEST _IOWR('f', TEST_NUM, struct big_data)

struct big_data {
	char 	msg[MSGSIZE];
};

int main ( int argc, char *argv[] )
{
	struct big_data *msgw;
	int rc, fd;

	printf("Allocating %lu bytes\n", sizeof(struct big_data));

	msgw = malloc(sizeof(struct big_data));
	if (!msgw)
		return -ENOMEM;

	memset(&msgw->msg, 'B', MSGSIZE*sizeof(char));

	fd = open(FNAME, O_RDWR);
	if (fd < 0) {
		perror("failed opening");
		return errno;
	}

	rc = ioctl(fd, IOC_TEST, msgw);
	if (rc < 0) {
		perror("failed ioctl");
		return errno;
	}

	free(msgw);

	close(fd);

	return EXIT_SUCCESS;
}


