//hashNode struct

#pragma once
#include "stdafx.h"


struct hashNode {
	char last_name[15];
	char first_name[15];
	int acct_number;
	unsigned month;
	unsigned day;
	unsigned year;
	float annual_salary;
	float new_salary;
	char dept_code;
	int serviceLength;
	bool collision;
	hashNode *next;

	void SetCharArray(char memberArray[], char newArray[], int newArraySize)
	{
		for (int i = 0; i < 15; ++i)
		{
			if (i < newArraySize)
			{
				memberArray[i] = newArray[i];
			}
			else
			{
				memberArray[i] = '\0';
			}
		}
	}

	hashNode()
	{ 
		next = NULL;
	}

	hashNode(int account, char lastName[], char firstName[], unsigned mm, unsigned dd, unsigned yyyy, float salary,
		char deptCode)
	{

		acct_number = account;

		int i = 0;
		while (lastName[i] != NULL)
		{
			i++;
		}
		SetCharArray(last_name, lastName, i);

		i = 0;
		while (firstName[i] != NULL)
		{
			i++;
		}
		SetCharArray(first_name, firstName, i);

		month = mm;
		day = dd;
		year = yyyy;
		annual_salary = salary;
		dept_code = deptCode;		
		next = NULL;
	}

};