# Ticketing-system- Console application
## Ticketing system for manage customer inquiries.

## Programming Language C

MODULES
This project has multiple modules.The console apllication developed for  an accadamic project.

| Modules | Header | Source File | Usage |
| ------- | ------ | ----------- | ----- |
|a2ms4Master|       | a2ms4Master.c | This module contain the main part of the application. |
|accountTicketingUI| accountTicketingUI.h| accountTicketingUI.c | This module UI part of the application |
|account| account.h | account.c | This module is responsiple for loading the account details from a text file. |
|ticket| ticket.h | ticket.c | This module is responsiple for loading the ticket details from a text file. |
|commonHelpers| commonHelpers.h | commonHelpers.c | This module conatins some helper functions.|

```sh
gcc command
gcc a2ms4Master.c accountTicketingUI.c account.c ticket.c commonHelpers.c  -o run
./run
```





## Entry point of the application.
```sh
==============================================
Account Ticketing System - Login
==============================================
1) Login to the system
0) Exit application
----------------------------------------------

```
## Sample logins for running the application

```sh
Selection: 1

Enter the account#: 50008
User Login        : agentJ
Password          : TT*&21tt

AGENT: Will Smith (50008)
==============================================
Account Ticketing System - Agent Menu
==============================================
1) Add a new account
2) Modify an existing account
3) Remove an account
4) List accounts: detailed view
----------------------------------------------
5) List new tickets
6) List active tickets
7) List closed tickets
8) Add a new ticket
9) Manage a ticket
----------------------------------------------
0) Logout


```



