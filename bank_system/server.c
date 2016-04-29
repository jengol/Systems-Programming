

#include "server.h"


//Maximum number of accounts: 20
static Account Bank[20];

void printStatus(){
	int i;
	int isEmpty = 1;
	for (i = 0; i < 20; ++i) {
		if(Bank[i]){
			isEmpty = 0;
			printf("Account: %s, Balance: %.2f%s",
					Bank[i]->name,Bank[i]->balance,(Bank[i]->inSession == 1) ? ", IN SERVICE" : ""
			);
		}
	}
	if(isEmpty){
		printf("NO ACCOUNTS\n");
	}
	return;
}

/*
 * SERVER
 * 1. Takes no command line arguments; Port is hard-coded
 * 2. Listens for requests
 * 3. Prints account information every 20 seconds.
 */

int main(int argc, char **argv) {

	printf("Hello\n");
	Account temp = (Account)malloc(sizeof(Account));
	temp->balance = 10000;
	temp->inSession = 1;
	temp->index = 1;
	temp->name = "I'm balling";

	printStatus();
	Bank[0] = temp;
	printStatus();

//	int socketfd = -1;
//	int clientfd = -1;
//	int clientLen = -1;
//
//
//	//	char clientBuffer[256];
//
//	struct sockaddr_in serverAddressInfo;
//	struct sockaddr_in clientAddressInfo;
//
//	socketfd = socket(AF_INET, SOCK_STREAM, 0);
//	if (socketfd < 0)
//	{
//		perror("ERROR opening socket");
//	}
//
//	/* Initialize sockaddr_in */
//
//	// set sockaddr_in to zero
//	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));
//	// Set remote port
//	serverAddressInfo.sin_port = htons(PORT);
//	// Set network address type
//	serverAddressInfo.sin_family = AF_INET;
//	// Set incoming connections type
//	serverAddressInfo.sin_addr.s_addr = INADDR_ANY;
//
//
//	// Bind the server socket to the local port
//	if (bind(socketfd, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo)) < 0)
//	{
//		perror("ERROR on binding");
//	}
//
//	// Listen for client connections
//	listen(socketfd,5);
//
//	// determine the size of a clientAddressInfo struct
//	clientLen = sizeof(clientAddressInfo);
//
//	clientfd = accept(socketfd, (struct sockaddr *) &clientAddressInfo, (socklen_t*)&clientLen);
//
//
//	if (clientfd < 0)
//	{
//		perror("ERROR on accept");
//	}
//
//	printf("%s\n","We made it");
	return 0;
}
