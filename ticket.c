
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"

#define MAXMESSAGE 150


void Display_tic_header(void)
{
	printf("\n------ ----- --------------- ------ ------------------------------ --------");
	printf("\nTicket Acct# Full Name       Status Subject                        Messages");
	printf("\n------ ----- --------------- ------ ------------------------------ --------");

}


void displayTicketDetailRecord(struct Ticket tickets, struct Account account[])
{
	char active[] = "ACTIVE";
	char close[] = "CLOSED";
	char name[31] = { 0 };
	int i;

	for ( i = 0;  account[i].account_number!=0 ; i++)
	{
		if (tickets.cus_acc_no==account[i].account_number)
		{
			strcpy(name, account[i].person.fullname);}

	}




	if (tickets.boolean==1)
	{
		printf("\n%06d %05d %-15s %-6s %-30s %5d", tickets.tic_no, tickets.cus_acc_no, name, active, tickets.subject, tickets.no_of_msg);
	}
	else if(tickets.tic_no!=0)
	{
	printf("\n%06d %05d %-15s %-6s %-30s %5d", tickets.tic_no, tickets.cus_acc_no, name, close, tickets.subject, tickets.no_of_msg);

	}


}

void Display_message_header(struct Ticket tickets)
{

	if (tickets.boolean==0)
	{
		printf("\n================================================================================\n");
		printf("%06d (CLOSED) Re: %s\n", tickets.tic_no, tickets.subject);
		printf("================================================================================\n");
	}
	else if(tickets.boolean == 1)
	{
		printf("\n================================================================================\n");
		printf("%06d (ACTIVE) Re: %s\n", tickets.tic_no, tickets.subject);
		printf("================================================================================\n");
	}
	

}
void Display_message_detail(struct Message messsage ) 
{


	if (messsage.acc_type_of_author=='C')
	{
		printf("CUSTOMER (%s):\n", messsage.author_name);
		printf("   %s\n\n", messsage.messages);
	}
	else if(messsage.acc_type_of_author == 'A')
	{
		printf("AGENT (%s):\n", messsage.author_name);
		printf("   %s\n\n", messsage.messages);
	}




}

int Display_manage_ticket(struct Ticket tickets, struct Account* account)
{

	int menu = -1,i;
	char name[31] = { 0 };
	for (i=0;account[i].account_number != 0; i++)
	{
		if (account[i].account_number==tickets.cus_acc_no)
		{
			strcpy(name, account->person.fullname);

		}

	}


	if (tickets.boolean==1)
	{
		printf("\n----------------------------------------\n");

		printf("Ticket %06d - Update Options\n", tickets.tic_no);
		printf("----------------------------------------\n");

		printf("Status  : ACTIVE\n");
		printf("Subject : %s\n", tickets.subject);
		printf("Acct#   : %05d\n", tickets.cus_acc_no);
		printf("Customer: %s\n", tickets.message[0].author_name);
		printf("----------------------------------------\n");
		printf("1) Add CUSTOMER message\n");
		printf("2) Add AGENT message\n");
		printf("3) Close ticket\n");
		printf("4) Re-activate ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		menu = getIntFromRange(0, 4);

	}
	else
	{
		printf("\n----------------------------------------\n");

		printf("Ticket %06d - Update Options\n", tickets.tic_no);
		printf("----------------------------------------\n");

		printf("Status  : CLOSED\n");
		printf("Subject : %s\n", tickets.subject);
		printf("Acct#   : %05d\n", tickets.cus_acc_no);
		printf("Customer: %s\n", tickets.message[0].author_name);
		printf("----------------------------------------\n");
		printf("1) Add CUSTOMER message\n");
		printf("2) Add AGENT message\n");
		printf("3) Close ticket\n");
		printf("4) Re-activate ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		menu = getIntFromRange(0, 4);
	}
	return menu;

}

int loadAccounts(struct Account accounts[], const int account_size)
{

	struct Account temp[25] = { {0} };



	FILE* fp;
	int  i=0;
	int ACC_NUM=0;
	fp = fopen("accounts.txt", "r");
	if (fp != NULL)
	{
		for (i = 0; i < account_size; i++)
		{
			fscanf(fp, "%d~ %c~ %[^~] ~ %d ~ %lf ~ ", &temp[i].account_number, &temp[i].account_type, temp[i].person.fullname, &temp[i].person.birth_year, &temp[i].person.household_income);
			if (temp[i].account_type == 'C')
			{
				fscanf(fp, "%[^\n]", temp[i].person.country);
				//strcpy(temp[i].user.username, );
				//strcpy(temp[i].user.password, NULL);

			}
			else if (temp[i].account_type == 'A')
			{
				fscanf(fp, "%[^~] ~ %[^~] ~ %[^\n]", temp[i].person.country, temp[i].user.username, temp[i].user.password);
			}
			//fscanf(fp, "%d~ %c~ %[^~] ~ %d ~ %lf ~ %[^~] ~ %[^~] ~ %[^\n]%c", &temp[i].account_number, &temp[i].account_type, temp[i].fullname, &temp[i].birth_year, &temp[i].household_income, temp[i].country, temp[i].username, temp[i].password,&type);
		}
		for (i = 0; i <account_size+1; i++)
		{
			if (temp[i].account_number>0 )
			{
			accounts[i] = temp[i];
			ACC_NUM = i;

			}
			else
			{
				ACC_NUM = i;
				//i = account_size+1;
			}
		}
	}
	else
	{
		printf("ERROR\n");
	}
	fclose(fp);
	return ACC_NUM;

}

int loadTickets(struct Ticket tickets[], const int ticket_size)
{


	struct Ticket temp[17] = { {0} };


	int Num_ticket=0;


	FILE* fP;
	int x = 0, i = 0 ;
	char te[12] = { 0 };
	fP= fopen("tickets.txt", "r");
	if (fP!= NULL)
	{
		for (i = 0; i < ticket_size; i++)
		{
			fscanf(fP, "%d|%d|%d|%[^|] |%d", &temp[i].tic_no, &temp[i].cus_acc_no,&temp[i].boolean, temp[i].subject, &temp[i].no_of_msg);
			for ( x = 0; x < temp[i].no_of_msg; x++)
			{
				fscanf(fP, "|%c |%[^|] |%[^|] ", &temp[i].message[x].acc_type_of_author, temp[i].message[x].author_name, temp[i].message[x].messages);
				if (x==temp[i].no_of_msg-1)
				{
					fscanf(fP, "%[^\n]", te);
				}


			}
			
			


		}
		for (i = 0; i < ticket_size; i++)
		{
			if (temp[i].tic_no>0)
			{
				tickets[i] = temp[i];

			}
			else
			{
				Num_ticket = i;
				i = ticket_size;

			}
		}
	}
	else
	{
		printf("ERROR\n");
	}
	fclose(fP);

	return Num_ticket;

}





























