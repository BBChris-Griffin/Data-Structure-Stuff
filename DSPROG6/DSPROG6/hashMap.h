#pragma once
//HashMap Class

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "hastNode.h"

using namespace std;
#define TABLE_SIZE 51

class hashMap
{
private: 
	// Array of hashNode Pointers
	hashNode** hashTable;
	const char Months[12][6] = { "Jan. ", "Feb. ", "Mar. ", "Apr. ", "May  ", "Jun. ", "Jul. ",
		"Aug. ", "Sep. ", "Oct. ", "Nov. ", "Dec. " };

	//Gets the time inside of the class
	time_t t = time(0);   // get time now
	tm * now = localtime(&t);
	int thisYear = (now->tm_year + 1900);
	int thisMonth = (now->tm_mon + 1);
	int thisDay = now->tm_mday;
public:
	hashMap()
	{
		// Allocates an array of nodes to form hash table and sets them to null
		hashTable = new hashNode*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			hashTable[i] = NULL;
		}
	}

	//Hashing Function
	int hashFunc(int acct_number)
	{
		return (acct_number % TABLE_SIZE);
	}
	
	//Calculates exact year of service from the arrival date to now
	int FindServiceTime(int thisMonth, int thisDay, int thisYear, int arrivalMonth, int arrivalDay, int arrivalYear)
	{
		int serviceDay = thisDay - arrivalDay;
		int serviceMonth = thisMonth - arrivalMonth;
		int serviceYear = thisYear - arrivalYear;

		int serviceTime = serviceYear;

		if (serviceDay < 0)
		{
			serviceMonth--;
		}
		if (serviceMonth < 0)
		{
			serviceTime--;
		}

		return serviceTime;
	}

	void FindNewSalary(hashNode *entry)
	{
		//Calculates new Salary
		if (entry->serviceLength >= 20 && entry->serviceLength < 30)
		{
			entry->new_salary = entry->annual_salary + entry->annual_salary*0.1;
		}
		else if (entry->serviceLength >= 30)
		{
			entry->new_salary = entry->annual_salary + entry->annual_salary*0.1254;
		}
		else
		{
			entry->new_salary = entry->annual_salary + entry->annual_salary*0.085;
		}
	}

	//Insert into Hash Table
	void Insert(int account, char lastName[], char firstName[], int month, int day, int year, float salary, char deptCode)
	{
		int hash_key = hashFunc(account);
		hashNode* prev = NULL;
		hashNode* entry = hashTable[hash_key];
		bool collision = false;
		//If entry spot is full, while through the linked list to the next availble spot
		while (entry != NULL)
		{
			collision = true;
			prev = entry;
			entry = entry->next;
		}

		if (entry == NULL)
		{
			//Allocates new node
			entry = new hashNode(account, lastName, firstName, month, day, year, salary, deptCode);
			entry->collision = collision;
			entry->serviceLength = FindServiceTime(thisDay, thisMonth, thisYear, month, day, year);

			FindNewSalary(entry);

			//If the hashed location was empty from the beginning 
			if (prev == NULL)
			{
				hashTable[hash_key] = entry;
			}
			else
			{
				prev->next = entry;
			}
		}
	}

	//Prints hashing table to screen and to output file
	void PrintTable()
	{
		int count = 0;

		cout << setw(50) << right << "Employee Report" << endl;

		cout << setw(50) << right << "***************" << endl << endl << endl;

		cout << setw(60) << " " << "Current" << setw(17) << "New" << setw(20) << "Years" << endl;

		cout << setw(20) << left << "Last" << setw(20) << "Acct" << setw(20) << "Date of" << setw(20) << "Annual"
			<< setw(20) << "Annual" << setw(20) << "of" << endl;

		cout << setw(20) << left << "Name" << setw(20) << "Number" << setw(20) << "Hire" << setw(20) << "Salary"
			<< setw(20) << "Salary" << setw(20) << "Service" << endl << endl;

		//For loop runs through each item in array
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			hashNode *ptr = hashTable[i];
			//While loop checks for linked lists inside of an array element
			while (ptr != NULL)
			{
				if (!ptr->collision)
				{
					cout << setw(20) << left << ptr->last_name << setw(4) <<
						setfill('0') << internal << ptr->acct_number << ' ' << setw(16) << setfill(' ') << left <<
						' ' << setw(4) << Months[ptr->month - 1]
						<< setw(2) << ptr->day << ',' << setw(12) << ptr->year << setw(20)
						<< setprecision(2) << fixed << ptr->annual_salary << setw(20) <<
						setprecision(2) << fixed << ptr->new_salary << ptr->serviceLength << endl;
				}
				else
				{
					cout << setw(20) << left << ptr->last_name << setw(4) <<
						setfill('0') << internal << ptr->acct_number << '*' << setw(16) << setfill(' ') << left <<
						' ' << setw(4) << Months[ptr->month - 1]
						<< setw(2) << ptr->day << ',' << setw(12) << ptr->year << setw(20)
						<< setprecision(2) << fixed << ptr->annual_salary << setw(20) <<
						setprecision(2) << fixed << ptr->new_salary << ptr->serviceLength << endl;
				}

				count++;

				ptr = ptr->next;
			}
		}
		cout << endl << "Total Records Processed " << count << endl;
		cout << endl << "*indicates the record resulted in a collision when inserted into the hash table" << endl;
	}
	void PrintTableToFile(ofstream &myFile)
	{
		int count = 0;

		myFile << setw(50) << right << "Employee Report" << endl;

		myFile << setw(50) << right << "***************" << endl << endl << endl;

		myFile << setw(60) << " " << "Current" << setw(17) << "New" << setw(20) << "Years" << endl;

		myFile << setw(20) << left << "Last" << setw(20) << "Acct" << setw(20) << "Date of" << setw(20) << "Annual"
			<< setw(20) << "Annual" << setw(20) << "of" << endl;

		myFile << setw(20) << left << "Name" << setw(20) << "Number" << setw(20) << "Hire" << setw(20) << "Salary"
			<< setw(20) << "Salary" << setw(20) << "Service" << endl << endl;

		//For loop runs through each item in array
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			hashNode *ptr = hashTable[i];
			//While loop checks for linked lists inside of an array element
			while (ptr != NULL)
			{
				//Checks whether or not to add the '*' to account number
				if (!ptr->collision)
				{
					myFile << setw(20) << left << ptr->last_name << setw(4) <<
						setfill('0') << internal << ptr->acct_number << ' ' << setw(16) << setfill(' ') << left <<
						' ' << setw(4) << Months[ptr->month - 1]
						<< setw(2) << ptr->day << ',' << setw(12) << ptr->year << setw(20)
						<< setprecision(2) << fixed << ptr->annual_salary << setw(20) <<
						setprecision(2) << fixed << ptr->new_salary << ptr->serviceLength << endl;
				}
				else
				{
					myFile << setw(20) << left << ptr->last_name << setw(4) <<
						setfill('0') << internal << ptr->acct_number << '*' << setw(16) << setfill(' ') << left <<
						' ' << setw(4) << Months[ptr->month - 1]
						<< setw(2) << ptr->day << ',' << setw(12) << ptr->year << setw(20)
						<< setprecision(2) << fixed << ptr->annual_salary << setw(20) <<
						setprecision(2) << fixed << ptr->new_salary << ptr->serviceLength << endl;
				}

				count++;

				ptr = ptr->next;
			}
		}
		myFile << endl << "Total Records Processed " << count << endl;
		myFile << endl << "*indicates the record resulted in a collision when inserted into the hash table" << endl;
	}

	void Delete(int account)
	{
		int hash_key = hashFunc(account);
		//If location has no linked list attached and matches...
		if (hashTable[hash_key] != NULL && hashTable[hash_key]->next == NULL && account == hashTable[hash_key]->acct_number)
		{
			hashTable[hash_key] = NULL;
			return;
		}
		else if (hashTable[hash_key] != NULL && hashTable[hash_key]->next != NULL && account == hashTable[hash_key]->acct_number)
		{
			
			hashTable[hash_key] = hashTable[hash_key]->next;
			return;
		}
		hashNode *ptr = hashTable[hash_key];

		//If location is in a linked list
		while (ptr->next != NULL)
		{
			if (ptr->next->acct_number == account)
			{
				hashNode *temp = ptr->next->next;
				delete ptr->next;
				ptr->next = temp;
				return;
			}
			ptr->next = ptr->next->next;
		}
	}

	void Modify(int account, char lastName[], char firstName[], int month, int day, int year, float salary, char deptCode)
	{
		int hash_key = hashFunc(account);

		//Find the match and change the values
		hashNode *ptr = hashTable[hash_key];
		while (ptr != NULL)
		{
			if (ptr->acct_number == account)
			{
				strcpy(ptr->last_name,lastName);
				strcpy(ptr->last_name, lastName);
				ptr->month = month;
				ptr->day = day;
				ptr->year = year;
				ptr->annual_salary = salary;
				ptr->dept_code = deptCode;
				FindNewSalary(ptr);
				ptr->serviceLength = FindServiceTime(thisDay, thisMonth, thisYear, month, day, year);
			}
			ptr = ptr->next;
		}

	}

	bool Check(int account)
	{
		int hash_key = hashFunc(account);
		hashNode *ptr = hashTable[hash_key];

		while (ptr != NULL)
		{
			if (ptr->acct_number == account)
			{
				return true;
			}
			ptr = ptr->next;
		}
		return false;
	}

	void CreateHashTable(ifstream dataFile, hashMap hash, hashMap errorHash)
	{
		char last_name[15];
		char first_name[15];
		int acct_number;
		unsigned month;
		unsigned day;
		char year[4];
		float annual_salary;
		char dept_code;
		bool inserted;

		while (dataFile >> last_name >> first_name >> acct_number >> month >> day >> year >> annual_salary >> dept_code)
		{
			inserted = false;
			for (int i = 0; i < 4; ++i)
			{
				if (isalpha(year[i]))
				{
					errorHash.Insert(acct_number, last_name, first_name, month, day, 0000, annual_salary, dept_code);
					inserted = true;
				}
			}
			//If the month is even and the day is 31 or higher
			// If it's not a leap year in February, but the day exceeds 29
			// If the day not within 1 and 31
			//If the year is not within 1 and 12
			//Place into error file
			if ((month % 2 == 0 && day > 30) || (month == 2 && day > 28 && atoi(year) % 4 != 0) || (day < 1 || day > 31) || (month < 1 || month > 12))
			{
				if (!inserted)
					errorHash.Insert(acct_number, last_name, first_name, month, day, atoi(year), annual_salary, dept_code);
			}
			else
			{
				if (!inserted)
				{
					//Place into actual hashing table
					hash.Insert(acct_number, last_name, first_name, month, day, atoi(year), annual_salary, dept_code);
				}
			}
		}
	}

	void PrintMenu()
	{
		cout << "/////////////////////////////////////////////////////////////////" << endl;
		cout << "woooo Hash Tables..." << endl;
		cout << "1) Create Hash Table" << endl;
		cout << "2) Add Record" << endl;
		cout << "3) Modify Record" << endl;
		cout << "4) Delete Record" << endl;
		cout << "5) Print Record" << endl;
		cout << "6) Quit And Save [Exit System]" << endl;
		cout << "///////////////////////////////////////////////////////////////" << endl << endl;
	}
	
};