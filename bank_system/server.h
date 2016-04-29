/*
 * server.h
 *
 *  Created on: Apr 27, 2016
 *      Author: je283
 */

#ifndef SERVER_H_
#define SERVER_H_



#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

//Constroversial necessity
#include <errno.h>

/*Hard-coded port number*/
#define PORT 4000



struct Account{
	int index;
	char * name;
	float balance;
	int inSession;
};
typedef struct Account* Account;

#endif /* SERVER_H_ */
