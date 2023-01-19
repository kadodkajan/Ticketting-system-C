#ifndef TICKET_H_ 
#define TICKET_H_


#include "account.h"




struct Ticket
{
	int tic_no;
	int cus_acc_no;
	int boolean;
	char subject[MAX_NAMELENGTH + 1];
	int no_of_msg;
	struct Message
	{
		char acc_type_of_author;
		char author_name[MAX_NAMELENGTH + 1];
		char messages[MAX_MESSAGE + 1];

	}message[20];

};

struct AccountTicketingData
{
	struct Account* accounts;   // array of accounts 
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array 

	struct Ticket* tickets;     // array of tickets 
	const int TICKET_MAX_SIZE;  // maximum elements for ticket array 
};
void Display_tic_header(void);
void displayTicketDetailRecord(struct Ticket tickets, struct Account account[]);
void Display_message_header(struct Ticket tickets);
void Display_message_detail(struct Message messsage);
int Display_manage_ticket(struct Ticket tickets, struct Account *account);
int loadAccounts(struct Account accounts[],const int account_size);
int loadTickets(struct Ticket tickets[], const int ticket_size);
#endif