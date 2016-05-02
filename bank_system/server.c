

#include "server.h"


pthread_mutex_t lock;
//static int accountsOpen = 0;


//void printStatus(){
//	int i;
//	int isEmpty = 1;
//	for (i = 0; i < 20; ++i) {
//		if(Bank[i].name!=NULL){
//			isEmpty = 0;
//			printf("Account: %s, Balance: %.2f%s\n",
//					Bank[i].name,Bank[i].balance,(Bank[i].inSession == 1) ? ", IN SERVICE" : ""
//			);
//		}
//	}
//	if(isEmpty){
//		printf("NO ACCOUNTS\n");
//	}
//	return;
//}

/*
 * SERVER
 * 1. Takes no command line arguments; Port is hard-coded
 * 2. Listens for requests
 * 3. Prints account information every 20 seconds.
 */

void doprocessing (int sock) {
   int n;
   char buffer[256];
   while(1){
   bzero(buffer,256);
   n = read(sock,buffer,255);


   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }

   int i;
   char * temp;

   switch(buffer){
		case 'o':
			for(i = 0; i<20; i++){
				if((accounts+i).name==NULL){
					continue;
				} else {
					temp = "Enter name of account\n";
					n =	write(sock,temp,strlen(temp));
				}

			}
			if(){
				printf("Account already in session. To open a new account, end (e) your current session\n");
				continue;
			}
			printf("Enter new account name\n");
			while(fgets(buffer)==NULL){
				bzero(buffer);
				printf("Error inputting name, try again\n");
				/* no break */
			}
			//Check if name is valid
			x = write(socketfd,choice,1);
			x = write(socketfd,buffer,strlen(buffer));
			break;
		case 's':
			if(inSession){
				printf("Account already in session. To start a different session, end (e) your current session\n");
				continue;
			}
			x = write(socketfd,choice,1);
			inSession = 1;
			break;
		case 'c':
			printf("Enter amount to credit/deposit:\n");
			x = write(socketfd,choice,1);
			fgets(buffer);
			x = write(socketfd,buffer,strlen(buffer));
			break;
		case 'd':
			printf("Enter amount to debit/withdraw:\n");
			x = write(socketfd,choice,1);
			fgets(buffer);
			x = write(socketfd,buffer,strlen(buffer));
			break;
		case 'b':
			x = write(socketfd,choice,1);
			break;
		case 'e':
			x = write(socketfd,choice,1);
			inSession = 0;
			break;
		case 'q':
			x = write(socketfd,choice,1);
			exitStatus = 1;
			break;

		}

   }



   printf("Here is the message: %s\n",buffer);
   printf("%d\n",getpid());
   n = write(sock,"I got your message",18);

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   }
}

int main(int argc, char **argv) {

	printf("Hello\n");

	//Initalize the bank with empty accounts
	//int i;

//	struct Account Bank[20];
//	for(i=0;i<20;i++){
//		Bank[i].balance = 0;
//		Bank[i].inSession = 0;
//		Bank[i].index = i;
//		Bank[i].name = "bob";
//	}
//
//	int shmid;
//	key_t key = 5678;
//
//	if((shmid = shmget(key,SIZE, IPC_CREAT | 0666)) < 0) {
//		perror("shmget");
//		exit(1);
//
//	}


	int shmid;
	key_t key;
	char *shm, *s;

	int SIZE = sizeof(struct Account)*20;
	int FLAG = IPC_CREAT | 0666;

	/*
	 * We'll name our shared memory segment
	 * "5678".
	 */
	key = 5678;


	/*
	 * Create the segment.
	 */
	shmget(key, SIZE, FLAG);
//	if ((shmid = shmget(key, SIZE, FLAG)) < 0) {
//		perror("shmget");
//		exit(1);
//	}

	/*
	 * Now we attach the segment to our data space.
	 */
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
		perror("shmat");
		exit(1);
	}

	/*
	 * Now put some things into the memory for the
	 * other process to read.
	 */
	s = shm;

	while (*shm != '*')
		sleep(1);

	exit(0);




		printStatus();

		pthread_t thr[MAX_THREADS];


		if(pthread_mutex_init(&lock,NULL)!=0){
			printf("Mutex failed to initialize");
			return 1;
		}
		printf("End");
		int socketfd = -1;
		int clientfd = -1;
		int clientLen = -1;


		//	char clientBuffer[256];

		struct sockaddr_in serverAddressInfo;
		struct sockaddr_in clientAddressInfo;

		socketfd = socket(AF_INET, SOCK_STREAM, 0);
		if (socketfd < 0)
		{
			perror("ERROR opening socket");
		}

		/* Initialize sockaddr_in */

		// set sockaddr_in to zero
		bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));
		// Set remote port
		serverAddressInfo.sin_port = htons(PORT);
		// Set network address type
		serverAddressInfo.sin_family = AF_INET;
		// Set incoming connections type
		serverAddressInfo.sin_addr.s_addr = INADDR_ANY;


		// Bind the server socket to the local port
		if (bind(socketfd, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo)) < 0)
		{
			perror("ERROR on binding");
		}

		// Listen for client connections
		listen(socketfd,5);

		// determine the size of a clientAddressInfo struct
		clientLen = sizeof(clientAddressInfo);


		/* --------------- */
		pid_t pid;
		int newsockfd = -1;

		while(1){
			clientfd = accept(socketfd, (struct sockaddr *) &clientAddressInfo, (socklen_t*)&clientLen);


			if (clientfd < 0)
			{
				perror("ERROR on accept");
			}

			/* Create child process */
			pid = fork();

			if (pid < 0) {
				perror("ERROR on fork");
				exit(1);
			}

			if (pid == 0) {
				/* This is the client process */
				close(socketfd);
				doprocessing(newsockfd);
				exit(0);
			}
			else {
				close(newsockfd);
			}
		}
		printf("%s\n","We made it");
	return 0;
}







































