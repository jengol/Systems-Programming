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

	puts("Connected to server: %s\n",argv[1]);
	/* Data read in from stdin */
	char buffer[100];
	/* User command */
	char choice;
	/* Condition to 'quit' program */
	int exitStatus = 0;
	int inSession = 0;

	while(1){

		printf("Please enter a command: (Case sensitive letter)\n");
		printf("Open account (o)\n");
		printf("Start account (s)\n");
		printf("Credit (c)\n");
		printf("Debit (d)\n");
		printf("Balance (b)\n");
		printf("End (e)\n");
		printf("Quit (q)\n");

		//Read in choice
		choice = getchar();
		write(socketfd,choice,1);

		switch(choice){
		case 'o':
			if(inSession){
				printf("Already in session.");
				continue;
			}
			printf("Enter a new account name\n");
			fgets(buffer);
			write(socketfd,buffer,strlen(buffer));
			bzero(buffer,100);
			read(socketfd,buffer,100);
			/* Server Response */
			printf("%s\n",buffer);

			break;
		case 's':
			if(inSession){
				printf("Already in session.");
				continue;
			}
			printf("Enter account name\n");
			fgets(buffer);
			write(socketfd,buffer,strlen(buffer));

			break;
		case 'c':
			if(!inSession){
				printf("Must start an account first");
			}
			printf("Enter amount to credit/deposit:\n");
			fgets(buffer);
			write(socketfd,buffer,strlen(buffer));
			break;
		case 'd':
			if(!inSession){
				printf("Must start an account first");
				continue;
			}
			printf("Enter amount to debit/withdraw:\n");
			fgets(buffer);
			write(socketfd,buffer,strlen(buffer));
			break;
		case 'b':
			break;
		case 'e':
			inSession = 0;
			break;
		case 'q':
			exitStatus = 1;
			break;

		default:
		}
		bzero(buffer,100);
		read(socketfd,buffer,100);
		/* Server Response */
		printf("%s\n",buffer);
		inSession = 1;

	}

	bzero(buffer,100);
	read(socketfd,buffer,255);
	printf("%s\n",buffer);

	if(exitStatus == 1){
		break;
	}
	/* Sleep to prevent client from entering more than one command in a two second interval */
	sleep(2);


return 0;
}

























