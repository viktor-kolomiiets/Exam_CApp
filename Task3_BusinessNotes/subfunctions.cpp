#include <iostream>
#include <string>
using namespace std;

string inputString()
{
	string input;
	getline(cin, input);
	return input;
}

int inputNum()
{
	string input = inputString();
	for (;;)
	{
		if (input.size() == 0)
			input = inputString();
		else
			break;
	}
	return stoi(input);
}

//scan user's input in range [lborder; rborder] from console
int inputNumRange(int lborder, int rborder)
{
	int input = 0;
	for (;;)
	{
		input = inputNum();
		if (input >= lborder && input <= rborder)
			break;
		else
			cout << "Invalid value\n";
	}
	return input;
}

bool isVisokosnyy(int year)
{
	return year % 4 == 0 ? true : false;
}

//converts curent date to amount days from new year
int dateToDay(int year, int mounth, int day)
{
	int amountDay = 0;

	//count of days in each mounth (not visokosnyy year)
	int mounthsDays[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	for (int i = 0; i < mounth - 1; i++)
	{
		amountDay += mounthsDays[i];

		//if year visokosniy then +1 day
		if (isVisokosnyy(year) && i == 1)
		{
			amountDay += 1;
		}
	}

	return amountDay + day;
}

int weekNo(int year, int month, int day)
{
	return (dateToDay(year, month, day) / 7) + 1;
}

void noSearches()
{
	cout << "To-Do note was not found\n";
	cout << "0. Back\n>> ";
	string s = inputString();
	if (s.size() >= 0)
		return;
	return;
}