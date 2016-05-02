

#include "server.h"


pthread_mutex_t lock;
//static int accountsOpen = 0;


void endHandler(int mysignal){


}



void printStatus(struct Account* shm){
	int i;
	int isEmpty = 1;
	struct Account* ptr = shm;
	for (i = 0; i < 20; i++) {
		if((ptr+i)->name[0]!='\0'){
			isEmpty = 0;
			printf("Account: %s, Balance: %.2f%s\n",
					(ptr+i)->name,(ptr+i)->balance,((ptr+i)->inSession == 1) ? ", IN SERVICE" : ""
			);
		}
	}
	printf("\n");
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

void doprocessing (int sock) {
	//for reading from client
	int n;
	char buffer[110];
	//flags for status checks
	int exitStatus = 0;
	int inSession = 0;
	//index f0r loops
	int i;
	//place holder for index after account is started
	int index;
	//write message back to client
	char * message;
	// token stores command and account name when called again in open and start cases
	char* token



	//start while loop and read from client
	while(1){
		bzero(buffer,110);
		n = read(sock,buffer,110);


		if (n < 0) {
			perror("ERROR reading from socket");
			exit(1);
		}

		token = strtok(buffer," ");

		switch(token){
		case "Open":
			//check if in session
			if(inSession){
				message = "Account already in session. To open a new account, end your current session\n";
				write(sock,message, strlen(message));
				continue;
			}
			token = strtok(buffer," ");

			//check if account name was entered
			if (token == NULL){
				message = "Must enter account name.";
				write(sock,message, strlen(message));
				continue;
			}

			int space = 20;

			for(i = 0; i<20; i++){
				//make sure this is right with shared memory:

				//check to see if account already exists
				if(strcmp((accounts+i).name, token) == 0){
					message = "Account already exists.\n";
					write(sock,message, strlen(message));
					continue;
				//check for space
				if((accounts+i).name == NULL){
					space --;
				}
			}
			//if no more space print message and continue
			if(space == 0){
				message = "No more space for account.\n";
				write(sock,message, strlen(message));
				continue;
			}

			//need check for lock on account (access from other users)

			//open account in bank array here

			message = "Account opened successfully.\n";
			write(sock,message, strlen(message));
			break;

		case "Start":
			if(inSession){
				message = "Account already in session. To start a new account, end your current session\n";
				write(sock,message, strlen(message));
				continue;
			}
			token = strtok(buffer," ");

			//check if account name was entered
			if (token == NULL){
				message = "Must enter account name.\n";
				write(sock,message, strlen(message));
				continue;
			}
			for(i = 0; i<20; i++){
				//make sure this is right with shared memory:

				//search for account name
				if(strcmp((accounts+i).name, token) == 0){
					//open account and store index
					inSession = 1;
					index = i;
					message = "Account started successfully.\n";
					write(sock,message, strlen(message));
					continue;
				}
			}
			break;

		case "Credit":
			if (!inSession){
				message = "Must start an account first\n";
				write(sock,message, strlen(message));
				continue;
			}
			//get amount
			token = strtok(buffer, " ");

			//make sure memory access is right
			bank[index].credit = bank[index].credit + atof(token);
			message = "Transaction successful.\n";
			write(sock,message, strlen(message));
			break;

		case "Debit":
			if (!inSession){
				message = "Must start an account first\n";
				write(sock,message, strlen(message));
				continue;
			}
			//get amount
			token = strtok(buffer, " ");

			//make sure memory access is right
			bank[index].debit = bank[index].debit + atof(token);
			message = "Transaction successful.\n";
			write(sock,message, strlen(message));
			break;

		case "Balance":
			if (!inSession){
				message = "Must start an account first\n";
				write(sock,message, strlen(message));
				continue;
			}
			message = "Credit balance: ";
			message = strcat(message, itoa(bank[index].credit));
			message = strcat(message, "\nDebit balance: ");
			message = strcat(message, itoa(bank[index.debit]));
			write(sock,message, strlen(message));
			break;

			break;
		case "Exit":
			return;
			//exit out of child process
		default:
			//Invalid input
			message = "Invalid command. Try again."
			write(sock,message, strlen(message));
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

int main(int argc, char **argv) {

	//Initalize the bank with empty accounts
	int i;
	struct Account Bank[20];
	for(i=0;i<20;i++){
		Bank[i].balance = 0;
		Bank[i].inSession = 0;
		Bank[i].index = i;
		memset(Bank[i].name,0,100);
	}

	int shmid;
	key_t key;

	//Pointers to the shared memory and a pointer variable.
	struct Account *shm;

	int SIZE = sizeof(struct Account)*20;
	int FLAG = IPC_CREAT | 0666;

	key = 5678;

	shmid =  shmget(key, SIZE, FLAG);
	if (shmid  < 0) {
		perror("shmget");
		exit(1);
	}

	/* Attach memory */
//	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
//		perror("shmat");
//		exit(1);
//	}
	shm = shmat(shmid, NULL, 0);
	if(shm==NULL){
		perror("shmat");
		exit(1);
	}


	//UNFINISHED
	//If Ctrl-C/Z is entered to exit program
	signal(SIGINT,endHandler);




	//Copy the Bank array into shared memory
	memcpy(shm,Bank,SIZE);


	strcpy(shm[0].name,"bob");
	strcpy(shm[1].name,"jack");
	strcpy(shm[0].name,"nick");

	while(1){
		printStatus(shm);
		sleep(20);
	}



//	pthread_t thr[MAX_THREADS];
//
//
//	if(pthread_mutex_init(&lock,NULL)!=0){
//		printf("Mutex failed to initialize");
//		return 1;
//	}
//	printf("End");
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
//
//	/* --------------- */
//	pid_t pid;
//	int newsockfd = -1;
//
//	while(1){
//		clientfd = accept(socketfd, (struct sockaddr *) &clientAddressInfo, (socklen_t*)&clientLen);
//
//
//		if (clientfd < 0)
//		{
//			perror("ERROR on accept");
//		}
//
//		/* Create child process */
//		pid = fork();
//
//		if (pid < 0) {
//			perror("ERROR on fork");
//			exit(1);
//		}
//
//		if (pid == 0) {
//			/* This is the client process */
//			close(socketfd);
//			doprocessing(newsockfd);
//			exit(0);
//		}
//		else {
//			close(newsockfd);
//		}
//	}





	/* Need to detach from and remove shared memory */
	shmdt(shm);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}







































