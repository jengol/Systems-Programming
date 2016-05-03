#include "client.h"



int main(int argc, char *argv[])
{
	int socketfd = -1;
	//	int n = -1;
	//	char buffer[256];
	struct sockaddr_in serverAddressInfo;
	struct hostent *serverIPAddress;

	if (argc < 2)
	{
		printf("ERROR: no IPAddress input\n");
		exit(1);
	}
	// Convert IPAddress into hostent struct
	serverIPAddress = gethostbyname(argv[1]);
	if (serverIPAddress == NULL)
	{
		printf("ERROR: no such host\n");
		exit(0);
	}

	//Create socket
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
	{
		perror("ERROR creating socket");
	}

	//Set serverAddressInfo to zero
	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	serverAddressInfo.sin_family = AF_INET;
	serverAddressInfo.sin_port = htons(PORT);

	// do a raw copy of the bytes that represent the server's IP address in
	//   the 'serverIPAddress' struct into our serverIPAddressInfo struct
	bcopy((char *)serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);



	/** We now have a blank socket and a fully parameterized address info struct .. time to connect **/

	//Attempt to connect to the server every 3 seconds
	while(connect(socketfd,(struct sockaddr *)&serverAddressInfo,sizeof(serverAddressInfo)) < 0){
		perror("Attempting to connect to server");
		sleep(3);
	}

	printf("Connected to server: %s\n",argv[1]);
	/* Data read in from stdin */
	char buffer[110];
	/* User command */
	char choice;
	/* Condition to 'quit' program */
	int exitStatus = 0;

	while(1){

		printf("Please enter a command:\n");
		printf("Open account (max 100 letters)\n");
		printf("Start account\n");
		printf("Credit\n");
		printf("Debit\n");
		printf("Balance\n");
		printf("Finish\n");
		printf("Exit\n");
		printf("\n");


		fgets(buffer,110,stdin);

		//Read in choice
		write(socketfd,buffer,strlen(buffer));
		if(strcmp("Exit",buffer)==0){
			exitStatus = 1;
		}
		bzero(buffer,110);
		read(socketfd,buffer,110);
		/* Server Response */
		printf("%s\n",buffer);
		if(exitStatus){
			break;
		}
		/* Sleep to prevent client from entering more than one command in a two second interval */
		sleep(2);
	}
	return 0;
}

























