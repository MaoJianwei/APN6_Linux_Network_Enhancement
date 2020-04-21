//#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include <string.h>
#include <malloc.h>

void main(void) {

	int listenSocket = socket(AF_INET6, SOCK_STREAM, 0);

	struct sockaddr_in6 * listenAddr = (struct sockaddr_in6 *) calloc(1, sizeof(struct sockaddr_in6));

	listenAddr->sin6_family = AF_INET6;
	listenAddr->sin6_port = htons(5511);
	memset(listenAddr->sin6_addr.s6_addr, 0, 16);
	//listenAddr->sin6_addr.s6_addr = in6addr_any;

	int bindRet = bind(listenSocket, (struct sockaddr*) listenAddr, sizeof(struct sockaddr_in6));

	printf("start listen\n");

	int listenRet = listen(listenSocket, 0);

	int count = 0;
	while (1) {
		printf("start accept\n");

		int acceptSocket = accept(listenSocket, NULL, NULL);


		unsigned char hbh[] = {
				0x00, 0x01, 0x03, 0x0c,
				0xaa, 0xaa, 0x08, 0x10,
				0x00, 0x00, 0xaa, 0xaa,
				0x00, 0x52, 0x27, 0x03,
		};
		//int rettt = setsockopt(acceptSocket, IPPROTO_IPV6, IPV6_HOPOPTS, hbh, 16);
		//printf("Mao setsockopt %d %d", rettt, errno);


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
