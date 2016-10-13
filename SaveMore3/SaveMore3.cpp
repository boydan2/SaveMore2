// ConsoleApplication8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
using namespace std;

class BankAccount //Generic "bank account" class that savings, checking, and CD will derive from
{
protected:
	char accountNumber[10];
	double interestRate;
	double balance;
public:
	virtual void createAccount() = 0;
	virtual void display() = 0;
	virtual void deposit() = 0;
	virtual void withdraw() = 0;
	virtual double interestCalc() = 0;//HAD TO PUT THESE LAST 2 IN. wouldnt let me call a method that wasnt defined in the generic "bank account" not sure why.
	virtual void orderChecks() = 0;
};










class Savings : public BankAccount
{
	int accountType = 0; //ACCOUNT TYPES: 0 - SAVINGS..... 1 - CHECKING..... 2 - CD.....
	double monthlyInterest = 0.0;
public:
	void createAccount() //constructor
	{
		cout << "enter desired 6 digit account number: ";
		gets_s(accountNumber);
		cout << "how much are you depositing for your beginning balance? ";
		cin >> balance;
		cin.clear();
		cin.ignore();

		getInterest();
	}//END createAccount (constructor)

	void display()//display account info
	{
		printf(" account type: %i\n account number: %s\n balance: %3.2f\n interest rate: %3.2f\n\n",
			accountType, accountNumber, balance, interestRate);
	}//END display

	void deposit()
	{
		double add = 0;//how much they want to add

		cout << "How much would you like to deposit?" << endl;//prompt
		cin >> add;
		balance += add;//adding
		getInterest();//recalc interest
	}//END deposit

	void withdraw()
	{
		double subtract = 0;//amount

		cout << "how much would you like to withdraw?" << endl;
		cin >> subtract;
		if (balance - 2 - subtract < 0)
		{
			cout << "error, invalid entry" << endl;
		}
		else
		{
			subtract += 2;//$2 fee for withdrawing
			balance -= subtract;
		}

		getInterest();//recalc interest
	}//END withdraw

	void getInterest() //determining interest rate (in every other method)
	{
		if (balance < 10000)
		{
			interestRate = 1.0;
		}
		else if (balance >= 10000)
		{
			interestRate = 2.0;
		}
	}//END get interest

	double interestCalc()
	{
		monthlyInterest = balance * (interestRate / 100);
		return monthlyInterest;
	}//END interestCalc

	void orderChecks()
	{

	}//void, cant use
};















class Checking : public BankAccount
{
	int accountType = 1;
	double interestRate = 0.0;
public:
	void createAccount()
	{
		cout << "enter desired 6 digit account number: ";
		gets_s(accountNumber);
		cout << "how much are you depositing for your beginning balance? ";
		cin >> balance;
		cin.clear();
		cin.ignore();
	}
	void display()
	{
		printf(" account type: %i\n account number: %s\n balance: %3.2f\n interest rate: %3.2f\n\n",
			accountType, accountNumber, balance, interestRate);
	}

	void deposit()
	{
		int add = 0;

		cout << "how much would you like to deposit?" << endl;
		cin >> add;
		balance += add;
	}//END deposit

	void withdraw()
	{
		int subtract = 0;

		cout << "how much would you like to withdraw?" << endl;
		cin >> subtract;
		if (balance - subtract < 0)
		{
			cout << "error, invalid entry" << endl;
		}
		else
		{
			balance -= subtract;
			check500();
		}

	}//END withdraw

	void check500()//$5 fee for deposit ending in less than 500
	{
		if (balance < 500)
		{
			balance -= 5;
		}
	}//END check500

	void orderChecks()
	{
		balance -= 15;
		cout << "your checks have been ordered" << endl;
	}//END orderChecks

	double interestCalc()
	{
		return 0;
	}//void. cant use
};

















