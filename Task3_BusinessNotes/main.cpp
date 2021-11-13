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
#include "subfunctions.h"
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
		name = inputString();

		cout << "Enter note\'s prioritet:";
		prioritet = inputNum();

		cout << "Enter description: ";
		description = inputString();

		cout << "Enter data&time execution:\n";
		cout << "\tDay    : ";
		dataExecution.day = inputNum();
		cout << "\tMounth : ";
		dataExecution.mounth = inputNum();
		cout << "\tYear   : ";
		dataExecution.year = inputNum();
		cout << "\tHour   : ";
		dataExecution.hour = inputNum();
		cout << "\tMinutes: ";
		dataExecution.minutes = inputNum();
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
	system("cls");
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
	system("cls");
	int id = 0;
	for (;;)
	{
		cout << "Enter business No: ";
		id = inputNum();
		if (id >= 0 && id <= lastNoteID)
			break;
		else
		{
			cout << "Out of range\n";
			continue;
		}
	}

	system("cls");
	for (int i = id; i < lastNoteID; i++)
	{
		notes[i] = notes[i + 1];
	}
	notes[lastNoteID].removeNote();
	::lastNoteID--;
}

void editBusiness(Note notes[])
{
	system("cls");
	int id = 0;

	for (;;)
	{
		cout << "Enter business No: ";
		id = inputNum();
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
	system("cls");
	int subMenu = 0;
	for (;;)
	{
		cout << "Search business note by:\n 1. name\n 2. priority\n 3. description\n 4. date & time execution\n0. Back\n>> ";
		subMenu = inputNum();

		if (subMenu == 0)
			break;
		else if (subMenu == 1)
		{
			system("cls");
			cout << "Enter searching name: ";
			string key = inputString();

			system("cls");
			for (int i = 0; i < lastNoteID; i++)
			{
				if (notes[i].name == key)
					notes[i].print();
			}
		}
		else if (subMenu == 2)
		{
			system("cls");
			cout << "Enter business priority: ";
			int key = inputNum();

			system("cls");
			for (int i = 0; i < lastNoteID; i++)
			{
				if (notes[i].prioritet == key)
					notes[i].print();
			}
		}
		else if (subMenu == 3)
		{
			system("cls");
			cout << "Enter key word: ";
			string key = inputString();

			system("cls");
			for (int i = 0; i < lastNoteID; i++)
			{
				if (notes[i].description.find(key) != string::npos)
					notes[i].print();
			}
		}
		else if (subMenu == 4)
		{
			int sub = 0;
			for (;;)
			{
				system("cls");
				cout << "Search by:\n 1. date\n 2. time\n0. Back\n>> ";
				sub = inputNum();

				if (sub == 0)
					break;
				else if (sub == 1)
				{
					system("cls");
					cout << "Enter day: ";
					int keyD = inputNum();
					cout << "Enter mounth: ";
					int keyM = inputNum();
					cout << "Enter year: ";
					int keyY = inputNum();

					system("cls");
					for (int i = 0; i < lastNoteID; i++)
					{
						if (notes[i].dataExecution.day == keyD && notes[i].dataExecution.mounth == keyM && notes[i].dataExecution.year == keyY)
							notes[i].print();
					}
				}
				else if (sub == 2)
				{
					system("cls");
					cout << "Enter hour: ";
					int keyH = inputNum();
					cout << "Enter minutes: ";
					int keyMn = inputNum();

					system("cls");
					for (int i = 0; i < lastNoteID; i++)
					{
						if (notes[i].dataExecution.hour == keyH && notes[i].dataExecution.minutes == keyMn)
							notes[i].print();
					}
				}
				else
				{
					system("cls");
					continue;
				}
			}
		}
		else
			continue;
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
	int menuNum = 0;

	for (;;)
	{
		system("cls");
		cout << "1. Add business\n2. Remove business\n3. Edit business\n";
		cout << "4. Search business\n5. Print business list\n0. Exit\n>> ";
		menuNum = inputNum();

		void (*menu[5])(Note notes[])
		{ 
			addBusiness,
			removeBusiness,
			editBusiness,
			searchBusiness,
			printBusiness
		};

		if (menuNum == 0)
			break;
		else if (menuNum >= 1 && menuNum <= 5)
			menu[menuNum - 1](notes);
		else
			continue;
	}

	return 0;
}
