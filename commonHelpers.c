
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"
#include <time.h>
#include "ticket.h"



int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing 
	}
}





int getInteger(void)
{

	char newline = 'x';
	int value, i = 0;
	do
	{
		scanf("%d%c", &value, &newline);
		if (newline == '\n')
		{
			i = 0;
		}
		if (newline != '\n')
		{
			i = 1;
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");

		}


	} while (i == 1);
	return value;
}


int getPositiveInteger(void)
{
	int PositiveInteger;
	do
	{
		PositiveInteger = getInteger();
		if (PositiveInteger < 0)
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}

	} while (PositiveInteger < 0);
	return PositiveInteger;
}

double getDouble(void)
{
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



	return Double;
}

double getPositiveDouble(void)
{
	double PositiveDouble = 0;
	do
	{
		PositiveDouble = getDouble();
		if (PositiveDouble <= 0.0000)
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
		}

	} while (PositiveDouble <= 0.0000);


	return PositiveDouble;
}

int getIntFromRange(int min, int max)
{
	int Integerinsiderange;
	int i = 0;
	do
	{
		i = 0;
		Integerinsiderange = getInteger();
		if (Integerinsiderange <min || Integerinsiderange>max)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", min, max);
			i = 1;
		}


	} while (i == 1);
	return Integerinsiderange;

}

char getCharOption(char CHAR[])

{
	char userchar[100];
	char returnchar;
	int i, j = 0, k = 1;
	for (i = 0; CHAR[i] != '\0'; i++)
	{
		//empty 
	}

	do
	{
		do
		{
			scanf(" %s", userchar);
			if (userchar[1] != '\0')
			{
				printf("ERROR: Character must be one of [%s]: ", CHAR);
			}

		} while (userchar[1] != '\0');

		for (j = 0; j < i; j++)
		{
			if (userchar[0] == CHAR[j])
			{
				k = 0;
				j = i;
			}


		}

		if (k == 1)
		{
			printf("ERROR: Character must be one of [%s]: ", CHAR);

		}

	} while (k == 1);
	returnchar = userchar[0];
	return returnchar;
};
void getCString(char charpointer[], int min, int max)
{
	int i = 0, j = 0, B = 0;
	char userinput[31] = { 0 };
	do
	{
		B = 0;
		scanf(" %[^\n]", userinput);
		//clearStandardInputBuffer();


		for (i = 0; userinput[i] != '\0'; i++)
		{

		}


		if (min == max && i != max)
		{
			printf("ERROR: String length must be exactly %d chars: ", max);
			B = 1;
		}
		else if (i > max)
		{
			printf("ERROR: String length must be no more than %d chars: ", max);
			B = 1;
		}
		else if (i < min)
		{
			printf("ERROR: String length must be between %d and %d chars: ", min, max);
			B = 1;
		}


	} while (B == 1);

	for (j = 0; j < i; j++)
	{
		charpointer[j] = userinput[j];

	}
	charpointer[i] = '\0';

	return;
};