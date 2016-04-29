#include "client.h"

//int main(int argc, char *argv[])
//{
//	int sockfd = -1;
//	//	int n = -1;
//	//	char buffer[256];
//	struct sockaddr_in serverAddressInfo;
//	struct hostent *serverIPAddress;
//
//	if (argc < 2)
//	{
//		printf("ERROR: no IPAddress input\n");
//		exit(1);
//	}
//	// Convert IPAddress into hostent struct
//	serverIPAddress = gethostbyname(argv[1]);
//	if (serverIPAddress == NULL)
//	{
//		printf("ERROR: no such host\n");
//		exit(0);
//	}
//
//	//Create socket
//	sockfd = socket(AF_INET, SOCK_STREAM, 0);
//	if (sockfd < 0)
//	{
//		perror("ERROR creating socket");
//	}
//
//	//Set serverAddressInfo to zero
//	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));
//
//	serverAddressInfo.sin_family = AF_INET;
//	serverAddressInfo.sin_port = htons(PORT);
//
//	// do a raw copy of the bytes that represent the server's IP address in
//	//   the 'serverIPAddress' struct into our serverIPAddressInfo struct
//	bcopy((char *)serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);
//
//
//
//	/** We now have a blank socket and a fully parameterized address info struct .. time to connect **/
//
//	// try to connect to the server using our blank socket and the address info struct
//	//   if it doesn't work, complain and exit
//	if (connect(sockfd,(struct sockaddr *)&serverAddressInfo,sizeof(serverAddressInfo)) < 0)
//	{
//		perror("ERROR connecting");
//	}
//
//
//	printf("%s\n","We made it");
//
//	//    printf("Please enter the message: ");
//	//
//	//	// zero out the message buffer
//	//    bzero(buffer,256);
//	//
//	//	// get a message from the client
//	//    fgets(buffer,255,stdin);
//	//
//	//	// try to write it out to the server
//	//	n = write(sockfd,buffer,strlen(buffer));
//	//
//	//	// if we couldn't write to the server for some reason, complain and exit
//	//    if (n < 0)
//	//	{
//	//         perror("ERROR writing to socket");
//	//    }
//	//
//	//	// sent message to the server, zero the buffer back out to read the server's response
//	//	bzero(buffer,256);
//	//
//	//	// read a message from the server into the buffer
//	//    n = read(sockfd,buffer,255);
//	//
//	//	// if we couldn't read from the server for some reason, complain and exit
//	//    if (n < 0)
//	//	{
//	//         error("ERROR reading from socket");
//	//	}
//	//
//	//	// print out server's message
//	//    printf("%s\n",buffer);
//
//
//	return 0;
//}
//
