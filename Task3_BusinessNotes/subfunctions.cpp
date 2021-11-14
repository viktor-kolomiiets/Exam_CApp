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

int sortType()
{
	cout << "Sort by:\n1. Priority\n2. Date & Time Exec.\n";
	return inputNum();
}
