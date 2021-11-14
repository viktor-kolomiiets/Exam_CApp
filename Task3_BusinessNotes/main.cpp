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
	int month = 0;
	int year = 0;

	void setDate()
	{
		cout << "\t\tDay      : ";
		day = inputNumRange(1, 31);
		cout << "\t\tMonth    : ";
		month = inputNumRange(1, 12);
		cout << "\t\tYear     : ";
		year = inputNumRange(1, 9999);
	}

	void setTime()
	{
		cout << "\t\tHour     : ";
		hour = inputNumRange(0, 24);
		cout << "\t\tMinutes  : ";
		minutes = inputNumRange(0, 59);
	}

	int getWeek()
	{
		return weekNo(year, month, day);
	}

	//convert date & time to union value
	long toValue()
	{
		long _value = year * 100000000 + month * 1000000 + day * 10000 + hour * 100 + minutes;
		return _value;
	}

	//convert time to union value
	int timeToValue()
	{
		return hour * 100 + minutes;
	}

	void removeDate()
	{
		minutes = 0;
		hour = 0;
		day = 0;
		month = 0;
		year = 0;
	}

	void print()
	{
		printf("%d.%d.%d, %d:%d", day, month, year, hour, minutes);
	}
};

struct Note
{
	string name = "";
	int priority = 0;
	string description = "";
	Date dateExec;

	void addNote()
	{
		system("cls");
		cout << "Enter business\'s name    : ";
		name = inputString();

		cout << "Enter note\'s priority    : ";
		priority = inputNum();

		cout << "Enter description        : ";
		description = inputString();

		cout << "Enter data&time execution:\n";
		dateExec.setDate();
		dateExec.setTime();
	}

	void removeNote()
	{
		name = "";
		priority = 0;
		description = "";
		dateExec.removeDate();
	}

	void print()
	{
		cout << priority << "\t| " << name << "\t| ";
		dateExec.print();
		cout << "\t| " << description << "\n";
	}
};

void setMinNotePrior(Note notes[], int start, int end)
{
	Note min = notes[start];

	for (int i = 1; i <= end; i++)
	{
		if (notes[i].priority < min.priority)
			min = notes[i];
	}

	notes[start] = min;
}

void sortByPriority(Note notes[], long size)
{
	Note note;
	long i, j;

	Note oldFirstNote = notes[0];

	setMinNotePrior(notes, 0, size - 1);

	for (i = 1; i < size; i++) {
		note = notes[i];
		for (j = i - 1; notes[j].priority > note.priority; j--)
			notes[j + 1] = notes[j];
		notes[j + 1] = note;
	}

	for (j = 1; j < size && notes[j].priority < oldFirstNote.priority; j++)
		notes[j - 1] = notes[j];

	notes[j - 1] = oldFirstNote;
}

void setMinNoteDate(Note notes[], int start, int end)
{
	Note min = notes[start];

	for (int i = 1; i <= end; i++)
	{
		if (notes[i].dateExec.toValue() < min.dateExec.toValue())
			min = notes[i];
	}

	notes[start] = min;
}

void sortByDate(Note notes[], long size)
{
	Note note;
	long i, j;

	Note oldFirstNote = notes[0];

	setMinNotePrior(notes, 0, size - 1);

	for (i = 1; i < size; i++) {
		note = notes[i];
		for (j = i - 1; notes[j].dateExec.toValue() > note.dateExec.toValue(); j--)
			notes[j + 1] = notes[j];
		notes[j + 1] = note;
	}

	for (j = 1; j < size && notes[j].dateExec.toValue() < oldFirstNote.dateExec.toValue(); j++)
		notes[j - 1] = notes[j];

	notes[j - 1] = oldFirstNote;
}

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
		id = inputNum() - 1;
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
		id = inputNum() - 1;
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

void printLine(Note note, int id)
{
	cout.width(4);
	cout << id << " \t| ";
	cout << note.name;
	if (note.name.size() < 8)
		cout << "\t";
	cout << "\t| " << note.priority << "\t|  ";
	note.dateExec.print();
	cout << "\t| ";
	cout << note.description << "\n";
}

void printTable(Note notes[], int size)
{
	int sub = 0;

	for (;;)
	{
		system("cls");
		cout << string(105, '-') << "\n";
		cout.width(4);
		cout << "   No\t| " << "Name\t\t| " << "Prior.|  " << "Date & Time Exec.\t| " << "Description" << endl;
		cout << string(105, '-') << "\n";

		for (int i = 0; i < size; i++)
			printLine(notes[i], i);

		cout << "0. Back\n>> ";

		sub = inputNum();
		if (sub == 0)
			break;
		else
			continue;
	}
}

