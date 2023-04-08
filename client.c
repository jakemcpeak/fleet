#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> 
#include <netdb.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <ixp.h>

#include "dat.h"
#include "fns.h"
#include "config.h"

#define PORT 8080

void srvCons(int sock) {
	// one way for now
	while(true) {
		char buf[100];

		read(sock, buf, 1);
		printf("%c", buf[0]);
	}
}
		

fltRunSrv init_service(fltService srvc) {
	fltRunSrv ret;
	char *name = srvc.name;

	ret.name = malloc(strlen(name)+1);
	strcpy(ret.name, name);
	
	int sock[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, sock);
	ret.sock = sock[0];

	if (ret.pid = fork()) {
		return ret;
	}
	srvc.func(sock[1]);
	exit(0);
}

int init_services() {
	int sock[2];
	int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sock);

	int nsrv = sizeof(services) / sizeof(services[0]);
	fltRunSrv *servers = malloc(sizeof(fltRunSrv) * nsrv);

	for (int i=0;i<nsrv;i++) {
		servers[i] = init_service(services[i]);
	}

	return servers[0].sock;



	while (true) {
		char buf[100];
		int n = read(sock[1], buf, 1);
		printf("%c", buf[0]);
	}
}

int create_proc() {
	int sock[2];
	int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sock);
	if (!fork()) {
		return sock[0];
	}
	// this is the child process. Right now it'll just read keyboard and write
	// to a pipe, which writes to the screen. 
	while (true) {
		char c = getchar();
		write(sock[1], &c, 1);
	}
}

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
		exit(-1);
	}
	fprintf(stderr, "connected to server\n");

	*/

	int procsock = create_proc();
	int servsock = init_services();

	printf("in here\n");
	while (true) {
		char buf[100];
		int n = read(procsock, buf, 1);
		write(servsock, buf, 1);
	}

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
