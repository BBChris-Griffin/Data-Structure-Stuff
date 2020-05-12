////////////////////////////////////////////////////////////////////
// DSPROG6.cpp : Defines the entry point for the console application.
// Christopher Griffin
// COP 3530
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "hashMap.h"
bool ValidDate(int month, int day, int year, int thisMonth, int thisDay, int thisYear);

using namespace std;

int main()
{
	char last_name[15];
	char first_name[15];
	int acct_number;
	char month[2];
	char day[2];
	char year[4];
	float annual_salary;
	char dept_code;

	time_t t = time(0);   // get time now
	tm * now = localtime(&t);
	int thisYear = (now->tm_year + 1900);
	int thisMonth = (now->tm_mon + 1);
	int thisDay = now->tm_mday;

	ifstream dataFile;
	dataFile.open("hash_proj_data6.txt");
	ofstream results;
	results.open("Results.txt");
	ofstream errors;
	errors.open("ErrorReport.txt");
	ofstream masterFile;

	bool inserted = false;
	bool dataRetrieved = false;
	bool errorAgain = false;
	int input = -1;

	hashMap hash;
	hashMap errorHash;

	hash.PrintMenu();

	while (input != 6)
	{
		cin >> input;

		switch (input)
		{
		case 1: 
			dataRetrieved = true;
			while (dataFile >> last_name >> first_name >> acct_number >> month >> day >> year >> annual_salary >> dept_code)
			{
				inserted = false;
				for (int i = 0; i < 4; ++i)
				{
					if (isalpha(year[i]))
					{
						errors << ' ' << last_name << ' ' << first_name << ' ' << acct_number
							<< ' ' << month << ' ' << day << ' ' << year << ' ' << annual_salary << ' ' << dept_code << endl;
						inserted = true;
					}
				}
				for (int i = 0; i < 2; ++i)
				{
					if (isalpha(month[i]))
					{
						errors  << ' ' << last_name << ' ' << first_name << ' ' << acct_number
							<< ' ' << month << ' ' << day << ' ' << year << ' ' << annual_salary << ' ' << dept_code << endl;
						inserted = true;
					}
				}
				for (int i = 0; i < 2; ++i)
				{
					if (isalpha(day[i]))
					{
						errors  << ' ' << last_name << ' ' << first_name << ' ' << acct_number
							<< ' ' << month << ' ' << day << ' ' << year << ' ' << annual_salary << ' ' << dept_code << endl;
						inserted = true;
					}
				}
				//If the month is even and the day is 31 or higher
				// If it's not a leap year in February, but the day exceeds 29
				// If the day not within 1 and 31
				//If the year is not within 1 and 12
				//Place into error file
				if (!ValidDate(atoi(month), atoi(day), atoi(year), thisMonth, thisDay, thisYear))
				{
					if (!inserted)
						errors  << ' ' << last_name << ' ' << first_name << ' ' << acct_number
						<< ' ' << month << ' ' <<  day << ' ' << year << ' ' << annual_salary << ' ' << dept_code << endl;

				}
				else
				{
					if (!inserted)
					{
						//Place into actual hashing table
						hash.Insert(acct_number, last_name, first_name, atoi(month), atoi(day), atoi(year), annual_salary, dept_code);
					}
				}
			}
			hash.PrintMenu();
		break;

		case 2:
			if (!dataRetrieved && !errorAgain)
			{
				cout << "WARNING: No data retrieved. Please choose a new option:" << endl;
				errorAgain = true;;
				break;
			}
			else if ((!dataRetrieved && errorAgain) || dataRetrieved)
			{
				cout << "Please enter the ACCOUNT NUMBER of the record you would like to add:" << endl;
				cin >> acct_number;

				if (!hash.Check(acct_number))
				{
					cout << "Please enter the LAST NAME of your new data: " << endl;
					cin >> last_name;
					cout << "Please enter the FIRST NAME of your new data: " << endl;
					cin >> first_name;

					do
					{
						cout << "Please enter the MONTH of your new data: " << endl;
						cin >> month;
						cout << "Please enter the DAY of your new data: " << endl;
						cin >> day;
						cout << "Please enter the YEAR of your new data: " << endl;
						cin >> year;

						if (!ValidDate(atoi(month), atoi(day), atoi(year), thisMonth, thisDay, thisYear))
						{
							cout << endl << "Invalid Date. Please try again" << endl << endl;
						}
					} while (!ValidDate(atoi(month), atoi(day), atoi(year), thisMonth, thisDay, thisYear));

					cout << "Please enter the ANNUAL SALARY of your new data: " << endl;
					cin >> annual_salary;
					cout << "Please enter the DEPT CODE of your new data: " << endl;
					cin >> dept_code;

					hash.Insert(acct_number, last_name, first_name, atoi(month), atoi(day), atoi(year), annual_salary, dept_code);
				}
				else
				{
					cout << "The ACCOUNT NUMBER is already used. Try choosing the modify option." << endl;
				}
				hash.PrintMenu();
			}
			break;
		case 3:
			if (!dataRetrieved && !errorAgain)
			{
				cout << "WARNING: No data retrieved. Please choose a new option:" << endl;
				errorAgain = true;
				break;
			}
			else if ((!dataRetrieved && errorAgain) || dataRetrieved)
			{
				cout << "Please enter the ACCOUNT NUMBER of the record you would like to modify:" << endl;
				cin >> acct_number;

				if (hash.Check(acct_number))
				{
					cout << "Please enter the LAST NAME of your new modified data: " << endl;
					cin >> last_name;
					cout << "Please enter the FIRST NAME of your new modified data: " << endl;
					cin >> first_name;
					do
					{
						cout << "Please enter the MONTH of your new modified data: " << endl;
						cin >> month;
						cout << "Please enter the DAY of your new modified data: " << endl;
						cin >> day;
						cout << "Please enter the YEAR of your new modified data: " << endl;
						cin >> year;

						if (!ValidDate(atoi(month), atoi(day), atoi(year), thisMonth, thisDay, thisYear))
						{
							cout << endl << "Invalid Date. Please try again" << endl << endl;
						}
					} while (!ValidDate(atoi(month), atoi(day), atoi(year), thisMonth, thisDay, thisYear));
					cout << "Please enter the ANNUAL SALARY of your new modified data: " << endl;
					cin >> annual_salary;
					cout << "Please enter the DEPT CODE of your new modified data: " << endl;
					cin >> dept_code;

					hash.Modify(acct_number, last_name, first_name, atoi(month), atoi(day), atoi(year), annual_salary, dept_code);
				}
				else
				{
					cout << "This account does not exist. Try choosing the ADD option." << endl;
				}
				hash.PrintMenu();
			}
			break;

		case 4:
			if (!dataRetrieved && !errorAgain)
			{
				cout << "WARNING: No data retrieved. Please choose a new option:" << endl;
				errorAgain = true;
				break;
			}
			else if ((!dataRetrieved && errorAgain) || dataRetrieved)
			{
				cout << "Please enter the ACCOUNT NUMBER of the record you would like to delete:" << endl;
				cin >> acct_number;

				if (hash.Check(acct_number))
				{
					hash.Delete(acct_number);
				}
				else
				{
					cout << "The account does not exist." << endl;
				}
				hash.PrintMenu();
			}
				break;
		case 5:
			if (!dataRetrieved && !errorAgain)
			{
				cout << "WARNING: No data retrieved. Please choose a new option:" << endl;
				errorAgain = true;
				break;
			}
			else if ((!dataRetrieved && errorAgain) || dataRetrieved)
			{
				hash.PrintTable();
				hash.PrintMenu();
			}
			break;
		case 6:
			dataFile.close();
			masterFile.open("hash_proj_data6.txt");
			hash.PrintTableToFile(masterFile);
			masterFile.close();
			exit(1);
			break;
		default:
			break;
		}
	}
	

	dataFile.close();
	results.close();
	errors.close();

    return 0;
}

bool ValidDate(int month, int day, int year, int thisMonth, int thisDay, int thisYear)
{
   
	//Checks that from February to June, even months should have no more than 30 days
	if (month % 2 == 0 && month < 8 && day > 30)
	{
		return false;
	}
	//Checks that from September to November, odd months should have no more than 30 days
	else if (month % 2 == 1 && month > 8 && day > 30)
	{
		return false;
	}
	//Checks that February is 28 days or less, except for leap years
	else if (month == 2 && day > 28 && year % 4 != 0)
	{
		return false;
	}
	else if (day < 1 || day > 31)
	{
		return false;
	}
	else if (month < 1 || month > 12)
	{
		return false;
	}
	else if (year > thisYear)
	{
		return false;
	}
	else if (year == thisYear && month > thisMonth)
	{
		return false;
	}
	else if (year == thisYear && month == thisMonth && day > thisDay)
	{
		return false;
	}
	else if (year < 1900)
	{
		return false;
	}
	
	return true;
}