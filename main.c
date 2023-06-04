#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> 
#include <netdb.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <poll.h>
#include <ixp.h>

#include "hashmap.h"
#include "dat.h"
#include "fns.h"

#define PORT 8080

int main()
{
	// Remove all of this server-client stuff for now. Without a bare minimum
	// client the server is worthless.
	
	/*
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		fprintf(stderr, "failed to create socket");
		exit(-1);
	}
	fprintf(stderr, "made socket\n");

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
		fprintf(stderr, "failed to connect to server");
		exit(-1)
	}
	fprintf(stderr, "connected to server\n");

	*/


	flt_resources resources = init_services();
	flt_proc proc = create_proc();

	flt_procs procs = { .procs=&proc, .count=1 };

	run_middleman(resources, procs);


	/*
	char buf[100] = "hellooooo";

	write(sockfd, buf, strlen(buf)+1);

	

	fprintf(stderr, "message sent\n");

	int n = read(sockfd, buf, sizeof(buf));
	fprintf(stderr, "message recieved:\n");
	for (int i=0;i<n;i++)
		fprintf(stderr, "%c", buf[i]);
	fprintf(stderr, "\n");

	fprintf(stderr, "closing socket\n");

	close(sockfd);
	*/
	return 0;
}