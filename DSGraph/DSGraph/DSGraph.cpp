// DSGraph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Utility.h"

using namespace std;
#define MAXSIZE 38
int main()
{
	int input = -1;
	string cities[MAXSIZE];
	string temp[MAXSIZE][MAXSIZE];
	int routes[MAXSIZE][MAXSIZE];
	ifstream excelFile;
	excelFile.open("directed_graph_of-cities-in-matrix_form_revised.csv");
	string city = "m";
	char nextLine = '5';
	int size = 0;
	int start, end;
	string startCity, endCity;
	bool directFlight = true;
	bool preReq = false;
	int price = 1500;
	int count = 0;

	for (int i = 0; i < MAXSIZE; ++i)
	{
		getline(excelFile, cities[i], ',');
	}
	RemoveFirstData(cities, MAXSIZE);

	for (int i = 0; i < MAXSIZE; ++i)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			getline(excelFile, temp[i][j], ',');
		}
	}

	CapatilizeCities(cities);

	RemoveFirstDataDoubleArray(temp, MAXSIZE);
	StringToIntMatrix(temp, routes, MAXSIZE);

	PrintMenu();
	while (input != 5)
	{
		cin >> input;
		switch (input)
		{
		case 1:
			do
			{

				cout << "Enter a Start City: (Capitalize first letter(s), please.)" << endl;
				if (count == 0)
				{
					cin.ignore();
				}
				getline(cin, startCity);
				cout << "Enter a Destination City: (Capitalize first letter(s), please.)" << endl;
				getline(cin, endCity);

				start = FindCity(startCity, cities, MAXSIZE);
				end = FindCity(endCity, cities, MAXSIZE);
				count++;
				if (start == -1)
				{
					cout << "The Start City is not valid!" << endl << endl;
				}
				if (end == -1)
				{
					cout << "The Destination City is not valid!" << endl << endl;
				}
			} while (start == -1 || end == -1);

			//If preReq is true, we can now access other options
			preReq = true;
			PrintMenu();

			break;
		case 2:
			if (preReq)
			{
				DijkstraShortestRoute(start, endCity, routes, cities);
			}
			else
			{
				cout << "Please select option 1 first!" << endl;
			}
			PrintMenu();

			break;
		case 3:
			if (preReq)
			{
				CheapestRoute(start, endCity, routes, cities);
			}
			else
			{
				cout << "Please select option 1 first!" << endl;
			}
			PrintMenu();
			break;
		case 4:
			if (preReq)
			{
				ShowAllRoutes(start, endCity, routes, cities);
			}
			else
			{
				cout << "Please select option 1 first!" << endl;
			}
			PrintMenu();
			break;
		default:
			break;
		}
	}
    return 0;
}

