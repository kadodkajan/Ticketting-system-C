#ifndef ACCOUNT_H_ 
#define ACCOUNT_H_




#pragma once

#define MAX_NAMELENGTH 30
#define MIN_NAMELENGTH 5 
#define MAX_USERNAME 10
#define PASSWORD 8
#define MIN_AGE 18
#define MAX_AGE 110
#define MAX_MESSAGE 150

/*struct Person
{
	char fullname[MAX_NAMELENGTH + 1];
	int birth_year;
	double household_income;
	char country[MAX_NAMELENGTH + 1];
};
struct UserLogin
{
	char username[MAX_USERNAME + 1];
	char password[PASSWORD + 1];
};*/
struct Account
{
	int account_number;
	char account_type;
	//struct Person person;
	struct Person
	{
		char fullname[MAX_NAMELENGTH + 1];
		int birth_year;
		double household_income;
		char country[MAX_NAMELENGTH + 1];
	}person;
	//struct UserLogin user;
	struct UserLogin
	{
		char username[MAX_USERNAME + 1];
		char password[PASSWORD + 1];
	}user;

}account[3];

void getAccount(struct Account* account);
void getPerson(struct Person* person);
void getUserLogin(struct UserLogin* user);
#endif