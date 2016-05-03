

#include "server.h"


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

void handle_signal(int signal){

	switch (signal) {
	case SIGHUP:
		break;
	case SIGTSTP:
		printf("YOU HAVE STOPPED THE PROGRAM USING CTRL-Z");
		break;
	case SIGINT:
		exit(0);
	case SIGCHLD:
		break;
	default:
		fprintf(stderr, "Caught wrong signal: %d\n", signal);
		return;
	}
}

/*
 * SERVER
 * 1. Takes no command line arguments; Port is hard-coded
 * 2. Listens for requests
 * 3. Prints account information every 20 seconds.
 */



void doprocessing (int sock, struct Account* bank) {
	//for reading from client
	int n;
	char buffer[110];
	/* flag to check status */
	int inSession = 0;
	//index for loops
	int i;
	//place holder for index after account is started
	int index;
	//write message back to client
	char * message;
	// token stores command and account name when called again in open and start cases
	char* token;
	// boolean to continue outer loop
	int continueOuter;
	//Current num of avaiable accounts
	int space;

	//start while loop and read from client
	while(1){
		continueOuter = 0;
		bzero(buffer,110);
		/* Read input from client */
		n = read(sock,buffer,110);

		if (n < 0) {
			perror("ERROR reading from socket");
			exit(1);
		}

		token = strtok(buffer," ");

		switch(token[0]){
		case 'O':
			if(strcmp("Open",token) != 0){
				message = "Invalid command1. Try again.";
				write(sock,message, strlen(message));
				continue;
			}
			//check if in session
			if(inSession){
				message = "Account already in session. To open a new account, end your current session\n";
				write(sock,message, strlen(message));
				continue;
			}
			token = strtok(NULL," ");
			token[strlen(token)-1] = '\0';

			//check if account name was entered
			if (token == NULL){
				message = "Must enter account name.";
				write(sock,message, strlen(message));
				continue;
			}

			space = 20;

			for(i = 0; i<20; i++){
				//check to see if account already exists
				if(strcmp(bank[i].name,token) == 0){
					message = "Account already exists.\n";
					write(sock,message,strlen(message));
					continueOuter = 1;
					break;
				} else if(bank[i].name[0] != '\0'){
					space--;
				}
			}

			if(continueOuter){
				continue;
			}

			//if no more space print message and continue
			if(space == 0){
				message = "No more space for account.\n";
				write(sock,message, strlen(message));
				continue;
			}
			for(i=0;i<20;i++){
				if(bank[i].name[0]=='\0'){
					break;
				}
			}
			strcpy(bank[i].name,token);

			message = "Account opened successfully.\n";
			write(sock,message, strlen(message));
			break;

		case 'S':
			if(strcmp("Start",token) != 0){
				message = "Invalid command2. Try again.";
				write(sock,message, strlen(message));
			}
			if(inSession){
				message = "Account already in session. To start a new account, end your current session\n";
				write(sock,message, strlen(message));
				continue;
			}
			token = strtok(NULL," ");
			token[strlen(token)-1] = '\0';

			//check if account name was entered
			if (token == NULL){
				message = "Must enter account name.\n";
				write(sock,message, strlen(message));
				continue;
			}
			for(i = 0; i<20; i++){
				//search for account name
				if(strcmp(bank[i].name, token) == 0){
					//open account and store index
					inSession = 1;
					index = i;
					message = "Account started successfully.\n";
					write(sock,message, strlen(message));
					continueOuter = 1;
					break;
				}
			}
			if(continueOuter){
				continue;
			}
			//Failed to find account
			message = "Account does not exist. Try again.\n";
			write(sock,message, strlen(message));
			continue;

			break;

		case 'C':
			if(strcmp("Credit",token) != 0){
				message = "Invalid command2. Try again.";
				write(sock,message, strlen(message));
			}
			if (!inSession){
				message = "Must start an account first\n";
				write(sock,message, strlen(message));
				continue;
			}
			//get amount
			token = strtok(NULL, " ");
			token[strlen(token)-1] = '\0';

			//make sure memory access is right
			if(atof(token)){
				bank[index].balance += atof(token);
				message = "Credit successful.\n";
				write(sock,message, strlen(message));
			} else {
				message = "Invalid credit entry.\n";
				write(sock,message, strlen(message));
			}
			break;
		case 'D':
			if(strcmp("Debit",token) != 0){
				message = "Invalid command3. Try again.";
				write(sock,message, strlen(message));
			}
			if (!inSession){
				message = "Must start an account first\n";
				write(sock,message, strlen(message));
				continue;
			}
			//get amount
			token = strtok(NULL, " ");
			token[strlen(token)-1] = '\0';

			if(atof(token)){
				if(bank[index].balance - atof(token) < 0){
					message = "Invalid credit entry. Attempted to withdraw more than balance.\n";
					write(sock,message, strlen(message));
					continue;
				}
				bank[index].balance -= atof(token);
				message = "Transaction successful.\n";
				write(sock,message, strlen(message));
			} else {
				message = "Invalid debit input.\n";
				write(sock,message, strlen(message));
			}
			break;

		case 'B':
			token[strlen(token)-1] = '\0';
//			printf("%d\n", strlen("Balance"));
//			printf("%d\n", strlen(token));
//
//			printf("the token:_%s\n",token);
			if(strcmp("Balance",token) != 0){
				message = "Invalid command4. Try again.";
				write(sock,message, strlen(message));
			}
			if (!inSession){
				message = "Must start an account first\n";
				write(sock,message, strlen(message));
				continue;
			}

			//FIX THIS
			bzero(buffer,110);
			write(sock,buffer,sprintf(buffer,"Balance: %.2f",bank[i].balance));
			break;
		case 'F':
			token[strlen(token)-1] = '\0';
			if(strcmp("Finish",token) != 0){
				message = "Invalid command5. Try again.";
				write(sock,message, strlen(message));
			}
			inSession = 0;

			message = "Session finished.";
			write(sock,message, strlen(message));
			continue;
			//exit out of child process
		case 'E':
			token[strlen(token)-1] = '\0';
			if(strcmp("Exit",token) != 0){
				message = "Invalid command6. Try again.";
				write(sock,message, strlen(message));
			}
			inSession = 0;
			message = "Exiting...";
			write(sock,message, strlen(message));
			return;
		default:
			//Invalid input
			message = "Invalid command7. Try again.";
			write(sock,message, strlen(message));
			continue;
		}

	}

	printf("%d\n",getpid());
}


