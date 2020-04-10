#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> /*struct sockaddr_in*/
#include <arpa/inet.h>  /*inet_pton */
#include <error.h>
#include <errno.h>

#include <unistd.h>
#include <malloc.h>

void main(void){

	struct sockaddr_in6 * peerSockaddr = (struct sockaddr_in6 *)calloc(1, sizeof(struct sockaddr_in6));
	peerSockaddr->sin6_family = AF_INET6;
	peerSockaddr->sin6_port = htons(5511);

	int ptonRet = inet_pton(AF_INET6, "2001:da8:215:A::BBBB", &(peerSockaddr->sin6_addr.s6_addr));
	//char buf[30] = {0};
	//char * ntopRet = inet_ntop(AF_INET, &(peerSockaddr->sin_addr), buf, 29);


	int connectSocket = socket(AF_INET6, SOCK_STREAM, 0);
	int connectRet = connect(connectSocket, (struct sockaddr*)peerSockaddr, sizeof(struct sockaddr_in6));

	unsigned char hbh[] = {
			0x00, 0x01, 0x03, 0x0c,
			0xaa, 0xaa, 0x08, 0x10,
			0x00, 0x00, 0xaa, 0xaa,
			0x00, 0x52, 0x27, 0x03,
	};
	int rettt = setsockopt(connectSocket, IPPROTO_IPV6, IPV6_HOPOPTS, hbh, 16);
	printf("Mao setsockopt %d %d", rettt, errno);

	char * html = "..........contact Beijing Tower on 118.5, good day!";
	while(0 == errno) {
		int sendRet = send(connectSocket, html, strlen(html), 0);
		printf("send html %d\n", sendRet);
		sleep(1);
	}
	printf("exit errno %d\n", errno);

	close(connectSocket);

	free(peerSockaddr);
}
