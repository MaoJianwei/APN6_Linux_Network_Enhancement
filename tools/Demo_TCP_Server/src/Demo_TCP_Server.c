//#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include <string.h>
#include <malloc.h>

void main(void) {

	int listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in * listenAddr = (struct sockaddr_in *) calloc(1, sizeof(struct sockaddr_in));

	listenAddr->sin_family = AF_INET;
	listenAddr->sin_port = htons(5511);
	listenAddr->sin_addr.s_addr = htonl(INADDR_ANY);

	int bindRet = bind(listenSocket, (struct sockaddr*) listenAddr, sizeof(struct sockaddr_in));

	printf("start listen\n");

	int listenRet = listen(listenSocket, 0);

	int count = 0;
	while (1) {
		printf("start accept\n");

		int acceptSocket = accept(listenSocket, NULL, NULL);

		struct timeval recvTimeout = {1,0};
		int setRet = setsockopt(acceptSocket,SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(struct timeval));
		//setsockopt(acceptSocket,SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(struct timeval));


		printf("start recv, time out: %d\n", setRet);
		char buf[1024] = { 0 };
		int recvRet = 0;
		while(-1 != recvRet) {
			do {
				recvRet = recv(acceptSocket, buf, 1023, 0);
				printf("recvRet: %d, error: %d buf: %s\n", recvRet, errno, buf);
			} while(-1 == recvRet && 11 == errno);

			if (-1 == recvRet)
				break;

			int sendRet = send(acceptSocket, buf, recvRet, 0);
		}
		printf("recvRet: %d, error: %d, to close acceptSocket\n", recvRet, errno);



		//int err = errno;

		//char * html = "<html><body>Beijing Tower 118.5</body></html>";
		//int sendRet = send(acceptSocket, html, strlen(html), 0);
		////printf("%d\n",++count);

		//err = errno;

		close(acceptSocket);
	}

	close(listenSocket);

	free(listenAddr);
	int aaaaaaa = 0;
	return;

}