void showBisinesses(Note notes[])
{
	int subMenu = 0;
	for (;;)
	{
		system("cls");
		cout << "Display to-do list for:\n";
		cout << "1. Day\n2. Week\n3. Month\n0. Back\n>> ";
		subMenu = inputNum();

		if (subMenu == 0)
			break;
		else if (subMenu == 1)
		{
			Date date;
			int sub = 0;
			
			system("cls");
			for (;;)
			{
				int id = -1;
				int outputSize = 0;
				Note* output;
				
				cout << "Enter day date:\n";
				date.setDate();

				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].dateExec.day == date.day && notes[i].dateExec.month == date.month && notes[i].dateExec.year == date.month)
						outputSize++;

				if (id == -1)
				{
					cout << "There is no entry for this day\n";
					//continue;
				}
				else
				{
					output = new Note[outputSize];
					int j = 0;
					for (int i = 0; i < lastNoteID; i++)
						if (notes[i].dateExec.day == date.day && notes[i].dateExec.month == date.month && notes[i].dateExec.year == date.month)
						{
							output[j] = notes[i];
							j++;
						}
					//system("cls");
					int sort = sortType();

					if (sort == 1)
						sortByPriority(output, outputSize);
					else
						sortByDate(output, outputSize);

					printTable(output, outputSize);

					if (output)
					{
						delete[] output;
						output = nullptr;
					}
				}

				cout << "0. Back\n>> ";
				sub = inputNum();
				if (sub == 0)
					break;
				else
					continue;
			}
		}
		else if (subMenu == 2)
		{
			int sub = 0, year = 0;

			system("cls");
			for (;;)
			{
				int id = -1, week = 0;
				int outputSize = 0;
				Note* output;

				cout << "Enter year:\n";
				year = inputNum();
				cout << "Enter week No (1 - 55): ";
				week = inputNumRange(1, 55);

				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].dateExec.year == year && notes[i].dateExec.getWeek() == week)
						outputSize++;

				if (id == -1)
				{
					cout << "There is no entry for this month\n";
					//continue;
				}
				else
				{
					output = new Note[outputSize];
					int j = 0;
					for (int i = 0; i < lastNoteID; i++)
						if (notes[i].dateExec.year == year && notes[i].dateExec.getWeek() == week)
						{
							output[j] = notes[i];
							j++;
						}

					int sort = sortType();
					if (sort == 1)
						sortByPriority(output, outputSize);
					else
						sortByDate(output, outputSize);
					//system("cls");
					printTable(output, outputSize);

					if (output)
					{
						delete[] output;
						output = nullptr;
					}
				}

				cout << "0. Back\n>> ";
				sub = inputNum();
				if (sub == 0)
					break;
				else
					continue;
			}
		}
		else if (subMenu == 3)
		{
			int sub = 0, month = 0;

			system("cls");
			for (;;)
			{
				int id = -1;
				int outputSize = 0;
				Note* output;

				cout << "Enter month:\n";
				month = inputNum();

				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].dateExec.month == month)
						outputSize++;

				if (id == -1)
				{
					cout << "There is no entry for this month\n";
					//continue;
				}
				else
				{
					output = new Note[outputSize];
					int j = 0;
					for (int i = 0; i < lastNoteID; i++)
						if (notes[i].dateExec.month == month)
						{
							output[j] = notes[i];
							j++;
						}
					
					int sort = sortType();
					if (sort == 1)
						sortByPriority(output, outputSize);
					else
						sortByDate(output, outputSize);
					//system("cls");
					printTable(output, outputSize);

					if (output)
					{
						delete[] output;
						output = nullptr;
					}
				}

				cout << "0. Back\n>> ";
				sub = inputNum();
				if (sub == 0)
					break;
				else
					continue;
			}
		}
		else
			continue;
	}
}

void searchBusiness(Note notes[])
{
	system("cls");
	int subMenu = 0;
	for (;;)
	{
		cout << "Search business note by:\n1. Name\n2. Priority\n3. Description\n4. Date & Time execution\n0. Back\n>> ";
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
				{
					cout << i + 1 << " | ";
					notes[i].print();
				}
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
				if (notes[i].priority == key)
				{
					cout << i + 1 << " | ";
					notes[i].print();
				}
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
				{
					cout << i + 1 << " | ";
					notes[i].print();
				}
			}
		}
		else if (subMenu == 4)
		{
			int sub = 0;
			for (;;)
			{
				system("cls");
				cout << "Search by:\n1. Date\n2. Time\n0. Back\n>> ";
				sub = inputNum();

				if (sub == 0)
					break;
				else if (sub == 1)
				{
					system("cls");
					cout << "Enter day   : ";
					int keyD = inputNum();
					cout << "Enter month : ";
					int keyM = inputNum();
					cout << "Enter year  : ";
					int keyY = inputNum();

					system("cls");
					for (int i = 0; i < lastNoteID; i++)
					{
						if (notes[i].dateExec.day == keyD && notes[i].dateExec.month == keyM && notes[i].dateExec.year == keyY)
						{
							cout << i + 1 << " | ";
							notes[i].print();
						}
					}
				}
				else if (sub == 2)
				{
					system("cls");
					cout << "Enter hour   : ";
					int keyH = inputNum();
					cout << "Enter minutes: ";
					int keyMn = inputNum();

					system("cls");
					for (int i = 0; i < lastNoteID; i++)
					{
						if (notes[i].dateExec.hour == keyH && notes[i].dateExec.minutes == keyMn)
						{
							cout << i + 1 << " | ";
							notes[i].print();
						}
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

int main()
{
	Note notes[SIZE]{};
	int menuNum = 0;

	for (;;)
	{
		system("cls");
		cout << "1. Add to-do note\n2. Remove to-do note\n3. Edit to-do note\n";
		cout << "4. Search to-do note\n5. Print to-do list\n0. Exit\n>> ";
		menuNum = inputNum();

		void (*menu[5])(Note notes[])
		{ 
			addBusiness,
			removeBusiness,
			editBusiness,
			searchBusiness,
			showBisinesses
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