class CD : public BankAccount
{
	int accountType = 2;
	int term = 0;
	double monthlyInterest = 0.0;
public:
	void createAccount()
	{
		cout << "enter CD term:  ";
		cin >> term;
		cin.clear();
		cin.ignore();
		cout << "enter desired 6 digit account number: ";
		gets_s(accountNumber);
		cout << "how much are you depositing for your CD? ";
		cin >> balance;
		cin.clear();
		cin.ignore();

		getInterest();
	}
	void display()
	{
		printf(" account type: %i\n account number: %s\n term: %i\n balance: %3.2f\n interest rate: %3.2f\n\n",
			accountType, accountNumber, term, balance, interestRate);
	}

	void deposit()
	{
		cout << "you cannot deposit to a CD" << endl;
	}//END deposit

	void withdraw()
	{
		int confirm = 0;
		int subtract = 0;
		cout << "if you choose to withdraw from this cd before the term expires, there will be a 10% fee on your whole balance" << endl;
		cout << "are you sure you wish to continue? 1 for yes and 0 for no" << endl;
		cin >> confirm;

		if (confirm == 1)
		{
			cout << "how much would you like to withdraw?" << endl;
			cin >> subtract;
			if (balance - 2 - subtract < 0)
			{
				cout << "error, invalid entry" << endl;
			}
			else
			{
				balance -= balance*0.10;
				balance -= subtract;
			}

		}
	}//END withdraw

	void getInterest()
	{
		if (term >= 5)
		{
			interestRate = 10.0;
		}
		else
		{
			interestRate = 5.0;
		}
	}//END getInterest

	double interestCalc()
	{
		monthlyInterest = balance * (interestRate / 100);
		return monthlyInterest;
	}//END interestCalc

	void orderChecks()
	{

	}//void, cant use
};















int main()
{
	BankAccount **bptr;
	int numberAccounts = 0;
	char answer[4];
	int answer2 = 0;//needed in the menu
	int choose = 0; //needed in the menu
	int accChoose = 0;//needed in the menu
	double currentInterest = 0.0;//used when displaying monthly interest

	cout << "how many bank accounts are you making? ";
	cin >> numberAccounts;
	cin.clear();
	cin.ignore();

	bptr = new BankAccount *[numberAccounts];
	for (int i = 0; i < numberAccounts; i++)
	{
		cout << "what type of account are you making? S for Savings, CH for checking, or CD for CD:  ";
		gets_s(answer);
		if (strcmp(answer, "CH") == 0)
		{
			bptr[i] = new Checking();
			bptr[i]->createAccount();
		}
		else if (strcmp(answer, "CD") == 0)
		{
			bptr[i] = new CD();
			bptr[i]->createAccount();
		}
		else if (strcmp(answer, "S") == 0)
		{
			bptr[i] = new Savings();
			bptr[i]->createAccount();
		}
		else
		{
			cout << "try again" << endl;
			--i;
		}
	}

	int o = 0;
	//OPTIONS to print/deposit/withdraw
	do
	{
		cout << "what would you like to do?" << endl;
		cout << "enter 1 for account access, 2 for display, or 0 for quit ";
		cin >> choose;
		cin.clear();
		cin.ignore();

		if (choose == 2)
		{
			for (int i = 0; i < numberAccounts; i++)
			{
				bptr[i]->display();
			}
		}
		else if (choose == 1)
		{
			cout << "which account do you want to access? 0 for first created, 1 for second created, 2 for third created" << endl;
			cin >> o;
			cin.clear();
			cin.ignore();
			cout << "what do you want to do with this account? enter 0 for withdraw, 1 for deposit, 2 for intrest calculation, or 3 for ordering checks" << endl;
			cin >> answer2;
			if (answer2 == 0)
			{
				bptr[o]->withdraw();
			}
			else if (answer2 == 1)
			{
				bptr[o]->deposit();
			}
			else if (answer2 == 2)
			{
				currentInterest = bptr[o]->interestCalc();
				cout << currentInterest << " is how much interest you will earn at the end of this month" << endl;
			}
			else if (answer2 == 3)
			{
				bptr[o]->orderChecks();
			}//END if
		}//END if
		else if (choose == 0)
		{
			cout << "goodbye" << endl;
		}
	} while (choose != 0);//END do while
	return 0;
}
