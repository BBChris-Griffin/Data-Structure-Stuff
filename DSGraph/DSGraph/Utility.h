#pragma once
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <list>
#include <iomanip>
#include <string>

using namespace std;
#define MAXSIZE 38

void PrintMenu()
{
	cout << "-------------------------------------------------------------------" << endl;
	cout << " 1) Enter start city and destination city [Atlanta to New York]" << endl;
	cout << " 2) Find shortest route" << endl;
	cout << " 3) Find cheapest route" << endl;
	cout << " 4) Find ALL available route with cost" << endl;
	cout << " 5) Exit system" << endl << endl;
	cout << "-------------------------------------------------------------------" << endl;
}

void RemoveFirstData(string array[], int size)
{
	//Search through array 
	for (int i = 0; i < size - 1; ++i)
	{
		//Move next element to current
		array[i] = array[i + 1];

		//If at the end, make it empty
		if (i == size - 2)
		{
			array[i + 1] = ' ';
		}
	}
}

void CapatilizeCities(string array[])
{
	char *temp;
	for (int i = 0; i < MAXSIZE; ++i)
	{
		string str;
		temp = (char*)array[i].c_str();
		temp[0] = (char)toupper(temp[0]);
		array[i] = (string)temp;
	}
}

void RemoveFirstDataDoubleArray(string array[][MAXSIZE], int size)
{
	//Search through matrix
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			//Replace current element with next one
			array[i][j] = array[i][j + 1];
		}
	}
}

void StringToIntMatrix(string matrix[][MAXSIZE], int newMatrix[][38], int size)
{
	//Traverse Matrix
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			//if current matrix is blank, put 0 into new matrix
			if (matrix[i][j] == "\0")
			{
				newMatrix[i][j] = 0;
			}
			else
			{
				//Else, put in 1
				newMatrix[i][j] = 1;
			}
		}
	}
}


int FindCity(string city, string cities[], int size)
{
	//Return the string at the location of the int 
	for (int i = 0; i < size; ++i)
	{
		if (cities[i] == city)
		{
			return i;
		}
	}

	return -1;
}

void FindAllRoutes(int startCity, string endCity, vector<string*> &routes, vector<int> &size, vector<string> tempRoute, int matrix[MAXSIZE][MAXSIZE],
	string cities[])
{
	bool visited = false;
	tempRoute.push_back(cities[startCity]);

	//If start city is the end city
	if (cities[startCity] == endCity)
	{
		routes.push_back(new string[tempRoute.size()]);
		for (int i = 0; i < tempRoute.size(); i++)
		{
			routes[routes.size() - 1][i] = tempRoute[i];
		}
		size.push_back(tempRoute.size());
	}
	else
	{
		// Else, go through the city's adjacent rows
		for (int j = 0; j < MAXSIZE; j++)
		{
			visited = false;
			if (matrix[startCity][j] == 1)
			{
				for (int i = 0; i < tempRoute.size(); i++)
				{
					if (cities[j] == tempRoute[i])
					{
						visited = true;
						break;
					}
				}
				if (!visited)
				{
					FindAllRoutes(j, endCity, routes, size, tempRoute, matrix, cities);
				}
			}
		}
	}
	// Remove start city
	tempRoute.pop_back();
}

float Price(int cities)
{
	//If there is only a start and end city
	if (cities <= 2)
		return 1500;
	//if price comes to less than 100
	else if (1500 - (cities - 2) * 50 <= 100)
		return 100;
	else
		return 1500 - (cities - 2) * 50;
}

void CheapestRoute(int startCity, string endCity, int matrix[MAXSIZE][MAXSIZE], string cities[])
{
	vector<string*> routes; 
	vector<string> tempRoute;
	vector<int> size;

	FindAllRoutes(startCity, endCity, routes, size, tempRoute, matrix, cities);
	if (routes.size() == 0)
	{
		cout << endl << "Cannot find a route from " << cities[startCity] << " to " << endCity << "." << endl;
	}
	else
	{
		cout << "Cheapest Route: ";
		int lowCost = Price(size[0]);

		for (int i = 0; i < routes.size(); i++)
		{
			if (Price(size[i]) < lowCost)
			{
				lowCost = Price(size[i]);
			}
		}
		for (int i = 0; i < routes.size(); i++)
		{
			for (int j = 0; j < size[i]; j++)
			{
				if (Price(size[i]) == lowCost)
				{
					cout << "[" << routes[i][j] << "]" << " ";
				}
			}
			if (routes.size() <= 1)
			{
				cout << endl;
			}
			else if (Price(size[i]) == lowCost)
			{
				cout << " $" << fixed << setprecision(2) << Price(size[i]) << endl;
			}
		}
	}
}

void ShowAllRoutes(int startCity, string endCity, int matrix[MAXSIZE][MAXSIZE], string cities[])
{
	vector<string*> routes; 
	vector<string> tempRoute;
	vector<int> size;

	FindAllRoutes(startCity, endCity, routes, size, tempRoute, matrix, cities);
	if (routes.size() == 0)
	{
		cout << endl << "Cannot find a route from " << cities[startCity] << " to " << endCity << "." << endl;
	}
	else
	{
		for (int i = 0; i < routes.size(); i++)
		{
			cout << "Route " << i + 1 << " ";
			for (int j = 0; j < size[i]; j++)
			{
				cout << "[" << routes[i][j] << "]" << " ";
			}
			cout << " $" << fixed << setprecision(2) << Price(size[i]) << endl;
		}
	}
}

void DijkstraShortestRoute(int startCity, string destCity, int matrix[MAXSIZE][MAXSIZE], string cities[])
{
	vector<string*> routes; 
	vector<string> tempRoute;
	vector<int> size;

	FindAllRoutes(startCity, destCity, routes, size, tempRoute, matrix, cities);
	if (routes.size() == 0)
	{
		cout << endl << "Cannot find a route from " << cities[startCity] << " to " << destCity << "." << endl;
	}
	else
	{
		cout << "Shortest Route: ";
		int shortest = size[0];
		for (int i = 0; i < routes.size(); i++)
		{
			if (size[i] < shortest)
				shortest = size[i];
		}
		for (int i = 0; i < routes.size(); i++)
		{
			for (int j = 0; j < size[i]; j++)
			{
				if (size[i] == shortest)
					cout << "[" << routes[i][j] << "]" << " ";
			}
			if (routes.size() <= 1)
			{
				cout << endl;
			}
			else if (size[i] == shortest)
			{
				cout << " $" << fixed << setprecision(2) << Price(size[i]) << endl;
			}
		}
	}
}




