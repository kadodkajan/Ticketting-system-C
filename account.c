

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>



#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"
#include "account.h"



void getAccount(struct Account* account)

{

	printf("\nAccount Data: New Record\n");
	printf("----------------------------------------\n");
	printf("Enter the account number: ");
	account->account_number = getPositiveInteger();
	printf("\nEnter the account type (A=Agent | C=Customer): ");
	account->account_type = getCharOption("AC");


	printf("\n");
}
void getPerson(struct Person* person)
{




	int current_year = currentYear();
	printf("Person Data Input\n");
	printf("----------------------------------------\n");

	printf("Enter the person's full name (30 chars max): ");
	getCString(person->fullname, MIN_NAMELENGTH, MAX_NAMELENGTH);
	printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
	person->birth_year = getIntFromRange(current_year - MAX_AGE, current_year - MIN_AGE);
	printf("Enter the household Income: $");
	person->household_income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(person->country, MIN_NAMELENGTH, MAX_NAMELENGTH);
	int i;
	char* up = person->country;
	//int x=strlen(account.person.country);
	for (i = 0; person->country[i] != '\0'; i++)
	{
		up[i] = toupper(person->country[i]);

	}
	up[i + 1] = '\0';
	printf("\n");

}
void getUserLogin(struct UserLogin* user)

{
	int x, i;
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	//
	do
	{

		x = 0;

		printf("Enter user login (10 chars max): ");
		getCString(user->username, MIN_NAMELENGTH, MAX_USERNAME);
		for (i = 0; user->username[i] != '\0'; i++)
		{
			if (user->username[i] == ' ')
			{
				printf("ERROR:  The user login must NOT contain whitespace characters.\n");
				x = 1;
				user->username[i] = '\0';

			}
		}

	} while (x == 1);
	do
	{

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