int main( int argc, char *argv[] ) {



	//	Initalize the bank with empty accounts
	int i;
	struct Account Bank[20];
	for(i=0;i<20;i++){
		Bank[i].balance = 0;
		Bank[i].inSession = 0;
		memset(Bank[i].name,'\0',100);
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

	shm = shmat(shmid, NULL, 0);
	if(shm==NULL){
		perror("shmat");
		exit(1);
	}

	//Copy the Bank array into shared memory
	memcpy(shm,Bank,SIZE);

	struct sigaction sa;
	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);

	if (sigaction(SIGHUP, &sa, NULL) == -1)
		perror("Error: cannot handle SIGHUP"); // Should not happen
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT"); // Should not happen
	if (sigaction(SIGTSTP, &sa, NULL) == -1)
		perror("Error: cannot handle SIGTSTP"); // Should not happen
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
		perror("Error: cannot handle SIGTSTP"); // Should not happen


	int sockfd, newsockfd, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n, pid;

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}

	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}

	/* Now start listening for the clients, here
	 * process will go in sleep mode and will wait
	 * for the incoming connection
	 */

	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	puts("Starting\n");
	while (1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0) {
			perror("ERROR on accept");
			exit(1);
		}

		printf("New client accepted\n");
		/* Create child process */
		pid = fork();

		if (pid < 0) {
			perror("ERROR on fork");
			exit(1);
		}

		if (pid == 0) {
			/* This is the client process */
			close(sockfd);
			doprocessing(newsockfd,shm);
			exit(0);
		}
		else {
			close(newsockfd);
		}

	} /* end of while */
	close(sockfd);


	//	/* Need to detach from and remove shared memory */
	//	shmdt(shm);
	//	shmctl(shmid,IPC_RMID,NULL);
}

