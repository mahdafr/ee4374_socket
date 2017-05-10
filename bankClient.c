#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "banking.h"

int setupTCPClient(char *servIPAddr, unsigned int portNum) {
    int clientSocket;
    struct sockaddr_in servAddr;

    /* Setup address of server */
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(servIPAddr);
    servAddr.sin_port = htons(portNum);

    /* Create socket */
    if( (clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("Failed to create socket; Error %d: %s\n", errno, strerror(errno));
        return -1;
    }

    /* Connect socket to server */
    if(connect(clientSocket,(struct sockaddr *) &servAddr,sizeof(servAddr)) < 0) {
        printf("Failed to connect socket to %s:%d; Error %d: %s\n", servIPAddr, portNum, errno, strerror(errno));
        return -1;
    }

    return clientSocket;
}

int main(int argc, char **argv) {
    int mySocket;
    char serverIP[15];
    unsigned int portNum;

    if(argc != 6) {
        printf("Usage: bankClient servIPAddr servPortNum command acctNum value\n");
        return -1;
    }

	/* Setup the IP address */
	strcpy(serverIP, argv[1]);
	
	/* Setup TCP port number */
	portNum = atoi(argv[2]);

    /* Setup the client socket */
    if((mySocket = setupTCPClient(serverIP, portNum)) < 0) {
        return -1;
    }
	
	
	
	/* @modified mafravi on 05-09 T */
	/* mySocket was created successfully, so send/receive with it */
	sBANK_PROTOCOL *bank;
	
	//get the transaction type
	switch ( argv[2][0] ) {
		case 'B':
			bank->trans = 2; //balance inquiry
			break;
		case 'W':
			bank->trans = 1; //withdrawal
			break;
		case 'D':
			bank->trans = 0; //deposit
			break;
	}
	//get the account number and value
	bank->acctnum = argv[3];
	bank->value = argv[4];
	
	sBANK_PROTOCOL *received;
	//send the data
	if ( send(mySocket,(void *)*bank,sizeof(*bank),0)<0 )
		return -1;
	else
		recv(mySocket,(void *)*received,sizeof(*received),0);
	
    close(mySocket);
}
