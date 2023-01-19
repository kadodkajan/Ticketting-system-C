#ifndef HELPERS_H_ 
#define HELPERS_H_

#include "account.h"
#include "ticket.h"
/*struct Message
{
	char acc_type_of_author;
	char author_name[MAX_NAMELENGTH + 1];
	char messages[MAX_MESSAGE + 1];

};

struct Ticket
{
	int tic_no;
	int cus_acc_no;
	int boolean;
	char subject[MAX_NAMELENGTH + 1];
	int no_of_msg;
	struct Message message[MAX_NAMELENGTH + 1];


};

struct AccountTicketingData
{
	struct Account* accounts;   // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array

	struct Ticket* tickets;     // array of tickets
	const int TICKET_MAX_SIZE;  // maximum elements for ticket array
};*/






void displayAccountDetailHeader(void);

void displayAccountDetailRecord(struct Account account);

void applicationStartup(struct AccountTicketingData* dataq);

//na
int menuLogin(const struct Account account[], int max_accounts);

void menuAgent(struct Account* account, int max_account, const struct Account* accounT, struct Ticket* tickets, int max_tickets);

int findAccountIndexByAcctNum(int account_num, const struct Account account[], int max_index, int control);

// Pause execution until user enters the enter key 
void pauseExecution(void);
void pauseExecution2(void);



void updateAccount(struct Account* account);

void updatePerson(struct Person* person);

void updateUserLogin(struct UserLogin* user);





#endif
