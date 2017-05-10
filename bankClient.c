#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "banking.h"
#include <stdlib.h> //@modified mafravi on 05-09 T
#include <unistd.h> //@modified mafravi on 05-09 T

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
    unsigned int portNum,trans,accnum,value; 	

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
	if ( argc==6 ) {
		
		/*
		//get the transaction type
		switch ( (char) argv[3][0] ) {
			case 'B':
				toSend->trans = BANK_TRANS_INQUIRY; //balance inquiry
				break;
			case 'W':
				toSend->trans = BANK_TRANS_WITHDRAW; //withdrawal
				break;
			case 'D':
				toSend->trans = BANK_TRANS_DEPOSIT; //deposit
				break;
		}*/
		//get the transaction type
		if ( strcmp(argv[3],"I")==0 ){
			trans = BANK_TRANS_INQUIRY; //balance inquiry
		}
		else if ( strcmp(argv[3],"W")==0 ){
			trans = BANK_TRANS_WITHDRAW; //withdrawal
		}
		else if ( strcmp(argv[3],"D")==0 ){
			trans = BANK_TRANS_DEPOSIT; //deposit
		}
		//get the account number and value
		accnum = atoi(argv[4]);
		value = atoi(argv[5]);
		
		sBANK_PROTOCOL toSend = {trans,accnum,value};
		
		printf("Transaction: %d\nAccount Number: %d\nAmount: %d\n",trans,acctnum,value);
		
		sBANK_PROTOCOL rec;
		//send and receive the data
		if ( send(mySocket,(void *)&toSend,sizeof(toSend),0)<0 ){
			puts("not sent");
			return -1;
		} else printf("sent\n");
		
		if ( recv(mySocket,&rec,sizeof(sBANK_PROTOCOL),0)<0 ){
			puts("not received");
			return -1;
		} else puts("received"); 
		//char s[15];
		//sprintf(s,"%d\n\n",rec);
		
		//received w/out error so parse the return message
		//sBANK_PROTOCOL *got = (struct sBANK_PROTOCOL *) rec;
		printf("Transaction: %d\nAccount Number: %d\nAmount: %d\n",rec.trans,rec.acctnum,rec.value);
		//printf("Transaction: %u\nAccount Number: %u\nAmount: %u\n",got->trans,got->acctnum,got->value);
	}
	
    close(mySocket);
	return 0;
}
