#include <iostream>
#include <string>
//#include <stdlib.h>
using namespace std;

string inputString()
{
	string input;
	getline(cin, input);
}

int inputNum()
{
	string input = inputString();
	return stoi(input);
}
