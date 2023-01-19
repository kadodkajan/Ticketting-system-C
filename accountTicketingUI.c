
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"




void displayAccountDetailHeader(void)


{
	printf("\nAcct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
	printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");

}

void displayAccountDetailRecord(struct Account account)
{
	char PASS[9] = "********";
	char account_typ_CUST[9] = "CUSTOMER";
	char account_typ_AGENT[6] = "AGENT";
	int i;
	char up[31] = { 0 };
	//int x=strlen(account.person.country);
	for (i = 0; account.person.country[i] != '\0'; i++)
	{
		up[i] = toupper(account.person.country[i]);

	}
	up[i + 1] = '\0';


	for (i = 0; i < 8; i = i + 2)
	{
		PASS[i] = account.user.password[i];
	}
	if (account.account_type == 'A')
	{
		printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n", account.account_number, account_typ_AGENT, account.person.fullname, account.person.birth_year, account.person.household_income, up, account.user.username, PASS);

	}
	else //if (ac_type == 'C')
	{

		printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n", account.account_number, account_typ_CUST, account.person.fullname, account.person.birth_year, account.person.household_income, up, account.user.username, PASS);


	}




}

void applicationStartup(struct AccountTicketingData* dataq)
{
	int x = 0;
	




	do
	{
		x = menuLogin(dataq->accounts, dataq->ACCOUNT_MAX_SIZE);
		if (x > 0)
		{
			printf("\n");
			menuAgent(dataq->accounts, dataq->ACCOUNT_MAX_SIZE, &dataq->accounts[x], dataq->tickets, dataq->TICKET_MAX_SIZE);

		}

		if (x == 0)
		{
			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n\n");
			//clearStandardInputBuffer();
			break;
		}


	} while (x != 0);





};









int menuLogin(const struct Account account[], int max_accounts)
{
	int NUM, i;
	char YorN;
	int errorcounter = 0;

	//

	printf("==============================================\n");
	printf("Account Ticketing System - Login\n");
	printf("==============================================\n");

	printf("1) Login to the system\n");
	printf("0) Exit application\n");
	printf("----------------------------------------------\n\n");

	printf("Selection: ");
	NUM = getIntFromRange(0, 1);

	if (NUM == 0)
	{
		printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
		YorN = getCharOption("yYnN");
		//clearStandardInputBuffer();

		printf("\n");
		if (YorN == 'n' || YorN == 'N')
		{
			NUM = -2;
		}
		if (YorN == 'y' || YorN == 'Y')
		{
			NUM = 0;
		}




	}


	if (NUM == 1)
	{

		//int foo = 0;
		char temp_us[99] = { 0 };
		char temp_pass[99] = { 0 };
		int counter = 2;
		do {
			printf("\nEnter the account#: ");
			NUM = getInteger();

			printf("User Login        : ");
			scanf("%s", temp_us);
			//printf("--%s\n", temp_us);
			printf("Password          : ");
			//getCString(temp_pass, PASSWORD, PASSWORD);
			scanf("%s", temp_pass);


			for (i = 0; i < max_accounts; i++)
			{
				int s = strcmp(temp_pass, account[i].user.password) + strcmp(temp_us, account[i].user.username);

				if (account[i].account_number == NUM && account[i].account_type == 'A' && s == 0)
				{
					NUM = i;
					i = max_accounts;
					errorcounter = 0;
				}

				else
				{
					errorcounter++;
				}

			}


			if (errorcounter > 0 && counter != -1)
			{

				printf("INVALID user login/password combination! [attempts remaining:%d]\n", counter);
				counter--;
				//printf("ERROR:  Login failed!\n\n");
				//printf(" << ENTER key to Continue... >> ");
				//getchar();


				NUM = -2;
			}
			if (counter == -1)
			{
				printf("\nERROR:  Access Denied.\n\n");
				errorcounter = 0;

				pauseExecution();
				printf("\n");

			}



		} while (errorcounter != 0);

	}

	return NUM;
}




void menuAgent(struct Account* account, int max_account, const struct Account* accounT, struct Ticket* ticket, int max_tickets)

{

	int menu = 0, i, available_account = 0;
	int temp = 0, j;
	int boo = 0;


	do
	{


		printf("AGENT: %s (%d)\n", accounT->person.fullname, accounT->account_number);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf("1) Add a new account\n");
		printf("2) Modify an existing account\n");
		printf("3) Remove an account\n");
		printf("4) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf("5) List new tickets\n");
		printf("6) List active tickets\n");
		printf("7) List closed tickets\n");
		printf("8) Add a new ticket\n");
		printf("9) Manage a ticket\n");




		printf("----------------------------------------------\n");
		printf("0) Logout\n");

		printf("\nSelection: ");
		menu = getIntFromRange(0, 9);

		switch (menu)
		{

		case 1:
		{
			int goo = 0;
			for (i = 0; i < max_account && goo == 0; i++)
			{
				//printf("||||%d\n", i);
				//printf(" ------%d\n", account[i].account_number);

				if (account[i].account_number == 0)
				{
					available_account = 1;
					//i = max_account;
					goo = 1;
				}
			}
			if (available_account == 0)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution2();
			}
			if (available_account == 1)
			{
				int high_ac_num = 0;

				for (j = 0; j < max_account; j++)
				{
					if (j == 0)

					{
						high_ac_num = account[j].account_number;
					}
					else if (account[j].account_number > high_ac_num)
					{
						high_ac_num = account[j].account_number;
					}


				}
				//printf("=========%d\n", i);

				available_account = i - 1;
				account[i - 1].account_number = high_ac_num + 1;

				printf("\nNew Account Data (Account#:%5d)\n", (account[available_account].account_number));
				printf("----------------------------------------\n");
				//printf("Enter the account number: ");
				//account->account_number = getPositiveInteger();
				printf("Enter the account type (A=Agent | C=Customer): ");
				account[available_account].account_type = getCharOption("AC");

				printf("\n");


				getPerson(&account[available_account].person);

				if (account[available_account].account_type == 'A')
				{
					getUserLogin(&account[available_account].user);
					printf("\n");


				}
				else
				{//
				}

				// 
				printf("*** New account added! ***\n\n");// 88 line

				//printf("");
				//printf("<< ENTER key to Continue... >>");
				//clearStandardInputBuffer();

				pauseExecution();
				printf("\n");
				//printf("<< ENTER key to Continue... >>\n\n");



			}


		}break;


		case 2:

		{
			int acc_num;
			int contr = 0;

			printf("\nEnter the account#: ");
			scanf("%d", &acc_num);

			for (i = 0; i < max_account; i++)
			{

				if (account[i].account_number == acc_num)
				{
					updateAccount(&account[i]);
					i = max_account;
				}
				else
				{
					contr++;
				}

			}




			if (contr == max_account)
			{
				printf("\nERROR :Account not found\n");
				printf("\n");

				pauseExecution2();
				printf("\n");
			}



		}break;

		case 3:

		{
			int tic_count = 0;
			int y = 0;
			int userinpu = findAccountIndexByAcctNum(0, account, max_account, 1);
			for (i = 0; i < max_account; i++)
			{
				if (account[userinpu].account_number == account[i].account_number)
				{
					y = 1;
				}


			}
			if (accounT->account_number == account[userinpu].account_number)
			{

				printf("\nERROR: You can't remove your own account!\n\n");

				pauseExecution2();

			}
			else if (y == 1)
			{
				char Yorn;
				//displayAccountDetailHeader();
				printf("\nAcct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
				printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
				displayAccountDetailRecord(account[userinpu]);
				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
				Yorn = getCharOption("YyNn");
				if (Yorn == 'Y' || Yorn == 'y')
				{
					struct Ticket temp[5] = { {0} };

					for (i = 0; i < max_tickets; i++)
					{

						//printf("\nsy=%d,us=%d\n", ticket[i].cus_acc_no, account[userinpu].account_number);

						if (ticket[i].cus_acc_no == account[userinpu].account_number)
						{
							tic_count++;
							ticket[i].tic_no=0;
							ticket[i] = temp[0];
						}

					}
					account[userinpu].account_number = 0;

					printf("\n*** Account Removed! (%d ticket(s) removed) ***\n\n", tic_count);



				}
				/*while (getchar() != '\n')
				{
					; // On purpose: do nothing
				}*/

				pauseExecution();
				printf("\n");

			}
			else if (y == 0)

			{
				printf("ERROR :Account not found\n");
				pauseExecution();
				printf("\n");

			}




		}	 break;



		case 4:
		{

			for (i = 0; i < max_account; i++)
			{
				if (account[i].account_type == 'C')
				{
					*account[i].user.password = 0;

					*account[i].user.username = 0;
				}


			}

			displayAccountDetailHeader();
			for (i = 0; i < max_account; i++)
			{

				if (account[i].account_number != 0)
				{
					displayAccountDetailRecord(account[i]);

				}


			}
			printf("\n");
			pauseExecution2();
			//printf("\n");


		}		break;
		case 5:
		{
			temp = 0;
			do
			{
				boo = 0;

				Display_tic_header();

				for (i = 0; i < max_tickets; i++)
				{

					if (ticket[i].no_of_msg == 1 && ticket[i].boolean == 1)
					{
						displayTicketDetailRecord(ticket[i], account);
					}


				}
				printf("\n------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &temp);

				for (i = 0; i < max_tickets; i++)
				{

					if (temp == ticket[i].tic_no)
					{

						Display_message_header(ticket[i]);
						for (j = 0; j <= ticket[i].no_of_msg; j++)
						{
							Display_message_detail(ticket[i].message[j]);

						}
						//printf("\n");

						pauseExecution();

					}
					else if (temp == 0)
					{
						i = max_tickets;
						printf("\n");


					}
					else if (temp != ticket[i].tic_no)
					{
						boo++;
					}


				}
				if (boo == max_tickets)
				{
					printf("\nERROR: Invalid ticket number.\n");
					printf("\n");

					pauseExecution();

				}







				//pauseExecution();
			} while (temp != 0);





		}break;
		case 6:
		{
			temp = 0;
			do
			{
				boo = 0;

				Display_tic_header();

				for (i = 0; i < max_tickets; i++)
				{

					if (ticket[i].boolean == 1)
					{
						displayTicketDetailRecord(ticket[i], account);
					}


				}
				printf("\n------ ----- --------------- ------ ------------------------------ --------\n");
				printf("\nEnter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &temp);

				for (i = 0; i < max_tickets; i++)
				{

					if (temp == ticket[i].tic_no && ticket[i].boolean == 1)
					{

						Display_message_header(ticket[i]);
						for (j = 0; j <= ticket[i].no_of_msg; j++)
						{
							Display_message_detail(ticket[i].message[j]);

						}
						//printf("\n");

						pauseExecution();

					}
					else if (temp == 0)
					{
						i = max_tickets;
						printf("\n");


					}
					else if (temp != ticket[i].tic_no)
					{
						boo++;
					}


				}
				if (boo == max_tickets)
				{
					printf("\nERROR: Invalid ticket number.\n");
					printf("\n");

					pauseExecution();

				}


			} while (temp != 0);



		}break;
		case 7:
		{
			do {
				boo = 0;
				temp = 0;

				Display_tic_header();

				for (i = 0; i < max_tickets; i++)
				{

					if (ticket[i].boolean == 0)
					{
						displayTicketDetailRecord(ticket[i], account);
					}


				}

				printf("\n------ ----- --------------- ------ ------------------------------ --------\n\n");

				printf("Enter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				scanf("%d", &temp);

				for (i = 0; i < max_tickets; i++)
				{

					if (temp == ticket[i].tic_no && ticket[i].boolean == 0)
					{

						Display_message_header(ticket[i]);
						for (j = 0; j <= ticket[i].no_of_msg; j++)
						{
							Display_message_detail(ticket[i].message[j]);

						}
						//printf("\n");

						pauseExecution();

					}
					else if (temp == 0)
					{
						i = max_tickets;
						printf("\n");

					}
					else //if (temp != ticket[i].tic_no && ticket[i].boolean == 1)

					{
						boo++;
					}


				}
				if (boo == max_tickets)
				{
					printf("\nERROR: Invalid ticket number.\n");
					printf("\n");

					pauseExecution();

				}

			} while (temp != 0);






		}break;
		case 8:
		{

			/*int high_ms_num = 0;
			int availabale_tick = 0;
			for (i = 0; i < max_tickets; i++)
			{
				if (ticket[i].tic_no == 0)
				{
					availabale_tick = i;
					i = max_tickets;
				}
			}
			if (availabale_tick == 0)
			{
				printf("ERROR: Ticket listing is FULL, call ITS Support!\n");
			}
			if ((availabale_tick != 0))
			{


				for (i = 0; i < max_tickets; i++)
				{
					if (i == 0)
					{
						high_ms_num = ticket[i].tic_no;
					}
					else if (ticket[i].tic_no > high_ms_num)
					{
						high_ms_num = ticket[i].tic_no;
					}


				}

			}
			ticket[availabale_tick].tic_no = high_ms_num+1;//+1*/

			i = findAccountIndexByAcctNum(0, account, max_account, 1);
			int j = i;
			/*for (j = 0; j < max_account; j++)
			{
				if (account[i].account_number == account[j].account_number)
				{
					i = j;
					j = max_account;
				}

			}*/
			if (account[i].account_type == 'A')
			{
				printf("\nERROR: Agent accounts can't have tickets!\n\n");
				pauseExecution2();
				//printf("\n");
			}
			else
			{
				int high_ms_num = 0;
				int availabale_tick = 0;
				for (i = 0; i < max_tickets; i++)
				{
					if (ticket[i].tic_no == 0)
					{
						availabale_tick = i;
						i = max_tickets;
					}
				}
				if (availabale_tick == 0)
				{
					printf("ERROR: Ticket listing is FULL, call ITS Support!\n");
				}
				/*if ((availabale_tick != 0))
				{


					for (i = 0; i < max_tickets; i++)
					{
						if (i == 0)
						{
							high_ms_num = ticket[i].tic_no;
						}
						else if (ticket[i].tic_no > high_ms_num)
						{
							high_ms_num = ticket[i].tic_no;
						}


					}

				}*/
				ticket[availabale_tick].tic_no = high_ms_num + 1;//+1
				displayAccountDetailHeader();
				displayAccountDetailRecord(account[j]);
				if ((availabale_tick != 0))
				{


					for (i = 0; i < max_tickets; i++)
					{
						if (i == 0)
						{
							high_ms_num = ticket[i].tic_no;
						}
						else if (ticket[i].tic_no > high_ms_num)
						{
							high_ms_num = ticket[i].tic_no;
						}


					}

				}
				ticket[availabale_tick].tic_no = high_ms_num + 1;//+1

				printf("\nAdd a new ticket for this customer? ([Y]es|[N]o): ");

				char YorN = getCharOption("YN");
				if (YorN == 'Y')
				{
					printf("\nNew Ticket (Ticket#:%06d)\n", ticket[availabale_tick].tic_no);
					ticket[availabale_tick].cus_acc_no = account[j].account_number;
					ticket[availabale_tick].message->acc_type_of_author = 'C';

					ticket[availabale_tick].boolean = 1;
					strcpy(ticket[availabale_tick].message[0].author_name, account[j].person.fullname);
					printf("----------------------------------------\n");
					printf("Enter the ticket SUBJECT (30 chars. maximum): ");
					getCString(ticket[availabale_tick].subject, MIN_NAMELENGTH, MAX_NAMELENGTH);
					printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
					getCString(ticket[availabale_tick].message[0].messages, MIN_NAMELENGTH, MAX_MESSAGE);
					ticket[availabale_tick].no_of_msg++;
					printf("\n*** New ticket created! ***\n\n");




				}

			}


			if (account[j].account_type == 'C')
			{
				pauseExecution();

				printf("\n");
			}


		}break;
		case 9:
		{
			int valid, ac;
			int foo = 0, k;
			char Yorn;

			printf("\nEnter ticket number: ");
			scanf("%d", &ac);

			for (i = 0; i < max_tickets && foo == 0; i++)
			{
				if (ac == ticket[i].tic_no)
				{
					//printf("\n--%s\n",ticket[i].message[0].author_name);
					//printf("\n--%s\n", ticket[i].message[1].author_name);
					//printf("\n--%s\n", ticket[i].message[2].messages);


					do
					{
						valid = Display_manage_ticket(ticket[i], account);
						//j = ticket[i].no_of_msg;




						if ((valid == 1 || valid == 2) && ticket[i].boolean == 1)
						{

							if (valid == 1)
							{

								ticket[i].message[ticket[i].no_of_msg].acc_type_of_author = 'C';
								for (k = 0; k < max_account; k++)
								{
									if (account[k].account_number == ticket[i].cus_acc_no)
									{
										strcpy(ticket[i].message[ticket[i].no_of_msg].author_name, ticket[i].message[0].author_name);

									}

								}

								printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
								getCString(ticket[i].message[ticket[i].no_of_msg].messages, MIN_NAMELENGTH, MAX_MESSAGE);
								ticket[i].no_of_msg++;

							}
							if (valid == 2)
							{
								ticket[i].message[ticket[i].no_of_msg].acc_type_of_author = 'A';
								strcpy(ticket[i].message[ticket[i].no_of_msg].author_name, accounT->person.fullname);

								printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
								getCString(ticket[i].message[ticket[i].no_of_msg].messages, MIN_NAMELENGTH, MAX_MESSAGE);
								ticket[i].no_of_msg++;


							}
						}
						else if (ticket[i].boolean == 0 && (valid == 1 || valid == 2))

						{
							printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
						}
						else if (ticket[i].no_of_msg == max_tickets)
						{
							printf("ERROR: Message limit has been reached, call ITS Support!\n");
						}


						else if (valid == 3)
						{
							if (ticket[i].boolean == 0)
							{
								printf("\nERROR: Ticket is already closed!\n");
							}
							else
							{
								printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
								Yorn = getCharOption("YN");
								if (Yorn == 'Y' || Yorn == 'y')
								{
									ticket[i].boolean = 0;
									printf("\n*** Ticket closed! ***\n");
								}

							}
						}
						else if (valid == 4)
						{
							if (ticket[i].boolean == 1)
							{
								printf("\nERROR: Ticket is already active!\n");
							}
							else
							{
								printf("\nAre you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
								Yorn = getCharOption("YN");
								if (Yorn == 'Y')
								{
									ticket[i].boolean = 1;
									printf("\n*** Ticket re-activated! ***\n");
								}

							}

						}
						if (valid == 0)
						{
							printf("\n");

						}



					} while (valid != 0);
					foo = 1;


				}



			}

			if (foo == max_tickets)
			{
				printf("\nERROR: Invalid ticket number.\n\n");

			}



		}break;






		case 0:
		{
			int acc_count=0,i=0;
			int tic_count=0;
			FILE* FP;
			FP = fopen("accounts.txt", "w");
			if (FP != NULL)
			{
				for (i = 0; i < max_account; i++)
				{
					fprintf(FP, "%d~%c~%s~%d~%lf~", account[i].account_number, account[i].account_type, account[i].person.fullname, account[i].person.birth_year, account[i].person.household_income);
					if (account[i].account_type == 'C')
					{
						fprintf(FP, "%s\n", account[i].person.country);
						//strcpy(account[i].user.username, );
						//strcpy(account[i].user.password, NULL);

					}
					else if (account[i].account_type == 'A')
					{
						fprintf(FP, "%s~%s~%s\n", account[i].person.country, account[i].user.username, account[i].user.password);
					}
					//fscanf(fp, "%d~ %c~ %[^~] ~ %d ~ %lf ~ %[^~] ~ %[^~] ~ %[^\n]%c", &account[i].account_number, &account[i].account_type, account[i].fullname, &account[i].birth_year, &account[i].household_income, account[i].country, account[i].username, account[i].password,&type);
				}


				for ( i = 0; i < max_account; i++)
				{
					if (account[i].account_number == 0||i==max_account-1)
					{
						acc_count = i+1;
						//i = max_account;
					}
				}
				
			}
			else
			{
				printf("ERROR\n");
			}
			fclose(FP);


			struct Ticket t_ticket[20] = { { 0 } };
			
			for ( i = 0; i < max_tickets; i++)
			{
				t_ticket[i] = ticket[i];
				
			}






			
			int x;
			FP = fopen("tickets.txt", "w");
			if (FP != NULL)
			{
				for (i = 0; i<max_tickets; i++)
				{
					if (t_ticket[i].cus_acc_no != 0)
					{

						tic_count++;

						fprintf(FP, "%d|%d|%d|%s|%d|", t_ticket[i].tic_no, t_ticket[i].cus_acc_no, t_ticket[i].boolean, t_ticket[i].subject, t_ticket[i].no_of_msg);
						for (x = 0; x < t_ticket[i].no_of_msg; x++)
						{
							fprintf(FP, "%c|%s|%s|", t_ticket[i].message[x].acc_type_of_author, t_ticket[i].message[x].author_name, t_ticket[i].message[x].messages);
							if (x == t_ticket[i].no_of_msg - 1)
							{
								fprintf(FP, "\n");

								//printf("%d\n", x);
								//printf("ticno==%d mess count=%d\n", ticket[i].tic_no, ticket[i].no_of_msg);

							}
						}

					}
				}

				
				
			}

			else
			{
				printf("ERROR\n");
			}
			fclose(FP);





			printf("\nSaving session modifications...\n");
			printf("   %d account(s) saved.\n",acc_count);
			printf("   %d ticket(s) saved.\n",tic_count);







			printf("### LOGGED OUT ###\n\n");


		}break;





		}

	} while (menu != 0);



}

int findAccountIndexByAcctNum(int account_num, const struct Account account[], int max_index, int control)
{
	int acc_num = 0, i, j = 0;



	if (control != 0)
	{


		printf("\nEnter the account#: ");
		acc_num = getInteger();
		for (i = 0; i < max_index; i++)
		{
			if (acc_num != account[i].account_number)
			{
				j++;
				//acc_num = -1;
			}
			if (acc_num == account[i].account_number)
			{
				acc_num = i;
				i = max_index;
				j = 0;
			}

		}
	}


	if (j > 0)
	{
		acc_num = -1;
	}
	return acc_num;

}

void pauseExecution(void)
{
	//clearStandardInputBuffer();
	int  c;

	do {
		c = getchar();

	} while (c != '\n' && c != EOF);
	if (c == EOF) {
		// 
	}
	else {
		printf("<< ENTER key to Continue... >>");
		getchar();
	}
}


void updateAccount(struct Account* account)
{
	int MENU = -1;

	do
	{


		printf("\nUpdate Account: %d (%s)\n", account->account_number, account->person.fullname);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->account_type);
		printf("2) Person\n");
		printf("3) Login\n");
		printf("0) Done\n");
		printf("Selection: ");
		MENU = getIntFromRange(0, 3);

		switch (MENU)
		{
		case 1:
		{

			char userinput;
			printf("\nEnter the account type (A=Agent | C=Customer): ");

			userinput = getCharOption("AC");
			if (account->account_type == 'C' && userinput == 'A')
			{
				printf("\nAgent type accounts require a user login.  Please enter this information now:\n\n");
				getUserLogin(&account->user);
				account->account_type = 'A';
			}
			if (account->account_type == 'A' && userinput == 'C')
			{
				account->account_type = 'C';
				*account->user.password = 0;
				*account->user.username = 0;


			}
		}break;

		case 2:
		{

			updatePerson(&account->person);


		}break;


		case 3:

		{

			if (account->account_type == 'C')
			{
				printf("\nERROR:  Customer account types don't have user logins!\n");
			}

			else if (account->account_type == 'A')
			{

				updateUserLogin(&account->user);

			}

		}break;


		case 0: {
			printf("\n"); //changed
		}
		}


	} while (MENU != 0);
}
void updatePerson(struct Person* person)

{

	int menu = 0;
	do
	{
		int i;
		char up[31] = { 0 };
		//int x=strlen(account.person.country);
		for (i = 0; person->country[i] != '\0'; i++)
		{
			up[i] = toupper(person->country[i]);

		}
		up[i + 1] = '\0';


		printf("\nPerson Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Full name (current value: %s)\n", person->fullname);
		printf("2) Household Income (current value: $%.2lf)\n", person->household_income);
		printf("3) Country (current value: %s)\n", up);
		printf("0) Done\n");
		printf("Selection: ");

		menu = getIntFromRange(0, 3);
		switch (menu)
		{
		case 1:
		{
			printf("\nEnter the person's full name (30 chars max): ");
			getCString(person->fullname, MIN_NAMELENGTH, MAX_NAMELENGTH);

		}break;

		case 2:
		{
			printf("\nEnter the household Income: $");
			char newline = 'x';
			double Double = 0;
			int i = 0;
			do
			{
				scanf("%lf%c", &Double, &newline);
				if (newline == '\n')
				{
					i = 0;
				}
				if (newline != '\n')
				{
					i = 1;
					clearStandardInputBuffer();
					printf("ERROR: Value must be a double floating-point number: ");
				}
			} while (i == 1);

			person->household_income = Double;




		}		break;

		case 3:
		{
			printf("\nEnter the country (30 chars max.): ");
			getCString(person->country, MIN_NAMELENGTH, MAX_NAMELENGTH);


		}break;


		case 0: {
			//printf("");
		}
		}








	} while (menu != 0);





}
void updateUserLogin(struct UserLogin* user)
{
	int menu = 0;


	do
	{
		printf("\nUser Login: %s - Update Options\n", user->username);
		printf("----------------------------------------\n");
		printf("1) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		menu = getIntFromRange(0, 1);

		if (menu == 1)
		{
			int x = 0;
			printf("\n");
			do
			{

				int i;
				int lower = 0;
				int upper = 0;
				int sympol = 0;
				int number = 0;
				char sym[10] = "!@#$%^&*";
				printf("Enter the password (must be 8 chars in length): ");
				getCString(user->password, PASSWORD, PASSWORD);

				for (i = 0; i < PASSWORD; i++)
				{

					x = user->password[i];
					if (x >= 65 && x <= 90)
					{
						upper++;

					}
					if (x >= 97 && x <= 122)
					{
						lower++;
					}
					if (x >= 48 && x <= 57)
					{
						number++;

					}
					if (x == 33 || x == 64 || x == 35 || x == 36 || x == 94 || x == 38 || x == 42)
					{
						sympol++;

					}



				}
				if (number != 2 || sympol != 2 || lower != 2 || upper != 2)
				{
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: %s\n", sym);
					x = 1;


				}
				else
				{
					x = 0;
				}

			} while (x == 1);
		}



	} while (menu != 0);




}
void pauseExecution2(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}