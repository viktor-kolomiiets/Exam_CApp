/*Создайте приложение «Список дел». Приложение должно позволять:
1. Добавление дел. У дела есть:
  - название;
  - приоритет;
  - описание;
  - дата, время исполнения.
2. Удаление дел.
3. Редактирование дел.
4. Поиск дел по:
  - названию;
  - приоритету;
  - описанию;
  - дате и времени исполнения.
5. Отображение списка дел:
  - на день;
  - на неделю;
  - на месяц.
6. При отображении должна быть возможность сортировки:
  - по приоритету;
  - по дате и времени исполнения*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int SIZE = 100;
int lastNoteID = 0;

struct Date
{
	int minutes = 0;
	int hour = 0;
	int day = 0;
	int mounth = 0;
	int year = 0;

	long toNumber()
	{
		long _value = year * 100000000 + mounth * 1000000 + day * 10000 + hour * 100 + minutes;
		return _value;
	}

	int timeToValue()
	{
		return hour * 100 + minutes;
	}

	void removeDate()
	{
		minutes = 0;
		hour = 0;
		day = 0;
		mounth = 0;
		year = 0;
	}

	void print()
	{
		printf("%d.%d.%d, %d:%d", day, mounth, year, hour, minutes);
	}
};

struct Note
{
	string name = "";
	int prioritet = 0;
	string description = "";
	Date dataExecution;

	void addNote()
	{
		system("cls");
		cout << "Enter name: ";
		getline(cin, name);

		cout << "Enter note\'s prioritet:";
		//cout << "(bigger - higher): ";
		string input;
		getline(cin, input);
		prioritet = stoi(input);

		cout << "Enter description: ";
		getline(cin, description);

		cout << "Enter data&time execution:\n";
		cout << "\tDay    : ";
		getline(cin, input);
		dataExecution.day = stoi(input);
		cout << "\tMounth : ";
		getline(cin, input);
		dataExecution.mounth = stoi(input);
		cout << "\tYear   : ";
		getline(cin, input);
		dataExecution.year = stoi(input);
		cout << "\tHour   : ";
		getline(cin, input);
		dataExecution.hour = stoi(input);
		cout << "\tMinutes: ";
		getline(cin, input);
		dataExecution.minutes = stoi(input);
	}

	void removeNote()
	{
		name = "";
		prioritet = 0;
		description = "";
		dataExecution.removeDate();
	}

	void print()
	{
		cout << "" << prioritet << "\t|" << name << "\t| ";
		dataExecution.print();
		cout << "   " << description << "\n";
	}
};



void addBusiness(Note notes[])
{
	if (lastNoteID + 1 < 100)
	{
		notes[lastNoteID].addNote();
		lastNoteID += 1;
	}
	else
		cout << "Out of memory\n";
}

void removeBusiness(Note notes[])
{
	int id = 0;
	for (;;)
	{
		string input;
		cout << "Enter business No: ";
		getline(cin, input);
		id = stoi(input) - 1;
		if (id >= 0 && id <= lastNoteID)
			break;
		else
		{
			cout << "Out of range\n";
			continue;
		}
	}

	for (int i = id; i < lastNoteID; i++)
	{
		notes[i] = notes[i + 1];
	}
	notes[lastNoteID].removeNote();
	::lastNoteID--;
}

void editBusiness(Note notes[])
{
	int id = 0;
	for (;;)
	{
		string input;
		cout << "Enter business No: ";
		getline(cin, input);
		id = stoi(input) - 1;
		if (id >= 0 && id <= lastNoteID)
			break;
		else
		{
			cout << "Out of range\n";
			continue;
		}
	}

	system("cls");
	cout << "Enter new data:\n";
	notes[id].addNote();
}

void searchBusiness(Note notes[])
{
	int subMenu = 0;
	for (;;)
	{
		string input;
		cout << "";
		getline(cin, input);
		subMenu = stoi(input);
	}
}

void printBusiness(Note notes[])
{
	for (int i = 0; i < lastNoteID; i++)
	{
		notes[i].print();
	}
}

int main()
{
	Note notes[SIZE]{};
	string menu = "";

	for (;;)
	{
		cout << "1. Add business\n2. Remove business\n3. Edit business\n";
		cout << "4. Search business\n5. Print business list\n0. Exit\n>> ";
		getline(cin, menu);

		if (menu == "0")
			break;
		else if (menu == "1")
			addBusiness(notes);
		else if (menu == "2")
			removeBusiness(notes);
		else if (menu == "3")
			editBusiness(notes);
		else if (menu == "4")
			searchBusiness(notes);
		else if (menu == "5")
			printBusiness(notes);
		else
		{
			cout << "Unknown command\n";
			continue;
		}
	}

	return 0;
}
