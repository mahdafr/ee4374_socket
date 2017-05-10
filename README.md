# Programming Assignment 4
## Task 1
Unpack the Programming Assignment 4 template provided by the instructor into your home directory: 'tar zxvf student_prog4.tgz'. This will create a directory called 'student_prog4', please rename this directory to firstinitiallastname_prog4 using the mv command. For example, the instructor would rename the directory by executing "mv student_prog4 mmcgarry_prog4"

## Task 2
Develop a bank client application (bankClient) that takes the following command line arguments and then communicates with the server to process the transaction:
bankClient servIPAddr servPortNum transaction acctnum value
servIPAddr is the IP address of the bank server
servPortNum is the port number of the bank server
transaction is {B for balance inquiry, D for deposit, or W for withdrawal}
acctnum is the account number
value is the value of the transaction in pennies (ignored for a balance inquiry)

The protocol between the client and server is simple: they exchange a single message
type in either direction (the sBANK_PROTOCOL data structure seen below).

/* Bank Transaction Types */
#define BANK_TRANS_DEPOSIT 0
#define BANK_TRANS_WITHDRAW 1
#define BANK_TRANS_INQUIRY 2

typedef struct {
unsigned int trans; /* transaction type */
unsigned int acctnum; /* account number */
unsigned int value; /* value */
} sBANK_PROTOCOL;

The server responds in the following way to transaction requests from the client:
trans and acctnum are repeated from client message, value depends on the transaction
For a deposit, the deposited value is set in the value field.
For a withdrawal, if there is insufficient funds then a zero is set in the value field,
otherwise the withdrawn amount is set in the value field.
For a balance inquiry, the balance of the account is set in the value field.

You can test your client with the instructor¡¯s server application that will be available at IP
address 129.108.32.2 port 26207.

## Task 3
You will find the definition of the bank protocol structure in a header file named
banking.h.

## Task 4
Use a Makefile to build your program.

## Task 5
Submit the deliverables, indicated below, as a single tarball file named
firstinitiallastname_prog4.tgz through Blackboard.

## Deliverables:
### 1
Submit all of the source files in your Programming Assignment 4 directory
(Makefile, bankClient.c, banking.h) as a single tarball file. You can create this by
changing to the directory above your Programming Assignment 4 directory and
execute ¡®tar zcvf firstinitiallastname_prog4.tgz firstinitiallastname_prog4¡¯. As an
example, the instructor would execute ¡®tar zcvf mmcgarry_prog4.tgz
mmcgarry_prog4¡¯. This file will be submitted through Blackboard.